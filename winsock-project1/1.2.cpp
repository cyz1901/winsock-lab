#include <iostream>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
int main()
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(1, 1), &wsaData))
    {
        puts("Could not load windows sockets DLL");
        return 0;
    }
    char hostname[256];
    gethostname(hostname, 256);
    strcpy_s(hostname, "DESKTOP-6GOMKPJ");
    hostent* pHostEnt = gethostbyname(hostname);
    if (pHostEnt)
    {
        char* strIPAddress = inet_ntoa(*(in_addr*)pHostEnt->h_addr_list[0]);
        printf("name is %s,ip is %s\n", pHostEnt->h_name, strIPAddress);
       
    }
    else
    {
        printf("cannot resolve the host name\n");
    }
    WSACleanup();

    

}