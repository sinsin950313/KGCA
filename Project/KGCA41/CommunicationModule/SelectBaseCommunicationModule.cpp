#include "SelectBaseCommunicationModule.h"

namespace SSB
{
	std::map<UserID, std::unique_ptr<Session>>::iterator SelectBaseCommunicationModule::GetNext()
	{
		FD_SET rSet;
		FD_SET wSet;
		FD_SET eSet;

		FD_ZERO(&rSet);
		FD_ZERO(&wSet);
		FD_ZERO(&eSet);

		for (auto& user : _connectionData)
		{
			FD_SET(user.second->GetSocket(), &rSet);
			FD_SET(user.second->GetSocket(), &wSet);
			FD_SET(user.second->GetSocket(), &eSet);
		}

		timeval timeOut;
		timeOut.tv_sec = 0;
		timeOut.tv_usec = 1000;
		{
			int ret = select(0, &rSet, &wSet, &eSet, &timeOut);
			if (ret == SOCKET_ERROR) return _connectionData.end();
			if (ret == 0) return _connectionData.end();
		}

		for (auto iter = _connectionData.begin(); iter != _connectionData.end(); ++iter)
		{
			if (FD_ISSET(iter->second->GetSocket(), &rSet))
			{
				_selectedList.push(iter->first);
			}
			if (FD_ISSET(iter->second->GetSocket(), &wSet))
			{
				continue;
			}
			if (FD_ISSET(iter->second->GetSocket(), &eSet))
			{
				continue;
			}
		}

		if (!_selectedList.empty())
		{
			UserID id = _selectedList.front();
			_selectedList.pop();
			return _connectionData.find(id);
		}
		return _connectionData.end();
	}
	UserID ListenWithSelectBaseCommunicationModule::Listen()
	{
		if (!_isListenEstablished)
		{
			_listenSocket = EstablishListen();
			_isListenEstablished = true;
		}

		UserID clientSocket = NewConnectionNotExist;

		FD_SET rSet;
		FD_SET wSet;
		FD_SET eSet;

		FD_ZERO(&rSet);
		FD_ZERO(&wSet);
		FD_ZERO(&eSet);

		FD_SET(_listenSocket, &rSet);
		FD_SET(_listenSocket, &wSet);
		FD_SET(_listenSocket, &eSet);

		timeval timeOut;
		timeOut.tv_sec = 0;
		timeOut.tv_usec = 1000;
		{
			int ret = select(0, &rSet, &wSet, &eSet, &timeOut);
			if (ret == SOCKET_ERROR) return NewConnectionNotExist;
			if (ret == 0) return NewConnectionNotExist;
		}

		if (FD_ISSET(_listenSocket, &rSet))
		{
			SOCKADDR_IN clientAddr;
			int length = sizeof(clientAddr);
			clientSocket = accept(_listenSocket, (sockaddr*)&clientAddr, &length);
			Connect(clientSocket);

			printf("Client connected at IP : %s, Port : %d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

			u_long mode = TRUE;
			ioctlsocket(clientSocket, FIONBIO, &mode);
		}

		return clientSocket;
	}
}
