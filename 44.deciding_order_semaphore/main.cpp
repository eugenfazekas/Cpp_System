#include <windows.h>
#include <iostream>

using namespace std;

// Global Variable
    HANDLE hSemaphore1;
    HANDLE hSemaphore2;
    HANDLE hSemaphore3;


// Thread Function
DWORD WINAPI ThreadFun1 (LPVOID lpParam) {
    WaitForSingleObject(hSemaphore2,INFINITE);
    cout<<"Thread 1"<<endl;
    ReleaseSemaphore(hSemaphore3,1,0);
    return 0;
}

DWORD WINAPI ThreadFun2 (LPVOID lpParam) {
    WaitForSingleObject(hSemaphore1,INFINITE); 
    cout<<"Thread 2"<<endl;
    ReleaseSemaphore(hSemaphore2,1,0);
    return 0;
}

DWORD WINAPI ThreadFun3 (LPVOID lpParam) {
    WaitForSingleObject(hSemaphore3,INFINITE);
    cout<<"Thread 3"<<endl;
    return 0;
}

DWORD WINAPI ThreadFun4 (LPVOID lpParam) {
    cout<<"Thread 4"<<endl;
    ReleaseSemaphore(hSemaphore1,1,0);
    return 0;
}

int main() {
    HANDLE  hThread1, hThread2,hThread3,hThread4;

    //Step - 1 Create Semaphore

        hSemaphore1 = CreateSemaphore(NULL,0,1,NULL);

        hSemaphore1 == NULL ? (
            cout<<"Semaphore1 Creation Failed & Error No - "<<GetLastError()<<endl
        ) : (
            cout<<"Semaphore1 Creation Success!"<<endl
        );

        hSemaphore2 = CreateSemaphore(NULL,0,1,NULL);

        hSemaphore2 == NULL ? (
            cout<<"Semaphore2 Creation Failed & Error No - "<<GetLastError()<<endl
        ) : (
            cout<<"Semaphore2 Creation Success!"<<endl
        );

        hSemaphore3 = CreateSemaphore(NULL,0,1,NULL);

        hSemaphore3 == NULL ? (
            cout<<"Semaphore3 Creation Failed & Error No - "<<GetLastError()<<endl
        ) : (
            cout<<"Semaphore3 Creation Success!"<<endl
        );

    // Step 2 Create 4 thread's

        hThread1 = CreateThread(NULL,0,&ThreadFun1,NULL,0,0);
        hThread2 = CreateThread(NULL,0,&ThreadFun2,NULL,0,0);
        hThread3 = CreateThread(NULL,0,&ThreadFun3,NULL,0,0);
        hThread4 = CreateThread(NULL,0,&ThreadFun4,NULL,0,0);

    // Step - 3 Wait for Single for thread

        WaitForSingleObject(hThread1,INFINITE); 
        WaitForSingleObject(hThread2,INFINITE);
        WaitForSingleObject(hThread3,INFINITE); 
        WaitForSingleObject(hThread4,INFINITE);


    // Step - 4 Close Handle for thread

        CloseHandle(hThread1);  
        CloseHandle(hThread2);
        CloseHandle(hThread3);
        CloseHandle(hThread4);

    // Step - 5 Close Handle for Semaphore

        CloseHandle(hSemaphore1);
        CloseHandle(hSemaphore2); 
        CloseHandle(hSemaphore3); 

    system("pause");
}