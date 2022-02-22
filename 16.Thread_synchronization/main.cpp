#include <iostream>
#include <Windows.h>
using namespace std;

HANDLE hMutex;
int gcount = 1;

DWORD WINAPI ThreadFunEven(LPVOID lpParam) {

    while(gcount<10){
        WaitForSingleObject(hMutex,INFINITE);
        if(gcount%2==0){
            cout<<"Even "<<gcount++<<endl;
        }
        ReleaseMutex(hMutex);
    }
    return 0;
}

DWORD WINAPI ThreadFunOdd(LPVOID lpParam) {
    while(gcount<10){
        WaitForSingleObject(hMutex,INFINITE);
        if(gcount%2==1){
            cout<<"Odd "<<gcount++<<endl;
        }
        ReleaseMutex(hMutex);
    }
    return 0;
}

int main() {

    HANDLE hThread1, hThread2;
    cout<<"Thread Synchronization"<<endl;
    hMutex = CreateMutex(
        NULL,
        false,
        NULL
    );

    hThread1 = CreateThread(
        NULL,
        0,
        ThreadFunEven,
        NULL,
        0,
        NULL
    );
        hThread2 = CreateThread(
        NULL,
        0,
        ThreadFunOdd,
        NULL,
        0,
        NULL
    );

    CloseHandle(hThread1);
    CloseHandle(hThread2);

    system("pause");
}