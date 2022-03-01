#include <windows.h>
#include <iostream>

using namespace std;

// Global Variable
    HANDLE hSemaphore;


// Thread Function
DWORD WINAPI ThreadFun (LPVOID lpParam) {
    DWORD dwWaitResult;
    BOOL bCondition = true;
    while(bCondition) {
        dwWaitResult = WaitForSingleObject(hSemaphore,INFINITE);
        switch (dwWaitResult)
        {
        case WAIT_OBJECT_0:
           cout<<"\n ThreadId - "<<GetCurrentThreadId()<<endl;
           bCondition = false;
           Sleep(5000);
           ReleaseSemaphore(hSemaphore,1,0);
            break; 
        case WAIT_TIMEOUT:
           cout<<"\nWait Timed Out ThreadId - "<<GetCurrentThreadId()<<endl;  
           break;
        default:
            break;
        }
    }
    return 0;
}

int main() {
    HANDLE  hThread[8];
    DWORD ThreadId;

    //Step - 1 Create Semaphore

        hSemaphore = CreateSemaphore(NULL,5,5,NULL);

        hSemaphore  == NULL ? (
            cout<<"Semaphore Creation Failed & Error No - "<<GetLastError()<<endl
        ) : (
            cout<<"Semaphore Creation Success!"<<endl
        );


    // Step 2 Create thread's

        for(int i = 0; i < 8 ; i++) {
            hThread[i] = CreateThread(NULL,0,&ThreadFun,NULL,0,&ThreadId);
        }

    // Step - 3 Wait for Single for thread
       
       WaitForMultipleObjects(8,hThread,TRUE,INFINITE); 

    // Step - 4 Close Handle for thread

        for(int i = 0; i < 8 ; i++) {
            CloseHandle(hThread[i]);
        }

    // Step - 5 Close Handle for Semaphore

        CloseHandle(hSemaphore);

    system("pause");
}