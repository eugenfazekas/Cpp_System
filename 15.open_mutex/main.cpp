#include <iostream>
#include <Windows.h>
using namespace std;

int main() {
    HANDLE hMutex;
    cout<<"Open Mutex Fun"<<endl;
    getchar();

    hMutex = OpenMutex(
        MUTEX_ALL_ACCESS,
        FALSE,
        "MyMutex"
    ); 

    hMutex == NULL ? 
    (
            cout<<"Open Mutex Failed"<< GetLastError()<<endl
    ) : (
             cout<<"Open Mutex Succes!"<<endl
    );

    CloseHandle(hMutex);

    system("pause");
}