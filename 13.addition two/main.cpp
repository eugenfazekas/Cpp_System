#include <iostream>
#include <Windows.h>
using namespace std;


int a[2];
DWORD WINAPI ThreadFun(LPVOID lpParam) {
    int x,y,result;
    x = a[0];
    y = a[1];
    result = x + y;
    cout<<"Addition "<<result<<endl;
    return 0;
}

int main() {
    HANDLE hThread;
    DWORD ThreadId; 

    cout<<"Enter Your First No."<<endl;
    cin>>a[0];
    cout<<"Enter Your Second No."<<endl;
    cin>>a[1];

    hThread = CreateThread(
        NULL,
        0,
        ThreadFun,
        (void*)&a,
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