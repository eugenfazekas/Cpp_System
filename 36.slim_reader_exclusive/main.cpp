#include <windows.h>
#include <iostream>

using namespace std;

//Global Variable

    SRWLOCK lock;
    int flag = 0;
    int x = 0;

    DWORD WINAPI WriterThread(LPVOID lpvoid) {

        while(1) {
            AcquireSRWLockExclusive(&lock);
                x = x + 5;
                cout<<"Writer - "<<x<<endl;
            ReleaseSRWLockExclusive(&lock);
            Sleep(1000);
        }
        return 0;
    }


    DWORD WINAPI ReaderThread(LPVOID lpvoid) {
        while(1) {
            AcquireSRWLockExclusive(&lock);
                flag++;
               if ( flag == 1 ) {
                    cout<<"Reader - "<<x<<endl;
                }
                --flag;
                cout<<"Reader - "<<x<<endl;
            ReleaseSRWLockExclusive(&lock);
            Sleep(1000);
        }
        return 0;
    }

int main() {

    HANDLE hWriter, hReader;

    // Step - 1 Initialize SRW Lock
        InitializeSRWLock(&lock);

    hWriter = CreateThread(NULL,0,&WriterThread,NULL,0,0); 
    hReader = CreateThread(NULL,0,&ReaderThread,NULL,0,0); 

    // Step - 4 Wait for Signaled Object for Writer and Reader
        WaitForSingleObject(hWriter,INFINITE);
        WaitForSingleObject(hReader,INFINITE);

    // Close Handle for Writer and Reader

    CloseHandle(hWriter);
    CloseHandle(hReader);

    system("pause");
}