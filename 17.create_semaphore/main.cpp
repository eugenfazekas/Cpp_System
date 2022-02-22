#include <iostream>
#include <Windows.h>

using namespace std;

int main() {

    HANDLE hSem;
    cout<<"Create Semaphore"<<endl;
    hSem = CreateSemaphore(
        NULL,
        1,
        1,
        "MySemaphore"
    );

    hSem == NULL ? 
    (
        cout<<"Create Semaphore Failed: "<<GetLastError()<<endl
    ) : (
        cout<<"Create Semaphore Success!"<<endl
    );

    getchar();
    CloseHandle(hSem);

    system("pause");
}