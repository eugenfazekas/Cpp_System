#include <iostream>
#include <Windows.h>
using namespace std;

int main() {

    BOOL bHFile;

    bHFile = CreateHardLink(
      "D:\\Programing\\Git\\C++_System\\8.DeleteFile\\testfile.txt",
      "D:\\Programing\\Git\\C++_System\\8.DeleteFile\\copy.txt",
      NULL
    );
    
    bHFile == false ? (
              cout<<"CreateHardLink failed & Error No - "<<GetLastError()<<endl
        ) : (
              cout<<"CreateHardLink  Success!"<<endl
            ) ;

    system("pause");

    bHFile = DeleteFile(
      "D:\\Programing\\Git\\C++_System\\8.DeleteFile\\testfile.txt"
        );

    bHFile == false ? (
              cout<<"DeleteFile failed & Error No - "<<GetLastError()<<endl
        ) : (
              cout<<"DeleteFile  Success!"<<endl
            ) ;  
}