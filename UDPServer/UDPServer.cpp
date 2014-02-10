// UDPServer.cpp : 定义控制台应用程序的入口点。
/// UDPClient.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#pragma comment(lib,"ws2_32.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	SOCKET socket1;
	WSADATA wsaData;

	int iErr;
	if ( WSAStartup( MAKEWORD(1,1),&wsaData ) )
	{
		printf("win sock cannot be init");
		WSACleanup();
		return 0 ;
	}

	printf("sevre has been successsfully start");
	sockaddr_in local;
	sockaddr_in from;
	int fromlen = sizeof(from);
	local.sin_addr.s_addr = INADDR_ANY;
	local.sin_family = AF_INET;
	local.sin_port = htons(5566);

	socket1 = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	bind(socket1,(SOCKADDR*)&local,fromlen);

	while (1)
	{
		char buffer[1024] = {0,};

		printf("waiting message from client");

		if (SOCKET_ERROR != recvfrom(socket1,buffer,sizeof(buffer),0,(SOCKADDR*)&from,&fromlen))
		{
			if ( strcmp(buffer,"bye") == 0 )
			{
				printf("client quit!\n");
				break;
			}
		}
		printf("receive message from %s -- %s \n",inet_ntoa(from.sin_addr),buffer);
		sendto(socket1,buffer,sizeof(buffer),0,(SOCKADDR*)&from,fromlen);
	}
	closesocket(socket1);
	WSACleanup();

		return 0;
}

