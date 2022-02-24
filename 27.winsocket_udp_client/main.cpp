#include <iostream>
#include <windows.h>
#include <winsock.h>

using namespace std;


 int main() {

     cout<<"\t\t........UDP Client......."<<endl;
     cout<<endl;

     WSADATA WinSockData;
     int iWsaStartUp;
     int iWsaCleanUp;

     SOCKET UDPSocketClient;
     struct  sockaddr_in UDPServer;

     const int BUFFER_SIZE = 512;
     char Buffer[BUFFER_SIZE] = "Hello from Client!";
     int iSendto;

     int iBufferLen = BUFFER_SIZE;
     int iUDPServerLen = sizeof(UDPServer);
     int iCloseSocket;

     //Step - 1 Initialization of Winsock

        iWsaStartUp = WSAStartup(MAKEWORD(2,2),&WinSockData);

        iWsaStartUp != 0 ? 
        (
                cout<<"WSAStartup Fun Failed & Error No ->"<<iWsaStartUp<<endl
        ) : (
                cout<<"WSAStartup Fun Success! "<<endl
        );

    // Step - 2 Fill the UDPServer(Socket ADDRESS) Structure

        UDPServer.sin_family = AF_INET;
        UDPServer.sin_addr.s_addr = inet_addr("127.0.0.1");
        UDPServer.sin_port = htons(8001);

    // Step - 3 Socket creation

        UDPSocketClient = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);

        UDPSocketClient == INVALID_SOCKET ? 
            (
                    cout<<"Socket Creation Failed & Error No ->"<<WSAGetLastError()<<endl
            ) : (
                    cout<<"Socket Creation Success!"<<endl
            );
    // Step - 4 Send to function

        iSendto = sendto(
            UDPSocketClient,
            Buffer,
            iBufferLen,
            MSG_DONTROUTE,
            (SOCKADDR*)&UDPServer,
            sizeof(UDPServer)
        );

        iSendto == SOCKET_ERROR ? 
            (
                    cout<<"Sending data Failed & Error No ->"<<WSAGetLastError()<<endl
            ) : (
                    cout<<"Sending data Success!"<<endl
            );

        cout<<"Sending Data Success"<<endl;    

    // Step - 5 Close Socket function

        iCloseSocket = closesocket(UDPSocketClient);

        iCloseSocket == SOCKET_ERROR ? 
            (
                cout<<"Socket Closing Failed & Error No ->"<<WSAGetLastError()<<endl
            ) : (
                cout<<"Socket Closing Success!"<<endl
            );  

    // Step - 6 WSACleanup fun for terminating from dll

        iWsaCleanUp = WSACleanup();

        iWsaCleanUp == SOCKET_ERROR ? 
            (
                cout<<"WSA Cleanup Failed & Error No ->"<<WSAGetLastError()<<endl
            ) : (
                cout<<"WSA Cleanup Success!"<<endl
            ); 
                        
    system("pause"); 
 }

 //cd "d:\Programing\Git\C++_System\27.winsocket_udp_client\" && g++ main.cpp -o main  -lws2_32   && "d:\Programing\Git\C++_System\27.winsocket_udp_client\"main