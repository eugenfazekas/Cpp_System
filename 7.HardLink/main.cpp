#include <iostream>
#include <Windows.h>
using namespace std;

int main() {

    BOOL bHFile;

    bHFile = CreateHardLink(
      "D:\\Programing\\Git\\C++_System\\7.HardLink\\testfile.txt",
      "D:\\Programing\\Git\\C++_System\\7.HardLink\\copy.txt",
      NULL
    );
    
    bHFile == false ? (
              cout<<"CreateHardLink failed & Error No - "<<GetLastError()<<endl
        ) : (
              cout<<"CreateHardLink  Success!"<<endl
            ) ;

    system("pause");
}