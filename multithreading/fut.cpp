#include<future>
#include<iostream>

using namespace std;

int foo(future<int>& f) {
    int res=1;    
    for(int k=f.get();k>=1;k--) res = res*k;
    return res;
}

int main() {
    promise<int> p;
    future<int> fut_prom = p.get_future();
    future<int> f = async(foo,ref(fut_prom));
    p.set_value(6);
    cout<<f.get()<<endl;
    return 0;
}
