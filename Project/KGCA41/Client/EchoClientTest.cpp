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

	u_long mode = TRUE;
	ioctlsocket(clientSocket, FIONBIO, &mode);

	while (1)
	{
		const int bufferSize = 256;
		{
			char sendMsg[bufferSize]{ 0, };
			printf("%s", "Send : ");
			fgets(sendMsg, bufferSize, stdin);

			int sendByte = send(clientSocket, sendMsg, bufferSize, 0);
			if (sendByte == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK)
				{
					closesocket(clientSocket);
					WSACleanup();
					return 1;
				}
				continue;
			}
		}

		{
			char recvMsg[bufferSize]{ 0, };
			int recvByte = recv(clientSocket, recvMsg, bufferSize, 0);
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
	}

	closesocket(clientSocket);
	WSACleanup();
}
