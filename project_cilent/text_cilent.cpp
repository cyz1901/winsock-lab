#include <iostream>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

int main()
{
    //�̶���ʽ
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

    //����ͨѶsocket
    SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);

    SOCKADDR_IN addrSrv;
    addrSrv.sin_addr.S_un.S_addr = inet_addr("192.168.1.105");//�趨��Ҫ���ӵķ�������ip��ַ
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(6001);//�趨��Ҫ���ӵķ������Ķ˿ڵ�ַ
    connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));//���������������

    //����������ʦ����Ϣ
    char recvBuf[100];
    recv(sockClient, recvBuf, 100, 0);
    printf("������ʦ����Ϣ��\n%s\n", recvBuf);

    //������Ϣ����ʦ
    send(sockClient, "������С�� ѧ�ţ�123456789��IP��ַ��192.168.1.14!", strlen("������С�� ѧ�ţ�123456789��IP��ַ��192.168.1.14!") + 1, 0);

    closesocket(sockClient);
    WSACleanup();
}