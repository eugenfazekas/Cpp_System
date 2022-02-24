#include <iostream>
#include <Windows.h>

using namespace std;

int main() {
    cout<<"\t\t.....Named Pipe Server......"<<endl;

    //Named Pipe Local Variable
    HANDLE hCreateNamedPipe;
    char szInputBuffer[1024], szOutputBuffer[1024];
    DWORD dwszInputBuffer = sizeof(szInputBuffer);
    DWORD dwszOutputBuffer = sizeof(szOutputBuffer);

    // Connect Named Pipe Local Variable;

    BOOL bConnectNamedPipe;

    //writeFile local variable
    BOOL bWriteFile;
    char szWriteFileBuffer[1024] = "Hello From Named Pipe Server!";
    DWORD dwWriteBufferSize = sizeof(szWriteFileBuffer);
    DWORD dwNoBytesWrite;

    //flushBuffer

    BOOL bFlushFileBuffer;

    //readFile local variable
    BOOL bReadFile;
    char szReadFileBuffer[1024];
    DWORD dwReadBufferSize = sizeof(szReadFileBuffer);
    DWORD dwNoBytesRead;

    hCreateNamedPipe = CreateNamedPipe(
        "\\\\.\\pipe\\MYNAMEDPIPE",
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        PIPE_UNLIMITED_INSTANCES,
        dwszOutputBuffer,
        dwszInputBuffer,
        0,
        NULL
    );

    hCreateNamedPipe == INVALID_HANDLE_VALUE ? 
    (
        cout<<"Named Pipe Creation Failed & Error No - "<<GetLastError()<<endl
    ) : (
        cout<<"Named Pipe Cration Success!"<<endl
    );

    bConnectNamedPipe = ConnectNamedPipe(hCreateNamedPipe, NULL);

    bConnectNamedPipe == false ? 
    (
            cout<<"Connection Failed & Error No - "<<GetLastError()<<endl
    ) : (
            cout<<"Connection Success! "<<endl
    );

    bWriteFile = WriteFile(
        hCreateNamedPipe,
        szWriteFileBuffer, 
        dwWriteBufferSize,
        &dwNoBytesWrite,
        NULL
    );

    bWriteFile == false ?
    (
            cout<<"Write File Failed & Error No - "<<GetLastError()<<endl
    ) : (
            cout<<"Write File Success! "<<endl
    );

    bFlushFileBuffer = FlushFileBuffers(hCreateNamedPipe);

        bFlushFileBuffer == false ? 
        (
            cout<<"FlushFileBuffer Failed & Error No - "<<GetLastError()<<endl
    ) : (
            cout<<"FlushFileBuffer Success! "<<endl
    );

    bReadFile = ReadFile(
        hCreateNamedPipe,
        szReadFileBuffer,
        dwReadBufferSize,
        &dwNoBytesRead,
        NULL
    );

    bReadFile == false ? 
        (
            cout<<"Read File Failed & Error No - "<<GetLastError()<<endl
    ) : (
            cout<<"Read File Success! "<<endl
    );

    cout<<"DATA READING FROM CLIENT -> "<<szReadFileBuffer<<endl;

    DisconnectNamedPipe(hCreateNamedPipe);

    CloseHandle(hCreateNamedPipe);

    system("pause");
}