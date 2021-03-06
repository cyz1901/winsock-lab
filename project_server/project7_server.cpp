
/*************************************************************************
  > File Name: Win_Server.c
  > Author: SongLee
 ************************************************************************/

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <WinSock2.h> 
#include <fstream>
using namespace std;


 //#define PORT 8082 
#define PORT 1029   //需要更改你可用的端口
#define SERVER_IP "127.0.0.1" 
#define BUFFER_SIZE 1024 
#define FILE_NAME_MAX_SIZE 512 
#pragma comment(lib, "WS2_32") 

int main()
{
    // 声明并初始化一个服务端(本地)的地址结构 
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.S_un.S_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // 初始化socket dll 
    WSADATA wsaData;
    WORD socketVersion = MAKEWORD(2, 0);
    if (WSAStartup(socketVersion, &wsaData) != 0)
    {
        printf("Init socket dll error!");
        exit(1);
    }

    // 创建socket 
    SOCKET m_Socket = socket(AF_INET, SOCK_STREAM, 0);
    if (SOCKET_ERROR == m_Socket)
    {
        printf("Create Socket Error!");
        exit(1);
    }

    //绑定socket和服务端(本地)地址 
    if (SOCKET_ERROR == bind(m_Socket, (LPSOCKADDR)&server_addr, sizeof(server_addr)))
    {
        printf("Server Bind Failed: %d", WSAGetLastError());
        exit(1);
    }

    //监听 
    if (SOCKET_ERROR == listen(m_Socket, 10))
    {
        printf("Server Listen Failed: %d", WSAGetLastError());
        exit(1);
    }

    ofstream rfile;
    while (1)
    {
        printf("Listening To Server...\n");    //监听服务器需求

        sockaddr_in client_addr;
        int client_addr_len = sizeof(client_addr);

        SOCKET m_New_Socket = accept(m_Socket, (sockaddr*)&client_addr, &client_addr_len);
        if (SOCKET_ERROR == m_New_Socket)
        {
            printf("Server Accept Failed: %d", WSAGetLastError());
            break;
        }

        char buffer[BUFFER_SIZE];
        memset(buffer, 0, BUFFER_SIZE);


        char file_name[FILE_NAME_MAX_SIZE + 1];
        memset(file_name, 0, FILE_NAME_MAX_SIZE + 1);
        printf("%s\n", file_name);
        /*
        FILE* fp = fopen("D:\\happy.txt", "wb"); //windows下是"rb",表示打开一个只读的二进制文件 
        if (NULL == fp)
        {
            printf("File: %s Not Found\n", file_name);
        }
        else
        {
            memset(buffer, 0, BUFFER_SIZE);
            int length = 10;


            while (recv(m_New_Socket, buffer, BUFFER_SIZE, 0))
            {

                if (fwrite(buffer, sizeof(char), BUFFER_SIZE, fp) < BUFFER_SIZE or buffer == NULL)
                {
                    printf("Send File: %s Failed\n", file_name);
                    break;
                }
                printf("write\n");
                memset(buffer, 0, BUFFER_SIZE);
            }
            printf("write finally\n");
            fclose(fp);

        }
        */


        rfile.open("happy.txt", ios::binary);
        int redlen = recv(m_New_Socket, buffer, BUFFER_SIZE, 0);
        if (redlen == -1)
        {
            rfile.close();
            closesocket(m_New_Socket);
            printf("over\n");
            break;
        }
        rfile.write(buffer,redlen);
        printf("recv is %s the len is %d\n", buffer,redlen);



        closesocket(m_New_Socket);

    }
    rfile.close();
    closesocket(m_Socket);
    //释放winsock库 
    WSACleanup();
    return 0;
}
