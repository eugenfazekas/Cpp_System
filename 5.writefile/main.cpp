#include <iostream>
#include <Windows.h>
using namespace std;

int main() {

    HANDLE hFile;
    BOOL bFile;
    char chBuffer[]="This is the Sample program of Write & Read API!";
    DWORD dwNoByteToWrite = strlen(chBuffer);
    DWORD dwNoByteWritten = 0;

    hFile = CreateFile(
    "D:\\Programing\\Git\\C++_System\\5.writefile\\copy.txt",
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
              cout<<"Create file  Success!"<<endl
            ) ;

    bFile = WriteFile(
      hFile,
      chBuffer,
      dwNoByteToWrite,
      &dwNoByteWritten,
      NULL
    );

    bFile == false ? (cout<<"Write file Failed!"<<endl):(cout<<"Write file Succes!"<<endl);
  
      system("pause");

          CloseHandle(hFile);
}