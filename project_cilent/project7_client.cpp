
/*************************************************************************
  > File Name: Win_Client.c
  > Author: SongLee
 ************************************************************************/

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <WinSock2.h> 
#include <fstream>
using namespace std;

 //#define PORT 8082 
#define PORT 1029    //需要更改你可用的端口
#define SERVER_IP "127.0.0.1" 
#define BUFFER_SIZE 1024 
#define FILE_NAME_MAX_SIZE 512
#pragma comment(lib, "WS2_32") 

int main()
{
	// 初始化socket dll 
	WSADATA wsaData;
	WORD socketVersion = MAKEWORD(2, 0);
	if (WSAStartup(socketVersion, &wsaData) != 0)
	{
		printf("Init socket dll error!");
		exit(1);
	}

	while (1) {
		//创建socket 
		SOCKET c_Socket = socket(AF_INET, SOCK_STREAM, 0);
		if (SOCKET_ERROR == c_Socket)
		{
			printf("Create Socket Error!");
			system("pause");
			exit(1);
		}

		//指定服务端的地址 
		sockaddr_in server_addr;
		server_addr.sin_family = AF_INET;
		server_addr.sin_addr.S_un.S_addr = inet_addr(SERVER_IP);
		server_addr.sin_port = htons(PORT);

		if (SOCKET_ERROR == connect(c_Socket, (LPSOCKADDR)&server_addr, sizeof(server_addr)))
		{
			printf("Can Not Connect To Client IP!\n");
			system("pause");
			exit(1);
		}
		//输入文件名 
		char file_name[FILE_NAME_MAX_SIZE + 1];
		memset(file_name, 0, FILE_NAME_MAX_SIZE + 1);
		printf("Please Input File Name On Client: ");

		scanf("%s", &file_name);

		char buffer[BUFFER_SIZE];
		memset(buffer, 0, BUFFER_SIZE);





		ifstream rfile;
		rfile.open(file_name);
		rfile >> buffer;
		send(c_Socket, buffer, 100, 0);

		printf("send %s \n",buffer);
		closesocket(c_Socket);
	}

	//释放winsock库 
	WSACleanup();

	system("pause");
	return 0;
}
