#include <iostream>
#include <Windows.h>

using namespace std;

int main() {

    BOOL bCreatePipe;
    HANDLE hRead, hWrite;
    BOOL bReadFile, bWriteFile;

    char szBuffer[512] = "Hello Pipe";
    DWORD dwBufferSize = sizeof(szBuffer);
    DWORD dwNoBytesWrite, dwNoBytesRead;

    bCreatePipe = CreatePipe(
        &hRead,
        &hWrite,
        NULL,
        dwBufferSize
    );

    bCreatePipe == false ? (
        cout<<"Create Pipe Failed & Error No -"<<GetLastError()<<endl
    ) : (
        cout<<"Create Pipe Success!"<<endl
    );

    bWriteFile = WriteFile(
        hWrite,
        szBuffer,
        dwBufferSize,
        &dwNoBytesWrite,
        NULL
    );

    CloseHandle(hWrite);

    bReadFile = (
         hRead,
         szBuffer,
         dwBufferSize,
         &dwNoBytesRead,
         NULL
    );

    cout<<"Read from pipe -> "<<szBuffer<<endl;
    CloseHandle(hRead);

    system("pause");
}