#include <iostream>
#include <Windows.h>
using namespace std;

int main() {

    BOOL bHFile;

    bHFile = CreateSymbolicLink(
      "D:\\Programing\\Git\\C++_System\\9.symbolicLink\testfile.txt",
      "D:\\Programing\\Git\\C++_System\\9.symbolicLink\\copy.txt",
      0
    );
    
    bHFile == false ? (
              cout<<"CreateSymbolicLink failed & Error No - "<<GetLastError()<<endl
        ) : (
              cout<<"CreateSymbolicLink  Success!"<<endl
            ) ;

    system("pause"); 
}