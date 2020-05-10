#include <iostream>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

int main()
{
    // 以下的几句都是固定的
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

    wVersionRequested = MAKEWORD(1, 1);

    err = WSAStartup(wVersionRequested, &wsaData);//该函数的功能是加载一个Winsocket库版本
    if (err != 0) {
        return 0;
    }


    if (LOBYTE(wsaData.wVersion) != 1 ||
        HIBYTE(wsaData.wVersion) != 1) {
        WSACleanup();
        return 0;
    }


    //真正socket编程部分
    SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);//面向连接的可靠性服务SOCK_STRAM

    SOCKADDR_IN addrSrv;//存放本地地址信息的
    addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//htol将主机字节序long型转换为网络字节序
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(6001);//htos用来将端口转换成字符，1024以上的数字即可

    bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));//将socket绑定到相应地址和端口上

    listen(sockSrv, 5);//等待队列中的最大长度为5

    SOCKADDR_IN addrClient;
    int len = sizeof(SOCKADDR);

    while (1)
    {
        SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len);//建立一个新的套接字用于通信，不是前面的监听套接字
        char sendBuf[100];
        sprintf_s(sendBuf, "Server IP is:%s",inet_ntoa(addrClient.sin_addr));//inet_nota函数是将字符转换成ip地址
        send(sockConn, sendBuf, strlen(sendBuf) + 1, 0);//服务器向客户端发送数据

        char recvBuf[100];
        recv(sockConn, recvBuf, 100, 0);//服务器从客户端接受数据
        printf("%s\n", recvBuf);
        closesocket(sockConn);//关闭socket
    }
}