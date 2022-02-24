#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    cout<<"\t\t..........FILEMAPPING SERVER........."<<endl;

    //Local Variable Definitions

        HANDLE hFileMap;
        BOOL bResult;
        PCHAR lpBuffer = NULL;
        char Buffer[1024] = "Hello from File Map Server";
        size_t szBuffer = sizeof( Buffer );

    // Step - 1 Create File Mapping
        hFileMap = CreateFileMapping(
            INVALID_HANDLE_VALUE,
            NULL,
            PAGE_READWRITE,
            0,
            256,
            "Local\\MyFileMap"
        );

        hFileMap == FALSE ? 
        (
            cout<<"Create File Mapping Failed & Error No - "<<GetLastError()<<endl
        ) : (
            cout<<"Create File Mapping Success!"<<endl
        );

    // Step - 2 MapViewOfFile

        lpBuffer = (PCHAR)MapViewOfFile(
            hFileMap,
            FILE_MAP_ALL_ACCESS,
            0,
            0,
            256   
        );

        lpBuffer == NULL ? 
        (
            cout<<"MapViewOfFile Failed & Error No - "<<GetLastError()<<endl
        ) : (
            cout<<"MapViewOfFile Success!"<<endl
        );

    // Step - 3 Copy Memory Function

        CopyMemory(lpBuffer,Buffer,szBuffer);

    // Step - 4 UnMapViewOfFile

    bResult = UnmapViewOfFile(lpBuffer);

        bResult == false ? 
            (
                cout<<"UnmapViewOfFile Failed & Error No - "<<GetLastError()<<endl
            ) : (
                cout<<"UnmapViewOfFile Success!"<<endl
            );

    system("pause");        
}