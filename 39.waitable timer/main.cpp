#include <windows.h>
#include <iostream>

using namespace std;

    //Global Variable
    
        HANDLE hTimer = NULL;
        DWORD dWaitForSingleObject;

    // Thread Function
        DWORD WINAPI Thread_Fun(LPVOID lpvoid) {
            dWaitForSingleObject = WaitForSingleObject(hTimer,INFINITE);

            dWaitForSingleObject == WAIT_FAILED ? 
            (
                cout<<"WaitForSingleObject Failed & Error No - "<<GetLastError()<<endl
            ) : (
                cout<<"Time Signaled after 5 Sec..."<<endl
            );

            cout<<"Thread Running"<<endl;
            return 0;
        }

int main() {

    // Local variable


        BOOL bSetWaitableTImer = false;
        HANDLE hThread;

        LARGE_INTEGER liDueTime;
        liDueTime.QuadPart = -50000000LL;

    // Step - 1 Create Waitbale Timer

        hTimer = CreateWaitableTimer(NULL,TRUE,NULL);

        hTimer == NULL ? 
        (
            cout<<"Create Waitbale Timer Function Failed & Error No - "<<GetLastError()<<endl
        ) : (
            cout<<"Create Waitbale Timer Function Success! "<<endl
        );

    // Step - 2 Create Thread

        hThread = CreateThread(NULL,0,Thread_Fun,NULL,0,NULL); 

    // Step - 3 Set Waitable Timer

        bSetWaitableTImer = SetWaitableTimer(
            hTimer,
            &liDueTime,
            0,
            NULL,
            NULL,
            0
        ); 

        bSetWaitableTImer == FALSE ? 
        (
            cout<<"Set Waitable Timer Failed & Error No - "<<GetLastError()<<endl
        ) : (
            cout<<"Set Waitable Timer Success! "<<endl
        );

    
    // Step - 4 Printing Output


        cout<<"Waiting for 5 Sec..."<<endl;       

    // Step - 5 Wait For Single Object

        WaitForSingleObject(hThread,INFINITE);    


    // Step - 6 CloseHandle

        CloseHandle(hTimer);
        CloseHandle(hThread);

    system("pause");    
}