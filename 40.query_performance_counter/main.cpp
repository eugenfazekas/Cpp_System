#include <windows.h>
#include <iostream>

using namespace std;

int main() {

    LARGE_INTEGER starting_time, ending_time, difference_of_time, frequency;
    QueryPerformanceFrequency(&frequency);

    QueryPerformanceCounter(&starting_time);
    cout<<"Hello World!"<<endl;
    QueryPerformanceCounter(&ending_time);

    difference_of_time.QuadPart = ending_time.QuadPart - starting_time.QuadPart;

    difference_of_time.QuadPart = difference_of_time.QuadPart * 1000000;
    difference_of_time.QuadPart = difference_of_time.QuadPart / frequency.QuadPart;
    difference_of_time.QuadPart = difference_of_time.QuadPart / 1000;

    cout<<"Execution Timer = "<<difference_of_time.QuadPart<<" ms"<<endl;
    system("pause");
}