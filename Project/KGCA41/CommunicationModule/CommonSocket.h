#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment (lib, "ws2_32.lib")

#include "NetworkProtocol.h"
#include <WinSock2.h>
#include <map>
#include <string>
#include <memory>

namespace SSB
{
	class CommunicationTypeAction
	{
	public:
		virtual void operator()() = 0;
	};

	struct HeaderStructure
	{
		ProtocolType Type;
		unsigned int ContentLength;
	};

#define HeaderSize sizeof(HeaderStructure)
#define PacketSize 256

	struct PacketContentStruct
	{
		Byte Stream[PacketSize - HeaderSize];
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
		Byte _data[PacketSize];
		int _length;

	public:
		Packet() = default;
		Packet(ProtocolType type, PacketContent& content);
		Packet(Byte* serialData, int packetLength);

	public:
		const Byte* Serialize();
		int GetLength();
	};

	class Decoder
	{
	public:
		virtual CommunicationTypeAction* Decode(Packet packet) = 0;
	};

	typedef SOCKET UserID;

	class Session
	{
	private:
		SOCKET _socket;
		UserID _id;
		bool _disconnect = false;;

	public:
		Session(SOCKET socket, UserID id);
		~Session();

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
#define NewConnectionNotExist -1

	class CommunicationModule
	{
	private:
		WSADATA wsa;

	protected:
		std::map<UserID, std::unique_ptr<Session>> _connectionData;
		std::map<UserID, std::unique_ptr<Session>>::iterator _iter;
		bool _dataUpdated = true;;

	public:
		CommunicationModule();
		~CommunicationModule();

	protected:
		SOCKET EstablishListen(PortNumber port = TestPort);
		void Connect(SOCKET socket);

	protected:
		virtual std::map<UserID, std::unique_ptr<Session>>::iterator GetNext();
		virtual void DIsconnect(UserID id);

	public:
		bool Write(UserID id, Packet packet);
		bool Read(UserID id, Packet& packet);
		bool Read(UserID* id, Packet& packet);
		void Close(UserID id);
		bool IsClosed(UserID id);

	public:
		virtual UserID Connect(IPAddress address = TestIP, PortNumber port = TestPort);
	};

	class ListenSocketInterface
	{
	public:
		virtual UserID Listen() = 0;
	};
}
