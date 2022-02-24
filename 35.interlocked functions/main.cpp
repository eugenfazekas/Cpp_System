#include <windows.h>
#include <iostream>
#include <intrin.h>

using namespace std;

int main() {
    volatile LONG64 a = 5;
    volatile LONG64 b;

    b = InterlockedAdd64(&a, 5);
    cout<<"Addition = "<<b<<endl;

    volatile LONG64 x = 10;
    volatile LONG64 y = 0;

    y = InterlockedIncrement64(&x);
    cout<<"Increment = "<<y<<endl;

}