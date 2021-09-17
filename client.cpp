#pragma comment(lib, "Ws2_32.lib")

#include <WinSock2.h>
#include <iostream>
#include <string>

using namespace std;

void main()
{
    string confirm;
    char message[200];

    //開始 Winsock-DLL
    int r;
    WSAData wsaData;
    WORD DLLVersion;
    DLLVersion = MAKEWORD(2, 1);
    r = WSAStartup(DLLVersion, &wsaData);

    //宣告給 socket 使用的 sockadder_in 結構
    SOCKADDR_IN addr;

    int addlen = sizeof(addr);

    //設定 socket
    SOCKET sConnect;

    //AF_INET: internet-family
    //SOCKET_STREAM: connection-oriented socket
    sConnect = socket(AF_INET, SOCK_STREAM, NULL);

    //設定 addr 資料
    addr.sin_addr.s_addr = inet_addr("XXX.X.X.X");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);

    cout << "connect to server?[Y] or [N]" << endl;
    cin >> confirm;

    if (confirm == "N")
    {
        exit(1);
    }
    else {
        if (confirm == "Y")
        {
            connect(sConnect, (SOCKADDR*)&addr, sizeof(addr));

            //接收 server 端的訊息
            ZeroMemory(message, 200);
            r = recv(sConnect, message, sizeof(message), 0);
            cout << message << endl;

            //設定 closesocket 時，不經過 TIME-WAIT 過程,直接關閉socket
            //BOOL bDontLinger = FALSE;
            //setsockopt(sConnect,SOL_SOCKET,SO_DONTLINGER,(const char*)&bDontLinger,sizeof(BOOL));

            //若之後不再使用，可用 closesocket 關閉連線
            closesocket(sConnect);

            getchar();
            getchar();
        }
    }

}
