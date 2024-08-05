#include <stdio.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32")

#define PORT 33333
#define PACKET_SIZE 4096

int main()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET hSocket;
	hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN tAddr = {};
	tAddr.sin_family = AF_INET;
	tAddr.sin_port = htons(PORT);
	PCWSTR ipAddr = L"127.0.0.1";
	InetPton(AF_INET,ipAddr,&tAddr.sin_addr.s_addr);

	connect(hSocket, (SOCKADDR*)&tAddr, sizeof(tAddr));
	
	while (true) {
		char cMsg[1024];
		scanf_s("%s", cMsg, (unsigned)_countof(cMsg)); // Correct use of scanf_s

		send(hSocket, cMsg, strlen(cMsg), 0);

		char cBuffer[PACKET_SIZE] = {};
		recv(hSocket, cBuffer, PACKET_SIZE, 0);
		printf("Recv Msg : %s\n", cBuffer);
	}

	

	closesocket(hSocket);

	WSACleanup();
	return 0;
}