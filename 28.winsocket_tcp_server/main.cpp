#include <winsock2.h>
#include <iostream>

using namespace std;

int main() {
        cout<<"\t\t-----------TCP Server-----------"<<endl;
        cout<<endl;

        //Local Variable

        WSADATA WinSockData;
        int iWsaStartup;
        int iWsaCleanUp;

        SOCKET TCPServerSocket;
        int iCLoseSocket;

        struct sockaddr_in TCPServerAdd;
        struct sockaddr_in TCPClientAdd;
        int iTCPClientAdd = sizeof(TCPClientAdd);

        int iBind;

        int iListen;

        SOCKET sAcceptSocket;

        const int BUFFER_SIZE = 512;

        int iSend;
        char SendBuffer[BUFFER_SIZE] = "Hello from Server!";
        int iSenderBuffer = BUFFER_SIZE;

        int iRecv;
        char RecvBuffer[BUFFER_SIZE];
        int iRecvBuffer = BUFFER_SIZE;

        // Step - 1 Start Up WSA function

                iWsaStartup = WSAStartup(MAKEWORD(2,2),&WinSockData);

                iWsaStartup != 0 ? (
                        cout<<"WSAStartup Failed"<<endl
                ) : (
                        cout<<"WSAStartup Success!"<<endl
                );

        // Step - 2 Fill the Structure

                TCPServerAdd.sin_family = AF_INET;
                TCPServerAdd.sin_addr.s_addr = inet_addr("127.0.0.1");
                TCPServerAdd.sin_port = htons(8002);

        // Step - 3 Create Socket 

                TCPServerSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

                TCPServerSocket == INVALID_SOCKET ? (
                        cout<<"Server Socket Creation Failed"<< WSAGetLastError()<<endl
                ) : (
                        cout<<"Server Socket Creation Success!"<<endl
                );

        // Step - 4 Bind function

                iBind = bind(
                        TCPServerSocket,
                        (SOCKADDR*)&TCPServerAdd,
                        sizeof(TCPServerAdd)
                        );

                iBind == SOCKET_ERROR ? (
                        cout<<"Binding Failed & Error No ->"<< WSAGetLastError()<<endl
                ) : (
                        cout<<"Binding Success!"<<endl
                );
    
        // Step - 5 Listen function

                iListen = listen(TCPServerSocket,2);

                iListen == SOCKET_ERROR ? (
                        cout<<"Listen fun Failed & Error No ->"<< WSAGetLastError()<<endl
                ) : (
                        cout<<"Listen fun Success!"<<endl
                );

        // Step - 6 Accept

                sAcceptSocket = accept(TCPServerSocket,(SOCKADDR*)&TCPClientAdd,&iTCPClientAdd);

                sAcceptSocket == INVALID_SOCKET ? (
                        cout<<"Accept Failed & Error No ->"<< WSAGetLastError()<<endl
                ) : (
                        cout<<"Connection Accepted!"<<endl
                );

        // Step - 7  Send data to client;

                iSend = send(sAcceptSocket,SendBuffer,iSenderBuffer,0);

                iSend == SOCKET_ERROR ? (
                        cout<<"Send data to client Failed & Error No ->"<< WSAGetLastError()<<endl
                ) : (
                        cout<<"Send data to client Success!"<<endl
                );

        // Step - 8 Receive Data From Client

                iRecv = recv(sAcceptSocket,RecvBuffer,iRecvBuffer,0);

                iRecv == SOCKET_ERROR ? (
                        cout<<"Receive Data From Client Failed & Error No ->"<< WSAGetLastError()<<endl
                ) : (
                        cout<<"Receive Data From Client Success!"<<endl
                );

                cout<<"Data Received from Client: "<<RecvBuffer<<endl;
    
        // Step 9 Close Socket 

                iCLoseSocket = closesocket(TCPServerSocket);

                iCLoseSocket == SOCKET_ERROR ? (
                        cout<<"Close Socket Failed & Error No ->"<< WSAGetLastError()<<endl
                ) : (
                        cout<<"Close Socket Success!"<<endl
                );

        // Step 10 CleanUp from dll

                iWsaCleanUp = WSACleanup();

                iCLoseSocket == SOCKET_ERROR ? (
                                cout<<"Clean up Failed & Error No ->"<< WSAGetLastError()<<endl
                        ) : (
                                cout<<"Clean up Success!"<<endl
                        );

                system("pause");    
}