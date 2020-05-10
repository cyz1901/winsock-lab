#include <iostream>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

int main()
{
    //固定格式
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

    wVersionRequested = MAKEWORD(1, 1);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        return 0;
    }


    if (LOBYTE(wsaData.wVersion) != 1 ||
        HIBYTE(wsaData.wVersion) != 1) {
        WSACleanup();
        return 0;
    }

    //建立通讯socket
    SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);

    SOCKADDR_IN addrSrv;
    addrSrv.sin_addr.S_un.S_addr = inet_addr("192.168.1.105");//设定需要连接的服务器的ip地址
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(6001);//设定需要连接的服务器的端口地址
    connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));//与服务器进行连接

    //接受来自老师的信息
    char recvBuf[100];
    recv(sockClient, recvBuf, 100, 0);
    printf("来自老师的信息：\n%s\n", recvBuf);

    //发送信息给老师
    send(sockClient, "姓名：小明 学号：123456789，IP地址：192.168.1.14!", strlen("姓名：小明 学号：123456789，IP地址：192.168.1.14!") + 1, 0);

    closesocket(sockClient);
    WSACleanup();
}