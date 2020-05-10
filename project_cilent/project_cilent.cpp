#include <iostream>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
int main()
{
    WSADATA wsaData;
    SOCKET clientsocket;//建立通讯socket
    sockaddr_in socketaddr;
    char buff[1000] = {0};
    const char* sendData = "hello i'am cilent";




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
            //socketaddr.sin_port = (u_short)8080;
            socketaddr.sin_port = htons(6001);//设定需要连接的服务器的端口地址
            //socketaddr.sin_addr = *(in_addr*)pHostEnt->h_addr_list[0];
            socketaddr.sin_addr.S_un.S_addr = inet_addr("192.168.1.105");

            clientsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            if (connect(clientsocket, (SOCKADDR*)&socketaddr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
                //connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR))
                printf("connect fail \n");
            }


                //int len = sizeof(SOCKADDR);

                //gets_s(buff);
                //std::cout << "你的班级是? \n";
                //std::cin >> buff;
                
                //int recv_status = recv(clientsocket, buff, sizeof(buff), 0); //接收文件长度
                /*
                if (recv(clientsocket, buff, sizeof(buff), 0) > 0) {
                    printf("success recevice\n");
                    printf("%s\n",buff);
                    

                }
                */
            recv(clientsocket, buff, sizeof(buff), 0);
            printf("client recv buff is %s\n", buff);

                
            send(clientsocket, sendData, strlen(sendData)+1, 0);
            printf("already send\n");
            closesocket(clientsocket);




        }
        else
        {
            printf("cannot resolve the host name\n");
        }
        WSACleanup();

    }
}