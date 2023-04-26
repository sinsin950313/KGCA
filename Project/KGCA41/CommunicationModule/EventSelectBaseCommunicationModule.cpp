#include "EventSelectBaseCommunicationModule.h"

namespace SSB
{
	SSB::EventSelectBaseCommunicationModule::EventSelectBaseCommunicationModule()
	{
		for (int i = 0; i < 64; ++i)
		{
			_eventIndexQueue.push(i);
		}
	}

	bool EventSelectBaseCommunicationModule::RegisterEventSelect(UserID id)
	{
		if (!_eventIndexQueue.empty())
		{
			int index = _eventIndexQueue.front();
			_eventIndexQueue.pop();
			_userIDToEventIndex.insert(std::make_pair(id, index));
			_eventIndexToUserID.insert(std::make_pair(index, id));

			HANDLE eventHandle = WSACreateEvent();
			_eventArray[index] = eventHandle;
			WSAEventSelect(_connectionData.find(id)->second->GetSocket(), eventHandle, FD_READ | FD_WRITE | FD_CLOSE);
			return true;
		}
		return false;
	}

	void SSB::EventSelectBaseCommunicationModule::DIsconnect(UserID id)
	{
		int index = _userIDToEventIndex.find(id)->second;
		_eventIndexQueue.push(index);

		{
			auto iter = _userIDToEventIndex.find(id);
			_userIDToEventIndex.erase(iter);
		}

		{
			auto iter = _eventIndexToUserID.find(index);
			_eventIndexToUserID.erase(iter);
		}

		CommunicationModule::DIsconnect(id);
	}

	std::map<UserID, std::unique_ptr<Session>>::iterator EventSelectBaseCommunicationModule::GetNext()
	{
        if (_dataUpdated)
        {
            _dataUpdated = false;
            _nextIndex = 0;
        }

		if (_nextIndex == _userIDToEventIndex.size())
		{
			_nextIndex = 0;
		}

        DWORD index = WSAWaitForMultipleEvents(_userIDToEventIndex.size() - _nextIndex, _eventArray + _nextIndex, FALSE, 0, FALSE);
        if (index == WSA_WAIT_FAILED) return _connectionData.end();
        if (index == WSA_WAIT_TIMEOUT) return _connectionData.end();
        index -= WSA_WAIT_EVENT_0;

		int finalIndex = index + _nextIndex;
		UserID id = _eventIndexToUserID.find(finalIndex)->second;
		SOCKET sock = _connectionData.find(id)->second->GetSocket();

		WSANETWORKEVENTS netEvent;
		int iRet = WSAEnumNetworkEvents(sock, _eventArray[finalIndex], &netEvent);
		if (iRet != SOCKET_ERROR)
		{
			if (netEvent.lNetworkEvents & FD_READ)
			{
				_nextIndex = index + _nextIndex + 1;
				return _connectionData.find(id);
			}
		}
		return _connectionData.end();
	}

	UserID SSB::EventSelectBaseCommunicationModule::Connect(IPAddress address, PortNumber port)
	{
		UserID id = CommunicationModule::Connect(address, port);
		if (!_eventIndexQueue.empty())
		{
			int index = _eventIndexQueue.front();
			_eventIndexQueue.pop();
			_userIDToEventIndex.insert(std::make_pair(id, index));
			_eventIndexToUserID.insert(std::make_pair(index, id));

			HANDLE eventHandle = WSACreateEvent();
			_eventArray[index] = eventHandle;
			WSAEventSelect(_connectionData.find(id)->second->GetSocket(), eventHandle, FD_READ | FD_WRITE | FD_CLOSE);

			return id;
		}

		return NewConnectionNotExist;
	}

    ListenWithEventSelectBaseCommunicationModule::ListenWithEventSelectBaseCommunicationModule()
    {
		for (int i = 0; i < 64; ++i)
		{
			_eventIndexQueue.push(i);
		}
    }

    UserID SSB::ListenWithEventSelectBaseCommunicationModule::Listen()
	{
		if (!_isListenEstablished)
		{
			_listenSocket = EstablishListen();
			_isListenEstablished = true;

			_listenIndex = _eventIndexQueue.front();
			_eventIndexQueue.pop();
			_userIDToEventIndex.insert(std::make_pair(_listenSocket, _listenIndex));

			HANDLE event = WSACreateEvent();
			_eventArray[_listenIndex] = event;
			WSAEventSelect(_listenSocket, event, FD_ACCEPT);
		}

        DWORD index = WSAWaitForMultipleEvents(1, &_eventArray[_listenIndex], FALSE, 0, FALSE);
        if (index == WSA_WAIT_FAILED) return NewConnectionNotExist;
        if (index == WSA_WAIT_TIMEOUT) return NewConnectionNotExist;
        index -= WSA_WAIT_EVENT_0;

        if (index == 0)
        {
            WSANETWORKEVENTS netEvent;
            int iRet = WSAEnumNetworkEvents(_listenSocket, _eventArray[_listenIndex], &netEvent);
            if (iRet != SOCKET_ERROR)
            {
                if (netEvent.lNetworkEvents & FD_ACCEPT)
                {
                    // 접속되면 반환된다.
                    SOCKADDR_IN clientaddr;
                    int length = sizeof(clientaddr);
                    SOCKET clientSocket = accept(_listenSocket, (sockaddr*)&clientaddr, &length);
                    if (clientSocket == SOCKET_ERROR)
                    {
                        return NewConnectionNotExist;
                    }

                    CommunicationModule::Connect(clientSocket);
					if (RegisterEventSelect(clientSocket))
					{
						return clientSocket;
					}
                }
            }
        }
        return NewConnectionNotExist;
	}
}
