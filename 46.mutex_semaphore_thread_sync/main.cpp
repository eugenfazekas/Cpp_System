#include <windows.h>
#include <iostream>

using namespace std;

// Global Variable
    HANDLE hSemaphore;
    HANDLE hMutex;
    int i = 0;

// Thread Function
    DWORD WINAPI ThreadFun (LPVOID lpParam) {
        while(i < 20) {
            WaitForSingleObject(hSemaphore,INFINITE);
            WaitForSingleObject(hMutex,INFINITE);
            cout<<"Count = "<<i++<<endl;
            ReleaseMutex(hMutex);
            ReleaseSemaphore(hSemaphore,1,0);
            Sleep(500);
        }
        return 0;
    }

    int main() {
        HANDLE  hThread1,hThread2;

    //Step - 1 Create Semaphore

        hSemaphore = CreateSemaphore(NULL,5,5,NULL);

        hSemaphore  == NULL ? (
            cout<<"Semaphore Creation Failed & Error No - "<<GetLastError()<<endl
        ) : (
            cout<<"Semaphore Creation Success!"<<endl
        );

    // Create mutex
    
        hMutex = CreateMutex(
            NULL,
            FALSE,
            NULL
        );

        hMutex   == NULL ? (
            cout<<"Mutex Creation Failed & Error No - "<<GetLastError()<<endl
        ) : (
            cout<<"Mutex Creation Success!"<<endl
        );

    // Step 3 Create thread's

        hThread1 = CreateThread(NULL,0,&ThreadFun,NULL,0,0);
        hThread2 = CreateThread(NULL,0,&ThreadFun,NULL,0,0);

    // Step - 4 Wait for Single for thread
       
       WaitForSingleObject(hThread1,INFINITE); 
       WaitForSingleObject(hThread2,INFINITE); 

    // Step - 5 Close Handle for thread

        CloseHandle(hThread1);
        CloseHandle(hThread2);

    // Step - 6 Close mutex

        CloseHandle(hMutex);

    // Step - 7 Close Handle for Semaphore

        CloseHandle(hSemaphore);

    system("pause");
}