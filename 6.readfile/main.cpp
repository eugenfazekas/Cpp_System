#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

void beolvas(vector<string> &v) {
    string sor;
    ifstream fin("copy.txt");
    while(!fin.eof()) {
        getline(fin,sor);
        cout<<sor<<endl;
        v.push_back(sor);
    }
    fin.close();
}

int main() {
    vector<string> v;
    beolvas(v);
}