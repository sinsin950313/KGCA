#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment (lib, "ws2_32.lib")

#include <WinSock2.h>
#include <iostream>

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

	while (1)
	{
		const int bufferSize = 256;
		char recvMsg[bufferSize]{ 0, };
		int recvByte = recv(clientSocket, recvMsg, bufferSize, 0);
		if (recvByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				closesocket(clientSocket);
				closesocket(listenSocket);
				WSACleanup();
				return 1;
			}
			continue;
		}
		else if (recvByte == 0)
		{
			printf("Client exit. IP : %s, Port : %d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
			closesocket(clientSocket);
			break;
		}
		else
		{
			printf("%s", recvMsg);
		}

		if (recvByte > 0)
		{
			int sendByte = send(clientSocket, recvMsg, bufferSize, 0);
			if (sendByte == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK)
				{
					closesocket(clientSocket);
					break;
				}
			}
		}
	}

	closesocket(listenSocket);
	WSACleanup();
}