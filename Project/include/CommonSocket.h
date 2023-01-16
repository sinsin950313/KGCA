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
		unsigned int PacketLength;
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

	public:
		Packet(ProtocolType type, PacketContent* content);
		Packet(Byte* serialData);

	public:
		const Byte* Serialize();
		int GetLength();
	};

	class Decoder
	{
	public:
		virtual CommunicationTypeAction& Decode(Packet packet) = 0;
	};

	typedef int UserID;

	class Client
	{
	private:
		SOCKET _socket;
		UserID _id;

	public:
		Client(SOCKET socket, UserID id);

	public:
		Packet Read();
		void Write(Packet packet);
	};

	typedef int PortNumber;
	typedef std::string IPAddress;

	class CommunicationModule
	{
	private:
		std::map<UserID, Client> _connectionData;

	public:
		void Write(UserID id, Packet packet);
		virtual void Read(UserID id, Packet& packet);
		virtual UserID Read(Packet& packet);
		UserID Listen(PortNumber port);
		void Connect(IPAddress address, PortNumber port);
	};
}
