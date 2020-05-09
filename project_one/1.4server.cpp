#include <iostream>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
int main()
{
    WSADATA wsaData;
    SOCKET serversocket;
    sockaddr_in socketaddr;
    char buff[1000];
    const char* sendData = "你好!客户端!我是服务器";
    if (WSAStartup(MAKEWORD(1, 1), &wsaData))
    {
        puts("Could not load windows sockets DLL");
        return 0;
    }
    DWORD dwIPAddress = inet_addr("127.0.0.1");
    if (dwIPAddress == INADDR_NONE) {
        puts("Invalid Internet Address");
    }
    else {
        hostent* pHostEnt = gethostbyaddr((const char*)&dwIPAddress, 4, AF_INET);
        if (pHostEnt) {
            char* strIPAddress = inet_ntoa(*(in_addr*)pHostEnt->h_addr_list[0]);
            printf("name = %s, ip = %s\n", pHostEnt->h_name, strIPAddress);
            
            socketaddr.sin_family = AF_INET;
            socketaddr.sin_port = (u_short)5050;
            socketaddr.sin_addr = *(in_addr*)pHostEnt->h_addr_list[0];
                
            serversocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            bind(serversocket, (SOCKADDR*)&socketaddr, sizeof(SOCKADDR));
            listen(serversocket,0);
            while (1)
            {
                SOCKET responseSocket;
                int len = sizeof(SOCKADDR);
                responseSocket = accept(serversocket, (SOCKADDR*)&socketaddr,&len);
                int recv_status = recv(serversocket,buff,100,0);
                if (recv_status > 0) {
                    //std::cout << buff;
                    printf("success recevice");

                }
                send(responseSocket, sendData, strlen(sendData), 0);
                closesocket(responseSocket);
            }

            closesocket(serversocket);
        }
        else
        {
            printf("cannot resolve the host name\n");
        }
        WSACleanup();

    }
}