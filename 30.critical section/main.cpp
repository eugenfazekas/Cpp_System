#include <windows.h>
#include <iostream>

using namespace std;

//Global variable

    int gcount = 0;
    CRITICAL_SECTION cs;

//Thread Function


    DWORD WINAPI ThreadFunEven(LPVOID lpParam) {
        while(gcount<10){
            EnterCriticalSection(&cs);
            if(gcount%2==0) {
                int i = gcount++;
                cout<<"Even - "<<i<<" count e"<<endl;
            }
            LeaveCriticalSection(&cs);
        } 
        return 0;
    }

    DWORD WINAPI ThreadFunOdd(LPVOID lpParam) {
        while(gcount<10){
            EnterCriticalSection(&cs);
            if(gcount%2==1) {
                int i = gcount++;
                cout<<"Odd - "<<i<<" count o"<<endl;
            }
            LeaveCriticalSection(&cs);
        } 
        return 0;
    }

    int main() {

            cout<<"----------CRITICAL_SECTION-----------"<<endl;
    // Local Variable
        HANDLE hThread1, hThread2;
    // Step - 1 Initialize the CRITICAL_SECTION

        InitializeCriticalSection(&cs);

    // Step - 2 Creat thread functions

        hThread1 = CreateThread(NULL,0,ThreadFunEven,NULL,0,NULL); 
        hThread2 = CreateThread(NULL,0,ThreadFunOdd,NULL,0,NULL); 

    // Step - 3 Wait for Signaled Object
        WaitForSingleObject(hThread1,INFINITE);
        WaitForSingleObject(hThread2,INFINITE);

    // Step - 4 Closing Handle of thread

    CloseHandle(hThread1);
    CloseHandle(hThread2);

    // Deleting the critical section

        DeleteCriticalSection(&cs);
    system("pause");
    }


