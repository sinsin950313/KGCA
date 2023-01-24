#include "CommonSocket.h"
#include <iostream>

namespace SSB
{
	Packet::Packet(ProtocolType type, PacketContent& content)
	{
		HeaderStructure header;
		header.Type = type;
		auto data = content.Serialize();
		header.ContentLength = data.Size;
		memcpy(_data, &header, HeaderSize);

		memcpy(_data + HeaderSize, data.Stream, data.Size);

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
	Session::Session(SOCKET socket, UserID id) : _socket(socket), _id(id)
	{
		u_long mode = TRUE;
		//ioctlsocket(_socket, FIONBIO, &mode);
	}
	Session::~Session()
	{
		closesocket(_socket);
	}
	bool Session::Read(Packet& packet)
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
	bool Session::Write(Packet& packet)
	{
		int sendCount = 0;
		auto buf = packet.Serialize();
		while (sendCount != packet.GetLength())
		{
			int sendByte = send(_socket, buf + sendCount, packet.GetLength() - sendCount, 0);
			if (sendByte == SOCKET_ERROR)
			{
				int error = WSAGetLastError();
				if (error != WSAEWOULDBLOCK)
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
	SOCKET Session::GetSocket()
	{
		return _socket;
	}
	bool Session::IsDisconnect()
	{
		return _disconnect;
	}
	bool CommunicationModule::Write(UserID id, Packet packet)
	{
		bool ret = false;
		auto iter = _connectionData.find(id);
		if (iter != _connectionData.end())
		{
			auto& Session = iter->second;
			ret = Session->Write(packet);
			if (!ret)
			{
				if (Session->IsDisconnect())
				{
					DIsconnect(id);
				}
			}
		}
		return ret;
	}
	bool CommunicationModule::Read(UserID id, Packet& packet)
	{
		bool ret = false;
		auto iter = _connectionData.find(id);
		if (iter != _connectionData.end())
		{
			auto& Session = iter->second;
			ret = Session->Read(packet);
			if (!ret)
			{
				if (Session->IsDisconnect())
				{
					DIsconnect(id);
				}
			}
		}
		return ret;
	}
	bool CommunicationModule::Read(UserID* id, Packet& packet)
	{
		auto iter = GetNext();
		if (iter != _connectionData.end())
		{
			Session& Session = *(iter->second);
			bool ret = Session.Read(packet);
			*id = iter->first;
			if (!ret)
			{
				if (Session.IsDisconnect())
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
		_connectionData.erase(id);
		_iter = _connectionData.begin();
	}
	void CommunicationModule::Connect(SOCKET socket)
	{
		_dataUpdated = true;
		// change to unique_ptr
		_connectionData.insert(std::make_pair(socket, std::make_unique<Session>(socket, socket)));
		_iter = _connectionData.begin();
	}
	std::map<UserID, std::unique_ptr<Session>>::iterator CommunicationModule::GetNext()
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
	SOCKET CommunicationModule::EstablishListen(PortNumber port)
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

		return listenSocket;
	}
	UserID CommunicationModule::Connect(IPAddress address, PortNumber port)
	{
		SOCKET SessionSocket = socket(AF_INET, SOCK_STREAM, 0);

		SOCKADDR_IN sa;
		sa.sin_family = AF_INET;
		sa.sin_addr.s_addr = inet_addr(address.c_str());
		sa.sin_port = htons(port);
		{
			int ret = connect(SessionSocket, (sockaddr*)&sa, sizeof(sa));
			if (ret == SOCKET_ERROR)
			{
				int error = GetLastError();
				return NewConnectionNotExist;
			}
		}
		Connect(SessionSocket);

		return SessionSocket;
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
