#include <windows.h>
#include <iostream>

using namespace std;

//Global variable

    HANDLE hEvent;

//Thread Function

    DWORD WINAPI ThreadFun1(LPVOID lpParam) {
            HANDLE hOpenEvent;
            hOpenEvent = OpenEvent(
                EVENT_ALL_ACCESS,
                FALSE,
                "MyEvent"
            );
            hOpenEvent == FALSE ? (
                    cout<<"Open Event Function Failed"<<GetLastError()<<endl
            ) : (
                    cout<<"OpenEventFunction Success!"<<endl
            );
            for(int i = 1; i <= 2; i++) {
             WaitForSingleObject(hEvent,INFINITE);
                cout<<"Got Signaled = "<<i<<endl;
            }
              cout<<"Thread 1 Running!"<<endl;
              CloseHandle(hOpenEvent);
        return 0; 
    }

    DWORD WINAPI ThreadFun2(LPVOID lpParam) {
            cout<<"Thread 2 Running!"<<endl;
            for(int i = 1; i <= 2; i++) {
                SetEvent(hEvent);
                Sleep(2000);
            }

        return 0; 
    }

    int main() {

            cout<<"----------AUTO RESET EVENT-----------"<<endl;
    // Local Variable
        HANDLE hThread1, hThread2;
        DWORD ThreadId1, ThreadId2;

    // Step - 1 Initialize the CRITICAL_SECTION

        hEvent = CreateEvent(NULL, 
                            FALSE, //AUTO RESET
                            FALSE, // NON-SIGNALED
                            "MyEvent"
                            );

        hEvent == NULL ? (
                cout<<"Create Event Function Failed & Error No -> "<<GetLastError()<<endl
        ) : (
                cout<<"Create Event Success "<<endl 
        );

    // Step - 2 Creat thread functions

        hThread1 = CreateThread(NULL,0,ThreadFun1,NULL,0,&ThreadId1); 
        hThread2 = CreateThread(NULL,0,ThreadFun2,NULL,0,&ThreadId2); 

    // Step - 3 Wait for Signaled Object - Waits until the object is in signaled state
        WaitForSingleObject(hThread1,INFINITE);
        WaitForSingleObject(hThread2,INFINITE);

    // Step - 4 Closing Handle of thread

        CloseHandle(hThread1);
        CloseHandle(hThread2);

    //Step -5 CloseHandle for an Event
        CloseHandle(hEvent);

    system("pause");
    }


