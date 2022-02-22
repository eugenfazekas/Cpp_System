#include <iostream>
#include <Windows.h>
using namespace std;

int main() {
    BOOL bFile;

    bFile = CopyFile("D:\\Programing\\Git\\C++_System\\2.copy file\\copy.txt",
    "D:\\Programing\\Git\\C++_System\\2.copy file\\paste.txt", false
    );

        if(bFile == false) {
        cout<<"Copy file failed & Error No - "<<GetLastError()<<endl;
    }

        cout<<"Copy file  Success"<<endl;
      system("pause");
}