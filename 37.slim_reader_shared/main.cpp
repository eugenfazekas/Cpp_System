#include <windows.h>
#include <iostream>

using namespace std;

//Global Variable

CONDITION_VARIABLE cvw;
CONDITION_VARIABLE cvr;
SRWLOCK lock;
int x = 0;
int readercount = 0;

    DWORD WINAPI WriterThread(LPVOID lpvoid) {
        while(1) {
            AcquireSRWLockShared(&lock);
                x = x + 5;
                cout<<"Writer = "<<x<<endl;
            ReleaseSRWLockShared(&lock);
            WakeConditionVariable(&cvr);
            Sleep(1000);
        }
        return 0;
    }


    DWORD WINAPI ReaderThread(LPVOID lpvoid) {
        while(1) {
            AcquireSRWLockShared(&lock);
            ++readercount;

            if (readercount == 1) { 
                SleepConditionVariableSRW(&cvw,&lock,INFINITE,CONDITION_VARIABLE_LOCKMODE_SHARED);
            } 
            ReleaseSRWLockShared(&lock);
            cout<<"Reader = "<<x<<endl;
            AcquireSRWLockShared(&lock);
            --readercount;
            if (readercount == 0 ) { 
                TryAcquireSRWLockShared(&lock);
             } 
            ReleaseSRWLockShared(&lock);
            WakeConditionVariable(&cvw);
            Sleep(1000);
        } 
        return 0;
    }

int main() {

    HANDLE hWriter, hReader[2];

    //Step - 1 Initialize Conditional variable

        InitializeConditionVariable(&cvw);
        InitializeConditionVariable(&cvr);

    // Step - 2 Initialize SRW Lock

        InitializeSRWLock(&lock);

    // Step - 3 Create Writer Thread
    
        hWriter = CreateThread(NULL,0,&WriterThread,NULL,0,0); 

    // Step - 4 Create Reader Threads

        hReader[0] = CreateThread(NULL,0,&ReaderThread,NULL,0,0); 
        hReader[1] = CreateThread(NULL,0,&ReaderThread,NULL,0,0); 

    // Step - 5 Wake up all conditional Variable 

        WakeAllConditionVariable(&cvw);
        WakeAllConditionVariable(&cvr);

    // Step - 6 Wait for Signaled Object for Writer and Reader
        WaitForSingleObject(hWriter,INFINITE);
        WaitForSingleObject(hReader[0],INFINITE);
        WaitForSingleObject(hReader[1],INFINITE);

    // Step - 7 Close Handle for Writer and Reader

    CloseHandle(hWriter);
    CloseHandle(hReader[0]);
    CloseHandle(hReader[1]);

    system("pause");
}