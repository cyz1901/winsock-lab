#include <iostream>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
int main()
{
    WSADATA wsaData;
    SOCKET clientsocket;
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

            clientsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            if (connect(clientsocket, (SOCKADDR*)&socketaddr, sizeof(socketaddr)) == SOCKET_ERROR) {
                printf("connect fail \n");
            }
            
            while (1)
            {
                int len = sizeof(SOCKADDR);
                gets_s(buff);
                send(clientsocket, sendData, strlen(sendData), 0);

                int nameLen;
                recv(clientsocket, (char*)&nameLen, sizeof(int), 0); //接收文件名长度
                char name[256];
                recv(clientsocket, name, nameLen, 0); //接收文件名
                name[nameLen] = 0;
                char filename[256] = "received "; //加入文件名前缀"received "
                strcat(filename, name);
                long fileLen;
                int recv_status = recv(clientsocket, (char*)&fileLen, sizeof(long), 0); //接收文件长度


                
                if (recv_status > 0) {
                    printf("success recevice");
                }

                FILE* fp = fopen(filename, "wb");//”r”表示读， ”w”表示写,”b”表示以二进制模式进行操作
                if (fp == NULL){
                    printf("cannot open file\n");
                    return;
                }
                char fileBuf[1024];
                int nRecvTotal = 0; //接收到的字节总数
                long nWriteTotal = 0; //写入文件的字节总数
                while (nRecvTotal < fileLen){
                    int nRecv = recv(clientsocket, fileBuf, 1024, 0); //接收数据到 filebuf中
                    nWriteTotal += fwrite(fileBuf, nRecv, 1, fp); //把 filebuf 中的数据写入文件
                    nRecvTotal += nRecv;
                } 
                printf("file %s, received %d bytes, written %d bytes\n",filename,nRecvTotal,nWriteTotal);
                //关闭文件
                fclose(fp);
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