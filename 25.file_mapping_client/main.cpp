#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    cout<<"\t\t..........FILEMAPPING CLIENT........."<<endl;

    //Local Variable Definition

        HANDLE hFileMap;
        BOOL bResult;
        PCHAR lpBuffer = NULL;

    // Step - 1 OpenFileMapping  

        hFileMap = OpenFileMapping(
            FILE_MAP_ALL_ACCESS,
            false,
           "Local\\MyFileMap"
        );

        hFileMap == NULL ? 
            (
                cout<<"Open File Mapping Failed & Error No - "<<GetLastError()<<endl
            ) : (
                cout<<"Open File Mapping Success!"<<endl
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
    // Step - 3 Reading the data from FIle Map Object

        cout<<"DATA Reading from Server "<<lpBuffer<<endl;

    // Step - 4 UnMapViewOfFile

        bResult = UnmapViewOfFile(lpBuffer);

        bResult == FALSE ? 
            (
                cout<<"Unmapping Failed & Error No - "<<GetLastError()<<endl
            ) : (
                cout<<"Unmapping Success!"<<endl
            ); 

        CloseHandle(hFileMap);   

    system("pause");
}