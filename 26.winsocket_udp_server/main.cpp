#include <iostream>
#include <windows.h>
#include <winsock.h>

using namespace std;
 int main() {

     cout<<"\t\t........UDP Server......."<<endl;
     cout<<endl;

     WSADATA WinSockData;
     int iWsaStartUp;
     int iWsaCleanUp;

     SOCKET UDPSocketServer;
     struct  sockaddr_in UDPClient;

     const int BUFFER_SIZE = 512;
     char Buffer[BUFFER_SIZE];
     int iBufferLen = BUFFER_SIZE;
     cout<<"iBufferLen: "<<iBufferLen<<endl;
     int iBind;
     int iReceiveFrom;

     int iUDPClientLen = sizeof(UDPClient);
     int iCloseSocket;

     //Step - 1 Initialization of Winsock

        iWsaStartUp = WSAStartup(MAKEWORD(2,2),&WinSockData);

        iWsaStartUp != 0 ? 
        (
                cout<<"WSAStartup Fun Failed & Error No ->"<<GetLastError()<<endl
        ) : (
                cout<<"WSAStartup Fun Success! "<<endl
        );

    // Step - 2 Fill the UDPClient(Socket ADDRESS) Structure

        UDPClient.sin_family = AF_INET;
        UDPClient.sin_addr.s_addr = inet_addr("127.0.0.1");
        UDPClient.sin_port = htons(8001);

    // Step - 3 Socket creation

        UDPSocketServer = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);

        UDPSocketServer == INVALID_SOCKET ? 
            (
                    cout<<"Socket Creation Failed & Error No ->"<<GetLastError()<<endl
            ) : (
                    cout<<"Socket Creation Success!"<<endl
            );
    // Step - 4 Bind Server

        iBind = bind(
            UDPSocketServer,
            (SOCKADDR*)&UDPClient,
            sizeof(UDPClient)
        );

        iBind == SOCKET_ERROR ? 
            (
                cout<<"Binding Failed & Error No ->"<<GetLastError()<<endl
            ) : (
                cout<<"Binding Success!"<<endl
            );

     // Step - 5 RecvFrom Fun from    

     iReceiveFrom = recvfrom(
         UDPSocketServer,
         Buffer,
         iBufferLen,
         MSG_PEEK,
         (SOCKADDR*)&UDPClient,
         &iUDPClientLen
     );

     iReceiveFrom == SOCKET_ERROR ? 
            (
                cout<<"Receiving Failed & Error No ->"<<WSAGetLastError()<<endl
            ) : (
                cout<<"Receiving Success!"<<endl
            );

     cout<<"Received Data ->"<<Buffer<<endl;       

    // Step - 6 Close Socket function

        iCloseSocket = closesocket(UDPSocketServer);

        iCloseSocket == SOCKET_ERROR ? 
            (
                cout<<"Socket Closing Failed & Error No ->"<<WSAGetLastError()<<endl
            ) : (
                cout<<"Socket Closing Success!"<<endl
            );  

    // Step - 7 WSACleanup fun for terminating from dll

        iWsaCleanUp = WSACleanup();

        iWsaCleanUp == SOCKET_ERROR ? 
            (
                cout<<"WSA Cleanup Failed & Error No ->"<<WSAGetLastError()<<endl
            ) : (
                cout<<"WSA Cleanup Success!"<<endl
            );  
            system("pause");
 }

 //cd "d:\Programing\Git\C++_System\26.winsocket_udp\" && g++ main.cpp -o main            -->  -lws2_32 <--        && "d:\Programing\Git\C++_System\26.winsocket_udp\"main