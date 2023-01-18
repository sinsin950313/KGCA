#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment (lib, "ws2_32.lib")

#include "NetworkProtocol.h"
#include <WinSock2.h>
#include <map>
#include <string>

namespace SSB
{
	struct HeaderStructure
	{
		ProtocolType Type;
		unsigned int ContentLength;
	};

#define HeaderSize sizeof(HeaderStructure)

	class CommunicationTypeAction
	{
	public:
		virtual void operator()() = 0;
	};

#define PacketSize 256

	struct PacketContentStruct
	{
		Byte Head[PacketSize - HeaderSize];
		int Size;
	};

	class PacketContent
	{
	public:
		virtual PacketContentStruct Serialize() = 0;
	};

	class Packet
	{
	private:
		HeaderStructure _header;
		Byte _data[PacketSize];
		int _length;

	public:
		Packet() = default;
		Packet(ProtocolType type, PacketContent* content);
		Packet(Byte* serialData, int packetLength);

	public:
		const Byte* Serialize();
		int GetLength();
	};

	class Decoder
	{
	public:
		virtual CommunicationTypeAction& Decode(Packet packet) = 0;
	};

	typedef SOCKET UserID;

	class Client
	{
	private:
		SOCKET _socket;
		UserID _id;
		bool _disconnect = false;;

	public:
		Client(SOCKET socket, UserID id);
		~Client();

	public:
		bool Read(Packet& packet);
		bool Write(Packet& packet);
		SOCKET GetSocket();
		bool IsDisconnect();
	};

	typedef int PortNumber;
	typedef std::string IPAddress;
#define TestPort 10000
#define TestIP "127.0.0.1"
#define ListenNotEstablished -1

	class CommunicationModule
	{
	private:
		UserID _listenSocketID = ListenNotEstablished;
		WSADATA wsa;
		std::map<UserID, Client*> _connectionData;
		bool _dataUpdated = true;;
		std::map<UserID, Client*>::iterator _iter;

	public:
		CommunicationModule();
		~CommunicationModule();

	protected:
		void DIsconnect(UserID id);
		void Connect(SOCKET socket);
		virtual std::map<UserID, Client*>::iterator GetNext();

	public:
		bool Write(UserID id, Packet packet);
		bool Read(UserID id, Packet& packet);
		bool Read(UserID* id, Packet& packet);
		UserID Listen(PortNumber port = TestPort);
		void Connect(IPAddress address = TestIP, PortNumber port = TestPort);
		void Close(UserID id);
		bool IsClosed(UserID id);
	};
}
