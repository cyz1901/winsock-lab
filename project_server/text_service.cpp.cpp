#include <iostream>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

int main()
{
    // ���µļ��䶼�ǹ̶���
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

    wVersionRequested = MAKEWORD(1, 1);

    err = WSAStartup(wVersionRequested, &wsaData);//�ú����Ĺ����Ǽ���һ��Winsocket��汾
    if (err != 0) {
        return 0;
    }


    if (LOBYTE(wsaData.wVersion) != 1 ||
        HIBYTE(wsaData.wVersion) != 1) {
        WSACleanup();
        return 0;
    }


    //����socket��̲���
    SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);//�������ӵĿɿ��Է���SOCK_STRAM

    SOCKADDR_IN addrSrv;//��ű��ص�ַ��Ϣ��
    addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//htol�������ֽ���long��ת��Ϊ�����ֽ���
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(6001);//htos�������˿�ת�����ַ���1024���ϵ����ּ���

    bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));//��socket�󶨵���Ӧ��ַ�Ͷ˿���

    listen(sockSrv, 5);//�ȴ������е���󳤶�Ϊ5

    SOCKADDR_IN addrClient;
    int len = sizeof(SOCKADDR);

    while (1)
    {
        SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len);//����һ���µ��׽�������ͨ�ţ�����ǰ��ļ����׽���
        char sendBuf[100];
        sprintf_s(sendBuf, "Server IP is:%s",inet_ntoa(addrClient.sin_addr));//inet_nota�����ǽ��ַ�ת����ip��ַ
        send(sockConn, sendBuf, strlen(sendBuf) + 1, 0);//��������ͻ��˷�������

        char recvBuf[100];
        recv(sockConn, recvBuf, 100, 0);//�������ӿͻ��˽�������
        printf("%s\n", recvBuf);
        closesocket(sockConn);//�ر�socket
    }
}