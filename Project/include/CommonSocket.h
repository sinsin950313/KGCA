#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

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

	class ConsoleDefaultAction : public CommunicationTypeAction
	{
	public:
		void operator()() override;
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

	class ConsoleDefaultDecoder : public Decoder
	{
	public:
		CommunicationTypeAction& Decode(Packet packet) override;
	};

	typedef int UserID;

	class Client
	{
	private:
		SOCKET _socket;
		UserID _id;

	public:
		Client(SOCKET socket, UserID id);
		~Client();

	public:
		Packet Read();
		void Write(Packet packet);
		SOCKET GetSocket();
	};

	typedef int PortNumber;
	typedef std::string IPAddress;
#define TestPort 10000
#define TestIP "127.0.0.1"

	class CommunicationModule
	{
#define ListenSocketID -1
	private:
		WSADATA wsa;
		std::map<UserID, Client> _connectionData;

	public:
		CommunicationModule();
		~CommunicationModule();

	public:
		bool Write(UserID id, Packet packet);
		virtual bool Read(UserID id, Packet& packet);
		virtual bool Read(UserID* id, Packet& packet);
		UserID Listen(PortNumber port = TestPort);
		void Connect(IPAddress address = TestIP, PortNumber port = TestPort);
		void Close(UserID id);
		bool IsClosed(UserID id);
	};
}
