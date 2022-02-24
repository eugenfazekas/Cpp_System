#include <iostream>
#include <windows.h>

using namespace std;

int main() {

    cout<<"\t\t...... MailSlots Server......"<<endl;

    //CreateMailSlots Local Variable

    HANDLE hSlots;

    //ReadFile Local Variable
    BOOL bReadFile;
    DWORD dwNoBytesRead;
    char szReadFileBuffer[1024];
    DWORD dwReadFileBufferSize = sizeof(szReadFileBuffer);

    // CreateMailslot def.
    hSlots = CreateMailslot(
        "\\\\.\\mailslot\\MYMAILSLOTS",
        0,
        MAILSLOT_WAIT_FOREVER,
        NULL
    );

    hSlots == INVALID_HANDLE_VALUE ? 
    (
            cout<<"Create Mail Slot Failed & Error No - "<<GetLastError()<<endl
    ) : (
            cout<<"Create Mail Slot Success "<<endl
    );

    bReadFile = ReadFile(
        hSlots,
        szReadFileBuffer,
        dwReadFileBufferSize,
        &dwNoBytesRead,
        NULL
    );

    bReadFile == false ? 
        (
            cout<<"Read File Failed & Error No - "<<GetLastError()<<endl
    ) : (
            cout<<"Read File Success! "<<endl
    );

    cout<<"DATA READING FROM MAISLOTS CLIENT ->"<<szReadFileBuffer<<endl;

    CloseHandle(hSlots);

    system("pause");
}