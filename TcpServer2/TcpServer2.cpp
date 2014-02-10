// TcpServer2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#pragma comment(lib,"ws2_32.lib")


int _tmain(int argc, _TCHAR* argv[])
{
	WORD myVersionRequest;
	WSADATA wsaData;
	myVersionRequest = MAKEWORD(1,1);
	int err;
	err = WSAStartup(myVersionRequest,&wsaData);
	if (!err)
	{
		printf("已打开套接字\n");
	}
	else
	{
		//进一步绑定套接字
		printf("嵌套字未打开");
		return 0;
	}

	SOCKET serSocket = socket(AF_INET,SOCK_STREAM,0);//创建了可识别套接字
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(6000);//绑定端口

	bind(serSocket,(SOCKADDR*)&addr,sizeof(SOCKADDR));//绑定完成
	listen(serSocket,5);//其中第二个参数代表能够接收最多连接数

	//开始监听
	SOCKADDR_IN clientsocket;

	int len = sizeof(SOCKADDR);
	while (1)
	{	
		SOCKET serConn = accept(serSocket,(SOCKADDR*)&clientsocket,&len);//若非accept而是connection的话，就会不断监听
		char sendBuf[100];

		sprintf(sendBuf,"welcome %s to beijing",inet_ntoa(clientsocket.sin_addr));//找到对应ip并将这行字打印到那里
		send(serConn,sendBuf,strlen(sendBuf)+1,0);
		char receiveBuf[100];
		int ret = recv(serConn,receiveBuf,strlen(receiveBuf) + 1,0);
		if (ret != -1)
		{
			printf("%s\n",receiveBuf);
		}
		closesocket(serConn);//关闭
	}
	WSACleanup();//释放资源的操作

	return 0;
}

