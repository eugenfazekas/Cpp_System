#include <iostream>
#include <Windows.h>

using namespace std;

int main() {

    HANDLE hSem;

    cout<<"Open Semaphore"<<endl;
    hSem = OpenSemaphore(
        SEMAPHORE_ALL_ACCESS,
        false,
        "MySemaphore"
    );

    hSem == NULL ? 
    (
        cout<<"Open Semaphore Failed: "<<GetLastError()<<endl
    ) : (
        cout<<"Open Semaphore Success!"<<endl
    );

    getchar();
    CloseHandle(hSem);

    system("pause");
}