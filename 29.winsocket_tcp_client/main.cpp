#include <winsock2.h>
#include <iostream>

using namespace std;

int main() {
    cout<<"\t\t-----------TCP CLIENT-----------"<<endl;
    cout<<endl;

    //Local Variable

    WSADATA WinSockData;
    int iWsaStartup;
    int iWsaCleanUp;

    SOCKET TCPClientSocket;
    int iCLoseSocket;

    struct sockaddr_in TCPServerAdd;

    int iConnect;

    const int BUFFER_SIZE = 512;

    int iRecv;
    char RecvBuffer[BUFFER_SIZE];
    int iRecvBuffer = BUFFER_SIZE;

    int iSend;
    char SendBuffer[BUFFER_SIZE] = "Hello from Client!";
    int iSenderBuffer = BUFFER_SIZE;

        // Step - 1 Start Up WSA function

                iWsaStartup = WSAStartup(MAKEWORD(2,2),&WinSockData);

                iWsaStartup != 0 ? (
                        cout<<"WSAStartup Failed"<<endl
                ) : (
                        cout<<"WSAStartup Success!"<<endl
                );

        // Step - 2 Create Socket 

                TCPClientSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

                TCPClientSocket == INVALID_SOCKET ? (
                        cout<<"Server Socket Creation Failed"<< WSAGetLastError()<<endl
                ) : (
                        cout<<"Server Socket Creation Success!"<<endl
                );
   
        // Step - 3 Fill the Structure

                TCPServerAdd.sin_family = AF_INET;
                TCPServerAdd.sin_addr.s_addr = inet_addr("127.0.0.1");
                TCPServerAdd.sin_port = htons(8002);    

        // Step - 4 Connect function

                iConnect = connect(TCPClientSocket,(SOCKADDR*)&TCPServerAdd,sizeof(TCPServerAdd));        

                iConnect == SOCKET_ERROR ? (
                        cout<<"Connection to server Failed"<< WSAGetLastError()<<endl
                ) : (
                        cout<<"Connection to  Success!"<<endl
                        
                );
        // Step - 5 Receive Data From Server

                iRecv = recv(TCPClientSocket,RecvBuffer,iRecvBuffer,0);

                iRecv == SOCKET_ERROR ? (
                    cout<<"Receive Data From Server Failed & Error No ->"<< WSAGetLastError()<<endl
            ) : (
                    cout<<"Receive Data From Server Success!"<<endl
            );

                cout<<"Data Received from Server: "<<RecvBuffer<<endl;
        // Step - 7  Send data to Server;

                iSend = send(TCPClientSocket,SendBuffer,iSenderBuffer,0);

                iSend == SOCKET_ERROR ? (
                                cout<<"Send data to Server Failed & Error No ->"<< WSAGetLastError()<<endl
                        ) : (
                                cout<<"Send data to Server Success!"<<endl
                        );
 
        // Step 8 Close Socket 

                iCLoseSocket = closesocket(TCPClientSocket);

                iCLoseSocket == SOCKET_ERROR ? (
                                cout<<"Close Socket Failed & Error No ->"<< WSAGetLastError()<<endl
                        ) : (
                                cout<<"Close Socket Success!"<<endl
                        );

        // Step 9 CleanUp from dll

                iWsaCleanUp = WSACleanup();

                iCLoseSocket == SOCKET_ERROR ? (
                        cout<<"Clean up Failed & Error No ->"<< WSAGetLastError()<<endl
                ) : (
                        cout<<"Clean up Success!"<<endl
                );

    system("pause");    
}