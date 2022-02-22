#include <iostream>
#include <Windows.h>
using namespace std;

int main() {

    HANDLE hProcess = NULL;
    HANDLE hThread = NULL;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    DWORD dwProcessId = 0;
    DWORD dwThreadID = 0;
    ZeroMemory( &si, sizeof(si) );
    ZeroMemory( &pi, sizeof(pi) );
    BOOL bCreateProcess;

    bCreateProcess= CreateProcess(
        "C:\\Program Files\\Windows Media Player\\wmplayer.exe",
        NULL,
        NULL,
        NULL,
        false,
        0,
        NULL,
        NULL,
        &si,
        &pi
    ); 

    bCreateProcess == false ? (
            cout<<"Create Pocess failed & Error No - "<<GetLastError()<<endl
        ) : (
            cout<<"Create Pocess success "<<endl
        );

    cout<<"Process ID ->"<<pi.dwProcessId<<endl;
    cout<<"Thread ID ->"<<pi.dwThreadId<<endl;
    cout<<"GetProcessId: "<<GetProcessId(pi.hProcess)<<endl;
    cout<<"GetThreadId: "<<GetThreadId(pi.hThread)<<endl;

    WaitForSingleObject(pi.hProcess,INFINITE);

    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    system("pause")  ;  
} 