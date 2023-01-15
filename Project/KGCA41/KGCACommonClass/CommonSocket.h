#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "NetworkProtocol.h"
#include <WinSock2.h>
#include <map>
#include <string>

namespace SSB
{
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

	class PacketHeader
	{
	private:
		HeaderStructure _structure;

	public:
		PacketHeader(HeaderStructure header);

	public:
		virtual Byte* Serialize() = 0;
		virtual CommunicationTypeAction& GetAction() = 0;
	};

	class ConsoleDefaultPacketHeader : public PacketHeader
	{
	public:
		ConsoleDefaultPacketHeader();

	public:
		Byte* Serialize() override;
		CommunicationTypeAction& GetAction() override;
	};

	class PacketContent
	{
	public:
		virtual Byte* Serialize() = 0;
	};

	typedef int UserID;

	class Packet
	{
	private:
		Byte _data[256];

	public:
		Packet(PacketHeader type, PacketContent content);
		Packet(Byte* serialData);

	public:
		const Byte* Serialize();
		PacketHeader GetHeader();
		PacketContent GetContent();
	};

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
		void Write(UserID id, PacketHeader header, PacketContent content);
		virtual void Read(UserID id, PacketHeader& header, PacketContent& content);
		virtual UserID Read(PacketHeader& header, PacketContent& content);
		UserID Listen(PortNumber port);
		void Connect(IPAddress address, PortNumber port);
	};
}
