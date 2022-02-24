#include <windows.h>
#include <iostream>

using namespace std;

//Global Variable

SYNCHRONIZATION_BARRIER sb;
int x = 5;

    DWORD WINAPI Thread1_Fun(LPVOID lpvoid) {

        EnterSynchronizationBarrier(&sb,SYNCHRONIZATION_BARRIER_FLAGS_SPIN_ONLY);
        cout<<"In Thread1_Fun "<<++x<<endl;
        cout<<endl;
        DeleteSynchronizationBarrier(&sb);
        return 0;
    }


    DWORD WINAPI Thread2_Fun(LPVOID lpvoid) {

        EnterSynchronizationBarrier(&sb,SYNCHRONIZATION_BARRIER_FLAGS_SPIN_ONLY);
        cout<<"In Thread2_Fun "<<++x<<endl;
        cout<<endl;
        DeleteSynchronizationBarrier(&sb);
        return 0;
    }

int main() {

    HANDLE Thread1, Thread2;

    //Step - 1 Initialize Conditional variable

        InitializeSynchronizationBarrier(&sb,2,SYNCHRONIZATION_BARRIER_FLAGS_SPIN_ONLY);

    // Step - 2 Create Writer Threads
    
        Thread1 = CreateThread(NULL,0,&Thread1_Fun,NULL,0,0); 
        Thread2 = CreateThread(NULL,0,&Thread2_Fun,NULL,0,0); 

    // Step - 3 Wait for Signaled Object for Writer and Reader

        WaitForSingleObject(Thread1,INFINITE);
        WaitForSingleObject(Thread2,INFINITE);


    // Step - 4 Close Handle for Writer and Reader

    CloseHandle(Thread1);
    CloseHandle(Thread2);


    system("pause");
}