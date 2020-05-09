// winsock-project1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
int main()
{
    WORD wVersionRequested = MAKEWORD(2, 0);
    WSADATA wsaData;
    int error = WSAStartup(wVersionRequested, &wsaData);
    if (error)
    {
        puts("Could not load windows sockets DLL");
        return 0;
    }
    else
    {
        puts("WSASstartup succeeded");
    }

    if (LOBYTE(wsaData.wVersion)!=1 || HIBYTE(wsaData.wVersion)!=1)
    {
        printf("%d", LOBYTE(wsaData.wVersion));
        printf("%d", LOBYTE(wsaData.wHighVersion));
        puts("Winsock 函数库不支持你要的版本！");
        WSACleanup();
        return 0;
    }
    puts("Load windows sockets DLL 1.1 succeeded!");
    WSACleanup();
    puts("ULoad windows sockets DLL 1.1 succeeded!");

    //下面是自己添加的代码
    printf("The vision is %d.%d\n", LOBYTE(wsaData.wVersion), HIBYTE(wsaData.wVersion));
    printf("The high vision is %d.%d\n", LOBYTE(wsaData.wHighVersion), HIBYTE(wsaData.wHighVersion));

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
