#include <windows.h>
#include <iostream>

using namespace std;

// Global Variable
    HANDLE hSemaphore;

// Thread Function
DWORD WINAPI MyFun (LPVOID lpParam) {
    WaitForSingleObject(hSemaphore,INFINITE);
    cout<<"Critical Section"<<endl;
    ReleaseSemaphore(hSemaphore,1,0);
    return 0;
}

int main() {
    HANDLE  hThread1, hThread2;

    //Step - 1 Create Semaphore

        hSemaphore = CreateSemaphore(NULL,1,1,NULL);

        hSemaphore == NULL ? (
            cout<<"Semaphore Creation Failed & Error No - "<<GetLastError()<<endl
        ) : (
            cout<<"Semaphore Creation Success!"<<GetLastError()<<endl
        );

    // Step 2 Create Thread

        hThread1 = CreateThread(NULL,0,&MyFun,NULL,0,0);
        hThread2 = CreateThread(NULL,0,&MyFun,NULL,0,0);

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