#include <windows.h>
#include <iostream>

using namespace std;

// Global Variable
    HANDLE hSemaphore;
    int a,b,c;

// Thread Function
DWORD WINAPI InputFun (LPVOID lpParam) {
    cout<<"Enter 1-st NO. "<<endl;
    cin>>a;
    cout<<"Enter 2-nd NO. "<<endl;
    cin>>b;
    Sleep(1000);
    ReleaseSemaphore(hSemaphore,1,0);
    return 0;
}

DWORD WINAPI OutputFun (LPVOID lpParam) {
    WaitForSingleObject(hSemaphore,INFINITE);
    c = a + b;
    cout<<"Addition a + b = "<<c<<endl;
    return 0;
}

int main() {
    HANDLE  hThread1, hThread2;

    //Step - 1 Create Semaphore

        hSemaphore = CreateSemaphore(NULL,0,1,NULL);

        hSemaphore == NULL ? (
            cout<<"Semaphore Creation Failed & Error No - "<<GetLastError()<<endl
        ) : (
            cout<<"Semaphore Creation Success!"<<GetLastError()<<endl
        );

    // Step 2 Create Thread

        hThread1 = CreateThread(NULL,0,&InputFun,NULL,0,0);
        hThread2 = CreateThread(NULL,0,&OutputFun,NULL,0,0);

    // Step - 3 Wait for Single for thread

        WaitForSingleObject(hThread1,INFINITE); 
        WaitForSingleObject(hThread2,INFINITE);

    // Step - 4 Close Handle for thread

        CloseHandle(hThread1);  
        CloseHandle(hThread2);

    // Step - 5 Close Handle for Semaphore

        CloseHandle(hSemaphore); 
    system("pause");
}