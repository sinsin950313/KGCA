#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment (lib, "ws2_32.lib")

#include <WinSock2.h>
#include <iostream>

DWORD WINAPI ClientThread(LPVOID lpThreadParameter)
{
	SOCKET sock = (SOCKET)lpThreadParameter;
	while (1)
	{
		char sendMsg[256]{ 0, };
		printf("%s", "Send : ");
		fgets(sendMsg, 256, stdin);

		if (strcmp(sendMsg, "exit\n") == 0)
		{
			break;
		}

		int sendByte = send(sock, sendMsg, strlen(sendMsg), 0);
		if (sendByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				closesocket(sock);
				return 1;
			}
		}
	}
	closesocket(sock);
}

int main()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return 0;
	}

	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN sa;
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr("192.168.0.126");
	sa.sin_port = htons(10000);
	{
		int ret = connect(clientSocket, (sockaddr*)&sa, sizeof(sa));
		if (ret == SOCKET_ERROR)
		{
			printf("%d", WSAGetLastError());
			WSACleanup();
			return 1;
		}
	}

	DWORD threadID;
	HANDLE handle = CreateThread(0, 0, ClientThread, (LPVOID)clientSocket, 0, &threadID);

	u_long mode = TRUE;
	ioctlsocket(clientSocket, FIONBIO, &mode);

	while (1)
	{
		char recvMsg[256]{ 0, };
		int recvByte = recv(clientSocket, recvMsg, 256, 0);
		if (recvByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				closesocket(clientSocket);
				WSACleanup();
				return 1;
			}
			continue;
		}

		printf("Recv : %s", recvMsg);
	}

	closesocket(clientSocket);
	WSACleanup();
}
