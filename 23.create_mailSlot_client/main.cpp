#include <iostream>
#include <Windows.h>

using namespace std;

int main() {
    cout<<"\t\t.....MAILSSLOTS Client......"<<endl;

    //Local variable Definitions
    HANDLE hCreateFile;

    //writeFile local variable
    BOOL bWriteFile;
    DWORD dwNoBytesWrite;
    char szWriteFileBuffer[1024];
    DWORD dwWriteBufferSize = sizeof(szWriteFileBuffer);

    hCreateFile = CreateFile(
        "\\\\.\\mailslot\\MYMAILSLOTS",
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

    cout<<"Write your Message"<<endl;

    gets(szWriteFileBuffer);

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