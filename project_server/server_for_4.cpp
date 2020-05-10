#include <iostream>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
int main()
{
    WSADATA wsaData;
    SOCKET serversocket;
    sockaddr_in socketaddr;//存放本地地址信息

    const char* sendData = "hello i'am server";

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
            socketaddr.sin_port = htons(6001);//htos用来将端口转换成字符，1024以上的数字即可
            socketaddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//htol将主机字节序long型转换为网络字节序

            serversocket = socket(AF_INET, SOCK_STREAM, 0);
            bind(serversocket, (SOCKADDR*)&socketaddr, sizeof(SOCKADDR));

            listen(serversocket, 5);
            int len = sizeof(SOCKADDR);
            while (1) {

                SOCKET responseSocket = accept(serversocket, (SOCKADDR*)&socketaddr, &len);

                send(responseSocket, sendData, strlen(sendData), 0);

                char buff[100] = { 0 };
                recv(responseSocket, buff, sizeof(buff), 0);
                printf("the buff is %s\n", buff);
                printf("success recevice\n");


                closesocket(responseSocket);
            }

            //closesocket(serversocket);
        }
        else {
            printf("cannot resolve the host name\n");
        }

        WSACleanup();

    }
}