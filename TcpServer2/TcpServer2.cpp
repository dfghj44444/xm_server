// TcpServer2.cpp : �������̨Ӧ�ó������ڵ㡣
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
		printf("�Ѵ��׽���\n");
	}
	else
	{
		//��һ�����׽���
		printf("Ƕ����δ��");
		return 0;
	}

	SOCKET serSocket = socket(AF_INET,SOCK_STREAM,0);//�����˿�ʶ���׽���
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(6000);//�󶨶˿�

	bind(serSocket,(SOCKADDR*)&addr,sizeof(SOCKADDR));//�����
	listen(serSocket,5);//���еڶ������������ܹ��������������

	//��ʼ����
	SOCKADDR_IN clientsocket;

	int len = sizeof(SOCKADDR);
	while (1)
	{	
		SOCKET serConn = accept(serSocket,(SOCKADDR*)&clientsocket,&len);//����accept����connection�Ļ����ͻ᲻�ϼ���
		char sendBuf[100];

		sprintf(sendBuf,"welcome %s to beijing",inet_ntoa(clientsocket.sin_addr));//�ҵ���Ӧip���������ִ�ӡ������
		send(serConn,sendBuf,strlen(sendBuf)+1,0);
		char receiveBuf[100];
		int ret = recv(serConn,receiveBuf,strlen(receiveBuf) + 1,0);
		if (ret != -1)
		{
			printf("%s\n",receiveBuf);
		}
		closesocket(serConn);//�ر�
	}
	WSACleanup();//�ͷ���Դ�Ĳ���

	return 0;
}

