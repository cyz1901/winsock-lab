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

       
                char filename[] = "myfile.txt"; //指定文件名
                FILE* fp = fopen(filename, "rb"); //"r"表示读， "w"表示写, "b"表示以二进制模式进行操作（比文本模式的读写速度快）, 写入时可用"wb"
                if (fp == NULL)
                {
                    printf("cannot open file\n");
                    return;
                }

                long startPos = ftell(fp); //记录文件起始位置
                fseek(fp, 0, SEEK_END); //文件指针移到文件末尾
                long endPos = ftell(fp); //记录文件末尾位置
                fseek(fp, 0, SEEK_SET); //文件指针重新移动到文件起始位置， 以便从头开始读文件内容
                long fileLen = endPos - startPos; //首尾两个位置相减就是文件的长度

                    //发送辅助信息： 文件名长度， 文件名、 文件长度
                int nameLen = strlen(filename);
                send(clientsocket, (char*)&nameLen, sizeof(int), 0); //发送文件名长度
                send(clientsocket, filename, nameLen, 0); //发送文件名
                send(clientsocket, (char*)&fileLen, sizeof(long), 0); //发送文件长度

                //读取并发送文件内容
                char fileBuf[1024];
                long nReadTotal = 0; //从文件中读取的字节总数
                int nSendTotal = 0; //向接收端发送的字节总数
                while (nReadTotal < fileLen) //当读取的字节数小于文件长度时
                {
                    long nRead = fread(fileBuf, 1024, 1, fp); //从文件中读取 1024 个字节到filebuf 中
                    nReadTotal += nRead;
                    nSendTotal += send(clientsocket, fileBuf, nRead,0); // 把 filebuf 中的内容发送出去
                }






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