#pragma once

#include "CommonSocket.h"
#include <queue>
#include <map>

namespace SSB
{
	class EventSelectBaseCommunicationModule : public CommunicationModule
	{
	private:
		std::queue<int> _eventIndexQueue;
		HANDLE	_eventArray[64];
		std::map<UserID, int> _userIDToEventIndex;
		std::map<int, UserID> _eventIndexToUserID;
		int _nextIndex = 0;

	public:
		EventSelectBaseCommunicationModule();

	protected:
		bool RegisterEventSelect(UserID id);

	protected:
		void DIsconnect(UserID id) override;
		std::map<UserID, std::unique_ptr<Session>>::iterator GetNext() override;

	public:
		UserID Connect(IPAddress address = TestIP, PortNumber port = TestPort) override;
	};

	class ListenWithEventSelectBaseCommunicationModule : public EventSelectBaseCommunicationModule, public ListenSocketInterface
	{
	private:
		bool _isListenEstablished = false;
		SOCKET _listenSocket;
		int _listenIndex;
		std::queue<int> _eventIndexQueue;
		HANDLE	_eventArray[64];
		std::map<UserID, int> _userIDToEventIndex;

	public:
		ListenWithEventSelectBaseCommunicationModule();

	public:
		UserID Listen() override;
	};
}
