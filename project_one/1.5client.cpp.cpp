#include <iostream>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
int main()
{
    WSADATA wsaData;
    SOCKET clientsocket;
    sockaddr_in socketaddr;
    char buff[1000];
    const char* sendData = "���!�����!���ǿͻ���";


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

       
                char filename[] = "myfile.txt"; //ָ���ļ���
                FILE* fp = fopen(filename, "rb"); //"r"��ʾ���� "w"��ʾд, "b"��ʾ�Զ�����ģʽ���в��������ı�ģʽ�Ķ�д�ٶȿ죩, д��ʱ����"wb"
                if (fp == NULL)
                {
                    printf("cannot open file\n");
                    return;
                }

                long startPos = ftell(fp); //��¼�ļ���ʼλ��
                fseek(fp, 0, SEEK_END); //�ļ�ָ���Ƶ��ļ�ĩβ
                long endPos = ftell(fp); //��¼�ļ�ĩβλ��
                fseek(fp, 0, SEEK_SET); //�ļ�ָ�������ƶ����ļ���ʼλ�ã� �Ա��ͷ��ʼ���ļ�����
                long fileLen = endPos - startPos; //��β����λ����������ļ��ĳ���

                    //���͸�����Ϣ�� �ļ������ȣ� �ļ����� �ļ�����
                int nameLen = strlen(filename);
                send(clientsocket, (char*)&nameLen, sizeof(int), 0); //�����ļ�������
                send(clientsocket, filename, nameLen, 0); //�����ļ���
                send(clientsocket, (char*)&fileLen, sizeof(long), 0); //�����ļ�����

                //��ȡ�������ļ�����
                char fileBuf[1024];
                long nReadTotal = 0; //���ļ��ж�ȡ���ֽ�����
                int nSendTotal = 0; //����ն˷��͵��ֽ�����
                while (nReadTotal < fileLen) //����ȡ���ֽ���С���ļ�����ʱ
                {
                    long nRead = fread(fileBuf, 1024, 1, fp); //���ļ��ж�ȡ 1024 ���ֽڵ�filebuf ��
                    nReadTotal += nRead;
                    nSendTotal += send(clientsocket, fileBuf, nRead,0); // �� filebuf �е����ݷ��ͳ�ȥ
                }






                int recv_status = recv(clientsocket, buff, sizeof(long), 0); //�����ļ�����



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