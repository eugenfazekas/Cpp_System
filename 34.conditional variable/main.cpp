#include <windows.h>
#include <iostream>

using namespace std;

CRITICAL_SECTION cs;
CONDITION_VARIABLE cv;
int buffer = 0;
int max_items[20];

DWORD WINAPI ProducerThread(LPVOID lpvoid) {
    for( int i = 0 ; i < 20; i++) {
        EnterCriticalSection(&cs);
            while(buffer == 20){
                SleepConditionVariableCS(&cv,&cs,INFINITE);
            }
        buffer++;
        cout<<"Producer = "<<buffer<<endl;
        Sleep(1000);
        WakeConditionVariable(&cv);
        LeaveCriticalSection(&cs);
    }
    return 0;
}


DWORD WINAPI ConsumerThread(LPVOID lpvoid) {
    for( int i = 0 ; i < 20; i++) {
        EnterCriticalSection(&cs);
        while(buffer == 0 ) {
            SleepConditionVariableCS(&cv,&cs,INFINITE);
        }
        cout<<"Consumer = "<<buffer<<endl;
        buffer--;
        WakeConditionVariable(&cv);
        LeaveCriticalSection(&cs);
    }
    return 0;
}

int main() {

    //Handle for thread
        HANDLE hProducer, hConsumer;

    // Initialize Critical Section
        InitializeCriticalSection(&cs);

    // Step - 1 Initialize Conditional variable

        InitializeConditionVariable(&cv);
    // Step - 2 Create Create Producer and Consumer Thread 

        hProducer = CreateThread(NULL,0,&ProducerThread,NULL,0,0); 
        hConsumer = CreateThread(NULL,0,&ConsumerThread,NULL,0,0);  

    // Wake All Conditional Variable

        WakeAllConditionVariable(&cv);

    // Step - 4 Wait for Signaled Object - Waits until the object is in signaled state
        WaitForSingleObject(hProducer,INFINITE);
        WaitForSingleObject(hConsumer,INFINITE);

    system("pause");

}