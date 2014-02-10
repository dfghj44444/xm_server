// UDPClient.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#pragma comment(lib,"ws2_32.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	SOCKET socket1;
	WSADATA wsaData;

	if ( WSAStartup( MAKEWORD(1,1),&wsaData ) )
	{
		printf("win sock cannot be init");
		WSACleanup();
		return 0 ;
	}

	printf("client has been successfully start");
	sockaddr_in server;
	int len = sizeof(server);

	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(5566);

	socket1 = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	while (1)
	{
		char buffer[1024] = {0,};
		printf("input message:");
		scanf("%s",buffer);
		if (strcmp(buffer,"bye") == 0)
		{
			sendto(socket1,"bye",3*sizeof(char),0,(SOCKADDR*)&server,len);
			printf("exit!\n");
			Sleep(100);
			closesocket(socket1);
			break;
		}

		if (SOCKET_ERROR != sendto(socket1,buffer,sizeof(buffer),0,(SOCKADDR*)&server,len))
		{
			Sleep(100);
			if (SOCKET_ERROR!= recvfrom(socket1,buffer,sizeof(buffer),0,(SOCKADDR*)&server,&len))
			{
				printf("receive from server:%S \n",buffer);
			}
		}
	}
	closesocket(socket1);

	return 0;
}

