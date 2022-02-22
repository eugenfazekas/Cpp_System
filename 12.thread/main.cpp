#include <iostream>
#include <Windows.h>
using namespace std;

DWORD WINAPI ThreadFun(LPVOID lpParam) {
    cout<<"Thread Running! "<<endl;
    return 0;
}

int main() {
    HANDLE hThread;
    DWORD ThreadId;

    hThread = CreateThread(
        NULL,
        0,
        ThreadFun,
        NULL,
        0,
        &ThreadId
    );

    hThread == NULL ? (
        cout<<"Thread Creation Failed"<<GetLastError()<<endl
    ) : (cout<<"Thread Creation Success! "<<endl);

    cout<<"ThreadId: "<<ThreadId<<endl;
    CloseHandle(hThread);

    system("pause");
}