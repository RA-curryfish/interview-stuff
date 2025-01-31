#include<iostream>
#include<fstream>

using namespace std;

int main() {
    fstream f("files.cpp");
    if(!f.is_open()){
        cout<< "error" << endl;
    }
    string buf = "";
    while(getline(f,buf)){
        cout<< buf << endl;
    }
    f.close();
    return 0;
}
