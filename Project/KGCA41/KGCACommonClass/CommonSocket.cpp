#include "CommonSocket.h"
#include <iostream>

namespace SSB
{
	Packet::Packet(ProtocolType type, PacketContent* content)
	{
		memcpy(_data, &_header, HeaderSize);

		auto data = content->Serialize();
		_header.ContentLength = data.Size;
		memcpy(_data + HeaderSize, data.Head, data.Size);

		_length = HeaderSize + data.Size;
	}
	Packet::Packet(Byte* serialData, int packetLength)
	{
		memcpy(_data, serialData, packetLength);
		_length = packetLength;
	}
	const Byte* Packet::Serialize()
	{
		return _data;
	}
	int Packet::GetLength()
	{
		return _length;
	}
	Client::Client(SOCKET socket, UserID id) : _socket(socket), _id(id)
	{
		u_long mode = TRUE;
		//ioctlsocket(_socket, FIONBIO, &mode);
	}
	Client::~Client()
	{
		closesocket(_socket);
	}
	bool Client::Read(Packet& packet)
	{
		int length = 0;
		Byte buf[PacketSize]{ 0, };
		while (length != HeaderSize)
		{
			int recvByte = recv(_socket, buf + length, HeaderSize - length, 0);
			if (recvByte == SOCKET_ERROR)
			{
				int error = WSAGetLastError();
				if (error != WSAEWOULDBLOCK)
				{
					_disconnect = true;
					return false;
				}
			}
			if (recvByte == 0)
			{
				_disconnect = true;
				return false;
			}
			length += recvByte;
		}

		HeaderStructure header;
		memcpy(&header, buf, HeaderSize);

		int contentLength = header.ContentLength;
		length = 0;
		while (length != contentLength)
		{
			int recvByte = recv(_socket, buf + HeaderSize + length, contentLength - length, 0);
			if (recvByte == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK)
				{
					_disconnect = true;
					return false;
				}
			}
			if (recvByte == 0)
			{
				_disconnect = true;
				return false;
			}
			length += recvByte;
		}

		packet = Packet(buf, HeaderSize + contentLength);

		return true;
	}
	bool Client::Write(Packet& packet)
	{
		int sendCount = 0;
		auto buf = packet.Serialize();
		while (sendCount != packet.GetLength())
		{
			int sendByte = send(_socket, buf + sendCount, packet.GetLength() - sendCount, 0);
			if (sendByte == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK)
				{
					_disconnect = true;
					return false;
				}
			}
			//if (sendByte == 0)
			//{
			//	_disconnect = true;
			//	return false;
			//}
			sendCount += sendByte;
		}

		return true;
	}
	SOCKET Client::GetSocket()
	{
		return _socket;
	}
	bool Client::IsDisconnect()
	{
		return _disconnect;
	}
	bool CommunicationModule::Write(UserID id, Packet packet)
	{
		auto& client = _connectionData.find(id)->second;
		bool ret = client->Write(packet);
		if (!ret)
		{
			if (client->IsDisconnect())
			{
				DIsconnect(id);
			}
		}
		return ret;
	}
	bool CommunicationModule::Read(UserID id, Packet& packet)
	{
		auto& client = _connectionData.find(id)->second;
		bool ret = client->Read(packet);
		if (!ret)
		{
			if (client->IsDisconnect())
			{
				DIsconnect(id);
			}
		}
		return ret;
	}
	bool CommunicationModule::Read(UserID* id, Packet& packet)
	{
		auto iter = GetNext();
		if (iter != _connectionData.end())
		{
			Client& client = *(iter->second);
			bool ret = client.Read(packet);
			*id = iter->first;
			if (!ret)
			{
				if (client.IsDisconnect())
				{
					DIsconnect(iter->first);
				}
			}

			return ret;
		}

		return false;
	}
	CommunicationModule::CommunicationModule()
	{
		if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		{
			return;
		}
	}
	CommunicationModule::~CommunicationModule()
	{
		WSACleanup();
	}
	void CommunicationModule::DIsconnect(UserID id)
	{
		_dataUpdated = true;
		delete _connectionData.find(id)->second;
		_connectionData.erase(id);
		_iter = _connectionData.begin();
	}
	void CommunicationModule::Connect(SOCKET socket)
	{
		_dataUpdated = true;
		_connectionData.insert(std::make_pair(socket, new Client(socket, socket)));
		_iter = _connectionData.begin();
	}
	std::map<UserID, Client*>::iterator CommunicationModule::GetNext()
	{
		if (_connectionData.empty())
		{
			return _connectionData.end();
		}

		if (_dataUpdated)
		{
			_dataUpdated = false;
			_iter = _connectionData.begin();
		}

		if (_iter == _connectionData.end())
		{
			_iter = _connectionData.begin();
		}

		return _iter++;
	}
	UserID CommunicationModule::Listen(PortNumber port)
	{
		if (_listenSocketID == ListenNotEstablished)
		{
			SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);

			SOCKADDR_IN sa;
			sa.sin_family = AF_INET;
			sa.sin_addr.s_addr = htonl(INADDR_ANY);
			sa.sin_port = htons(port);

			{
				int ret = bind(listenSocket, (sockaddr*)&sa, sizeof(sa));
				if (ret == SOCKET_ERROR)
				{
					WSACleanup();
					return 1;
				}
			}
			{
				int ret = listen(listenSocket, SOMAXCONN);
				if (ret == SOCKET_ERROR)
				{
					WSACleanup();
					return 1;
				}
			}

			_listenSocketID = listenSocket;
			//Connect(listenSocket);

			//u_long mode = FALSE;
			//ioctlsocket(listenSocket, FIONBIO, &mode);
		}

		//SOCKET listenSocket = (*_connectionData.find(_listenSocketID)->second).GetSocket();
		SOCKADDR_IN clientAddr;
		int length = sizeof(clientAddr);
		SOCKET clientSocket = accept(_listenSocketID, (sockaddr*)&clientAddr, &length);
		if (clientSocket == SOCKET_ERROR)
		{
			return WSAGetLastError();
		}

		Connect(clientSocket);

		return clientSocket;
	}
	void CommunicationModule::Connect(IPAddress address, PortNumber port)
	{
		static SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);

		SOCKADDR_IN sa;
		sa.sin_family = AF_INET;
		sa.sin_addr.s_addr = inet_addr(address.c_str());
		sa.sin_port = htons(port);
		{
			int ret = connect(clientSocket, (sockaddr*)&sa, sizeof(sa));
		}
		Connect(clientSocket);
	}
	void CommunicationModule::Close(UserID id)
	{
		DIsconnect(id);
	}
	bool CommunicationModule::IsClosed(UserID id)
	{
		return _connectionData.find(id) == _connectionData.end();
	}
}
