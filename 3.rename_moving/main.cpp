#include <iostream>
#include <Windows.h>
using namespace std;

int main() {
    BOOL bFile;

    bFile = MoveFile(
    "D:\\Programing\\Git\\C++_System\\3.rename_moving\\copy.txt",
    "D:\\Programing\\Git\\C++_System\\3.rename_moving\\dir\\paste.txt"
    );

        bFile == false ? (
        cout<<"Move file failed & Error No - "<<GetLastError()<<endl) :
        (cout<<"Move file  Success"<<endl);
      
      system("pause");
}