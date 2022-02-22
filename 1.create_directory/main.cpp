#include <iostream>
#include <Windows.h>
using namespace std;

int main() {

    BOOL bDir;
    bDir = CreateDirectory("D:\\Programing\\Git\\C++_System\\1.create_directory\\dir1", NULL);

    if(bDir == false) {
        cout<<"Create directory failed & Error No - "<<GetLastError()<<endl;
    }

    cout<<"Create Directory Success"<<endl;

    system("pause");

    bDir = RemoveDirectory("D:\\Programing\\Git\\C++_System\\1.create_directory\\dir1");

    
    if(bDir == false) {
        cout<<"Delete directory failed & Error No - "<<GetLastError()<<endl;
    }

    cout<<"Delete Directory Success"<<endl;
}