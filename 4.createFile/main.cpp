#include <iostream>
#include <Windows.h>
using namespace std;

int main() {
    HANDLE hFile;

    hFile = CreateFile(
    "D:\\Programing\\Git\\C++_System\\4.createFile\\copy.txt",
    GENERIC_READ | GENERIC_WRITE,
    FILE_SHARE_READ,
    NULL,
    CREATE_NEW,
    FILE_ATTRIBUTE_NORMAL,
    NULL
    );

    hFile == INVALID_HANDLE_VALUE ? (
        cout<<"Create file failed & Error No - "<<GetLastError()<<endl
        ) : (
          cout<<"Create file  Success"<<endl) ;

    CloseHandle(hFile);

      
      system("pause");
}