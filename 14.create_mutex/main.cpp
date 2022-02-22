#include <iostream>
#include <Windows.h>
using namespace std;

int main() {
    HANDLE hMutex;
    cout<<"Mutex 1"<<endl;

    hMutex = CreateMutex(
        NULL,
        FALSE,
        "MyMutex"
    ); 

    hMutex == NULL ? 
    (
            cout<<"Create Mutex Failed"<< GetLastError()<<endl
    ) : (
             cout<<"Create Mutex Succes!"<<endl
    );

    getchar();
    //CloseHandle(hMutex);

    system("pause");
}