#include <iostream>
#include <Windows.h>
using namespace std;

int main() {

    LONG lReg;
    DWORD dwData = 1234;
    HKEY hKey;

    lReg = RegCreateKeyEx(
        HKEY_LOCAL_MACHINE,
        "SOFTWARE\\Test\\Produc\\SmartId",
        0,
        NULL,
        REG_OPTION_NON_VOLATILE,
        KEY_ALL_ACCESS | KEY_WOW64_64KEY,
        NULL,
        &hKey,
        NULL
    );

    lReg != ERROR_SUCCESS ? 
        (
              cout<<"Create RegKey failed & Error No - "<<GetLastError()<<endl
        ) : (
              cout<<"Create RegKey   Success!"<<endl
            ) ;

    lReg = RegSetValueEx(
        hKey,
        "VALUE",
        NULL,
        REG_DWORD,
        (LPBYTE)&dwData,
        sizeof(dwData)
    );

    lReg != ERROR_SUCCESS ? 
        (
              cout<<"Create RegKey failed & Error No - "<<GetLastError()<<endl
        ) : (
              cout<<"Create RegKey   Success!"<<endl
            ) ;

    system("pause");
}