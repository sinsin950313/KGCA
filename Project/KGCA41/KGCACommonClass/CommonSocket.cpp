#include "CommonSocket.h"
#include <iostream>

namespace SSB
{
	void ConsoleDefaultAction::operator()()
	{
		std::cout << "Console Default Action Called" << std::endl;
	}

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
	CommunicationTypeAction& ConsoleDefaultDecoder::Decode(Packet packet)
	{
		static ConsoleDefaultAction action;
		return action;
	}
	Client::Client(SOCKET socket, UserID id) : _socket(socket), _id(id)
	{
		u_long mode = TRUE;
		ioctlsocket(_socket, FIONBIO, &mode);
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
			length += recv(_socket, buf + length, HeaderSize - length, 0);
		}

		HeaderStructure header;
		memcpy(&header, buf, HeaderSize);

		int contentLength = header.ContentLength;
		length = 0;
		while (length != contentLength)
		{
			length += recv(_socket, buf + HeaderSize + length, contentLength - length, 0);
		}

		return Packet(buf, HeaderSize + contentLength);
	}
	bool Client::Write(Packet& packet)
	{
		int sendCount = 0;
		auto buf = packet.Serialize();
		while (sendCount != packet.GetLength())
		{
			sendCount += send(_socket, buf + sendCount, packet.GetLength() - sendCount, 0);
		}

		return;
	}
	SOCKET Client::GetSocket()
	{
		return _socket;
	}
	bool CommunicationModule::Write(UserID id, Packet packet)
	{
		bool ret = _connectionData.find(id)->second.Write(packet);
		if (!ret)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				_connectionData.erase(id);
			}
		}
		return ret;
	}
	bool CommunicationModule::Read(UserID id, Packet& packet)
	{
		bool ret = _connectionData.find(id)->second.Read(packet);
		if (!ret)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				_connectionData.erase(id);
			}
		}
		return ret;
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
	UserID CommunicationModule::Listen(PortNumber port)
	{
		if (_connectionData.find(ListenSocketID) == _connectionData.end())
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

			_connectionData.insert(std::make_pair(ListenSocketID, Client(listenSocket, ListenSocketID)));
		}

		SOCKET listenSocket = _connectionData.find(ListenSocketID)->second.GetSocket();
		SOCKADDR_IN clientAddr;
		int length = sizeof(clientAddr);
		SOCKET clientSocket = accept(listenSocket, (sockaddr*)&clientAddr, &length);

		int clientID = _connectionData.size();
		_connectionData.insert(std::make_pair(clientID, Client(clientSocket, clientID)));

		return clientID;
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
	}
	void CommunicationModule::Close(UserID id)
	{
		_connectionData.erase(id);
	}
	bool CommunicationModule::IsClosed(UserID id)
	{
		return _connectionData.find(id) == _connectionData.end();
	}
}
