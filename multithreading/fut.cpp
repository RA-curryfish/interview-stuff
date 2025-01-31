#include<future>
#include<iostream>

using namespace std;

int foo(future<int>& f) {
    int res=1;    
    for(int k=f.get();k>=1;k--) res = res*k;
    return res;
}

int foo2(int x) {
    int res=1;
    for(int k=x;k>=1;k--) res = res*k;
    return res;
}

int main() {
    promise<int> p;
    future<int> fut_prom = p.get_future();
    future<int> f = async(&foo,ref(fut_prom));
    future<int> f1 = async(foo2,10);
    p.set_value(6);
    int ans = f1.get();
    cout<<f.get()<<endl;
    cout<<ans<<endl;
    return 0;
}
