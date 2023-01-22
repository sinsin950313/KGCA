#pragma once

#include "CommonSocket.h"
#include <queue>

namespace SSB
{
	class SelectBaseCommunicationModule : public CommunicationModule
	{
	private:
		std::queue<UserID> _selectedList;

	protected:
		std::map<UserID, std::unique_ptr<Session>>::iterator GetNext() override;
	};

	class ListenWithSelectBaseCommunicationModule : public SelectBaseCommunicationModule, public ListenSocketInterface
	{
	private:
		bool _isListenEstablished = false;
		SOCKET _listenSocket;

	public:
		UserID Listen() override;
	};
}
