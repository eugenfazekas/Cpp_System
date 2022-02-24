#include <iostream>
#include <Windows.h>

using namespace std;

int main() {
    cout<<"\t\t.....Named Pipe Client......"<<endl;

    //Local variable Definitions
    HANDLE hCreateFile;

    //readFile local variable
    BOOL bReadFile;
    DWORD dwNoBytesRead;
    char szReadFileBuffer[1024];
    DWORD dwReadBufferSize = sizeof(szReadFileBuffer);


    //writeFile local variable
    BOOL bWriteFile;
    DWORD dwNoBytesWrite;
    char szWriteFileBuffer[1024] = "Hello From Named Pipe Client!";
    DWORD dwWriteBufferSize = sizeof(szWriteFileBuffer);

    hCreateFile = CreateFile(
         "\\\\.\\pipe\\MYNAMEDPIPE",
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    hCreateFile == INVALID_HANDLE_VALUE ? 
    (
        cout<<"File Creation Failed & Error No - "<<GetLastError()<<endl
    ) : (
        cout<<"File Creation Success"<<endl
    );

        bReadFile = ReadFile(
        hCreateFile,
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

    cout<<"Read File Success"<<endl;
    cout<<"DATA READING FROM SERVER-> "<<szReadFileBuffer<<endl;

    bWriteFile = WriteFile(
        hCreateFile,
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

    cout<<"WriteFile Success!"<<endl;

    CloseHandle(hCreateFile);

    system("pause");
}