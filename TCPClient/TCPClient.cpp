// Client.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#pragma comment(lib,"ws2_32.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	int err;
	WORD versionRequired;
	WSADATA wsaData;
	versionRequired = MAKEWORD(1,1);
	err = WSAStartup(versionRequired,&wsaData);//Э���İ汾��Ϣ

	if (!err)
	{
		printf("�ͻ���Ƕ�����Ѵ�\n");
	}
	else
	{
		printf("�ͻ���Ƕ���ִ�ʧ��\n");
		return 0;//end
	}
	
	SOCKET clientSocket = socket(AF_INET,SOCK_STREAM,0);
	SOCKADDR_IN clientsock_in;
	clientsock_in.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	clientsock_in.sin_family = AF_INET;
	clientsock_in.sin_port = htons(6000);
	connect(clientSocket,(SOCKADDR*)&clientsock_in,sizeof(SOCKADDR));//��ʼ����

	char receiveBuf[100];
	recv(clientSocket,receiveBuf,101,0);
	printf("%s\n",receiveBuf);

	send(clientSocket,"Hello,this is client",strlen("Hello,this is client")+1,0);
	closesocket(clientSocket);
	WSACleanup();

	return 0;
}

