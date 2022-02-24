#include <windows.h>
#include <iostream>

using namespace std;

//Global variable

    HANDLE hEvent;

//Thread Function

    DWORD WINAPI ThreadFun1(LPVOID lpParam) {
            WaitForSingleObject(hEvent,INFINITE);
            cout<<"Thread 1 Running!"<<endl;
        return 0; 
    }

    DWORD WINAPI ThreadFun2(LPVOID lpParam) {
            cout<<"Thread 2 Running!"<<endl;
            SetEvent(hEvent);
        return 0; 
    }

    int main() {

            cout<<"----------EVENT-----------"<<endl;
    // Local Variable
        HANDLE hThread1, hThread2;
        DWORD ThreadId1, ThreadId2;

    // Step - 1 Initialize the CRITICAL_SECTION

        hEvent = CreateEvent(NULL,FALSE,FALSE,"MyEvent");

        hEvent == NULL ? (
                cout<<"Create Event Function Failed & Error No -> "<<GetLastError()<<endl
        ) : (
                cout<<"Create Event Success "<<endl
        );

    // Step - 2 Creat thread functions

        hThread1 = CreateThread(NULL,0,ThreadFun1,NULL,0,&ThreadId1); 
        hThread2 = CreateThread(NULL,0,ThreadFun2,NULL,0,&ThreadId2); 

    // Step - 3 Wait for Signaled Object
        WaitForSingleObject(hThread1,INFINITE);
        WaitForSingleObject(hThread2,INFINITE);

    // Step - 4 Closing Handle of thread

    CloseHandle(hThread1);
    CloseHandle(hThread2);

    system("pause");
    }


