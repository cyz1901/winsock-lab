#include <iostream>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
int main()
{
    WSADATA wsaData;
    SOCKET clientsocket;
    sockaddr_in socketaddr;
    char buff[1000];
    const char* sendData = "你好!服务端!我是客户端";
    //定义信息结构体
    typedef struct USERINFO {
        int id;
        char name[30];
        int classe;
        int age;
        char hobby[100];
    };

    USERINFO usreInfo;


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

            clientsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            if (connect(clientsocket, (SOCKADDR*)&socketaddr, sizeof(socketaddr)) == SOCKET_ERROR) {
                printf("connect fail \n");
            }
            
            while (1)
            {   
                int len = sizeof(SOCKADDR);
                //gets_s(buff);
                std::cout << "你的班级是? \n";
                std::cin >> usreInfo.classe;
                std::cout << "你的学号是? \n";
                std::cin >> usreInfo.id;
                std::cout << "你的姓名是? \n";
                std::cin >> usreInfo.name;
                std::cout << "你的年龄是? \n";
                std::cin >> usreInfo.age;
                std::cout << "你的爱好是? \n";
                std::cin >> usreInfo.hobby;
                //scanf_s("班级：%d 学号：%d 姓名：%s 年龄：%d 爱好：%s \n", usreInfo.classe, usreInfo.id, usreInfo.name, usreInfo.age, usreInfo.hobby);

                memset(buff, 0, 1024);
                memcpy(buff, &usreInfo, sizeof(USERINFO));
                send(clientsocket, buff, strlen(sendData), 0);

          
                int recv_status = recv(clientsocket, buff, sizeof(long), 0); //接收文件长度


                
                if (recv_status > 0) {
                    printf("success recevice");
                }

                
            }

            closesocket(clientsocket);
        }
        else
        {
            printf("cannot resolve the host name\n");
        }
        WSACleanup();

    }
}