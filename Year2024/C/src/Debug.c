#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

int main(void)
{
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        puts( "WSAStartup failed.\n");
        exit(1);
    }

    if (LOBYTE(wsaData.wVersion) != 2 ||
        HIBYTE(wsaData.wVersion) != 2)
    {
        puts("Version 2.2 of Winsock is not available.\n");
        WSACleanup();
        exit(2);
    }

    puts("SUCCESS!");
}
