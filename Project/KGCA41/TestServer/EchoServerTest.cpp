#include "CommonSocket.h"
#include <iostream>
#include <queue>
#include <thread>

#pragma comment(lib, "CommunicationModule.lib")

namespace SSB
{
	class ConsoleDefaultAction : public CommunicationTypeAction
	{
	private:
		Packet _packet;

	public:
		void SetPacket(Packet packet)
		{
			_packet = packet;
		}

	public:
		void operator()() override;
	};
	void ConsoleDefaultAction::operator()()
	{
		int length = _packet.GetLength();
		const char* buf = _packet.Serialize();
		std::cout << "Console Default Action Called" << std::endl;
	}

	class ConsoleDefaultDecoder : public Decoder
	{
	public:
		CommunicationTypeAction* Decode(Packet packet) override;
	};
	CommunicationTypeAction* ConsoleDefaultDecoder::Decode(Packet packet)
	{
		static ConsoleDefaultAction action;
		action.SetPacket(packet);
		return &action;
	}

	class ConsoleDefaultCommunicationModule : public CommunicationModule, public ListenSocketInterface
	{
	private:
		std::queue<SOCKET> waitForRegister;
		bool _listenSocketEstablished;
		SOCKET _listenSocket;
		std::thread _listenThread;

	private:
		void RunListenSocket(SOCKET listenSocket);
		bool IsListenEstablished();

	public:
		UserID Listen() override;
	};
	void ConsoleDefaultCommunicationModule::RunListenSocket(SOCKET listenSocket)
	{
		while (1)
		{
			SOCKADDR_IN clientAddr;
			int length = sizeof(clientAddr);
			SOCKET clientSocket = accept(listenSocket, (sockaddr*)&clientAddr, &length);
			if (clientSocket == SOCKET_ERROR)
			{
				int error = WSAGetLastError();
				continue;
			}

			waitForRegister.push(clientSocket);
		}
	}
	bool ConsoleDefaultCommunicationModule::IsListenEstablished()
	{
		return _listenSocketEstablished;
	}
	UserID ConsoleDefaultCommunicationModule::Listen()
	{
		static SOCKET listenSocket;
		if (!IsListenEstablished())
		{
			_listenSocketEstablished = true;
			listenSocket = EstablishListen();

			static std::thread th(&ConsoleDefaultCommunicationModule::RunListenSocket, this, listenSocket);
		}

		SOCKET socketID = NewConnectionNotExist;
		if (!waitForRegister.empty())
		{
			socketID = waitForRegister.front();
			Connect(socketID);
			waitForRegister.pop();
		}
		return socketID;
	}
}

int main()
{
	SSB::ConsoleDefaultCommunicationModule cm;
	SSB::ConsoleDefaultDecoder decoder;
	while (1)
	{
		{
			SSB::UserID id = cm.Listen();
			if (id == WSAEWOULDBLOCK)
			{
				continue;
			}
		}

		SSB::UserID id;
		SSB::Packet packet;
		if (cm.Read(&id, packet))
		{
			SSB::CommunicationTypeAction* action = decoder.Decode(packet);
			(*action)();
		}
	}
}