#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment (lib, "ws2_32.lib")

#include <WinSock2.h>
#include <iostream>
#include <list>

struct User
{
	SOCKET sock;
	SOCKADDR_IN address;
};
std::list<User> userList;

DWORD WINAPI ServerThread(LPVOID lpThreadParameter)
{
	while (1)
	{
		for (auto iter = userList.begin(); iter != userList.end();)
		{
			const int bufferSize = 256;
			char recvMsg[bufferSize]{ 0, };
			int recvByte = recv(iter->sock, recvMsg, bufferSize, 0);
			if (recvByte == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK)
				{
					printf("Client exit with error. IP : %s, Port : %d\n", inet_ntoa(iter->address.sin_addr), ntohs(iter->address.sin_port));
					closesocket(iter->sock);
					iter = userList.erase(iter);
					continue;
				}
			}
			else if (recvByte == 0)
			{
				printf("Client exit. IP : %s, Port : %d\n", inet_ntoa(iter->address.sin_addr), ntohs(iter->address.sin_port));
				closesocket(iter->sock);
				iter = userList.erase(iter);
				continue;
			}
			else
			{
				printf("%s", recvMsg);
			}

			if (recvByte > 0)
			{
				for (auto sendIter = userList.begin(); sendIter != userList.end();)
				{
					int sendByte = send(sendIter->sock, recvMsg, bufferSize, 0);
					if (sendByte == SOCKET_ERROR)
					{
						if (WSAGetLastError() != WSAEWOULDBLOCK)
						{
							printf("Client exit with error 2. IP : %s, Port : %d\n", inet_ntoa(sendIter->address.sin_addr), ntohs(sendIter->address.sin_port));
							closesocket(sendIter->sock);
							sendIter = userList.erase(sendIter);
							continue;
						}
					}
					++sendIter;
				}
			}
			++iter;
		}
	}
}

int main()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return 0;
	}

	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN sa;
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	sa.sin_port = htons(10000);

	{
		int ret = bind(listenSocket, (sockaddr*)&sa, sizeof(sa));
		if (ret == SOCKET_ERROR)
		{
			WSACleanup();
			return 1;
		}
	}
	{
		int ret = listen(listenSocket, SOMAXCONN);
		if (ret == SOCKET_ERROR)
		{
			WSACleanup();
			return 1;
		}
	}

	//DWORD threadID;
	//HANDLE handle = CreateThread(0, 0, ServerThread, 0, 0, &threadID);

	FD_SET rSet;
	FD_SET wSet;
	FD_SET eSet;

	while (1)
	{
		FD_ZERO(&rSet);
		FD_ZERO(&wSet);
		FD_ZERO(&eSet);

		FD_SET(listenSocket, &rSet);
		FD_SET(listenSocket, &wSet);
		FD_SET(listenSocket, &eSet);

		for (auto& user : userList)
		{
			FD_SET(user.sock, &rSet);
			FD_SET(user.sock, &wSet);
			FD_SET(user.sock, &eSet);
		}

		timeval timeOut;
		timeOut.tv_sec = 0;
		timeOut.tv_usec = 1000;
		{
			int ret = select(0, &rSet, &wSet, &eSet, &timeOut);
			if (ret == SOCKET_ERROR) continue;
			if (ret == 0) continue;
		}

		if (FD_ISSET(listenSocket, &rSet))
		{
			SOCKADDR_IN clientAddr;
			int length = sizeof(clientAddr);
			SOCKET clientSocket = accept(listenSocket, (sockaddr*)&clientAddr, &length);
			if (clientSocket == SOCKET_ERROR)
			{
				closesocket(listenSocket);
				WSACleanup();
				return 1;
			}

			printf("Client connected at IP : %s, Port : %d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

			u_long mode = TRUE;
			ioctlsocket(clientSocket, FIONBIO, &mode);

			User user;
			user.sock = clientSocket;
			user.address = clientAddr;
			userList.push_back(user);
		}

		for (auto iter = userList.begin(); iter != userList.end(); )
		{
			if (FD_ISSET(iter->sock, &rSet))
			{
				const int bufferSize = 256;
				char recvMsg[bufferSize]{ 0, };
				int recvByte = recv(iter->sock, recvMsg, bufferSize, 0);
				if (recvByte == SOCKET_ERROR)
				{
					if (WSAGetLastError() != WSAEWOULDBLOCK)
					{
						printf("Client exit with error. IP : %s, Port : %d\n", inet_ntoa(iter->address.sin_addr), ntohs(iter->address.sin_port));
						closesocket(iter->sock);
						iter = userList.erase(iter);
						continue;
					}
				}
				else if (recvByte == 0)
				{
					printf("Client exit. IP : %s, Port : %d\n", inet_ntoa(iter->address.sin_addr), ntohs(iter->address.sin_port));
					closesocket(iter->sock);
					iter = userList.erase(iter);
					continue;
				}
				else
				{
					printf("%s", recvMsg);
				}

				if (recvByte > 0)
				{
					for (auto sendIter = userList.begin(); sendIter != userList.end();)
					{
						int sendByte = send(sendIter->sock, recvMsg, bufferSize, 0);
						if (sendByte == SOCKET_ERROR)
						{
							if (WSAGetLastError() != WSAEWOULDBLOCK)
							{
								printf("Client exit with error 2. IP : %s, Port : %d\n", inet_ntoa(sendIter->address.sin_addr), ntohs(sendIter->address.sin_port));
								closesocket(sendIter->sock);
								sendIter = userList.erase(sendIter);
								continue;
							}
						}
						++sendIter;
					}
				}
			}
			++iter;
		}
	}

	//CloseHandle(handle);
	closesocket(listenSocket);
	WSACleanup();
}