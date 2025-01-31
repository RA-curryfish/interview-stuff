#include<iostream>
#include<stack>
#include<mutex>
#include<thread>
#include<vector>
using namespace std;

template<typename T>
class ConcurrentStack{
    static stack<T> m_stack;
    static mutex m_mtx;
public:
    ConcurrentStack() = default;
    void push(T val) {
        unique_lock<mutex> lck(m_mtx);
        m_stack.push(val);
    }
    T pop() {
        unique_lock<mutex> lck(m_mtx);
        if(m_stack.empty())
            return "";
        T val = m_stack.top();
        m_stack.pop();
        return val;
    }
};

template<typename T> stack<T> ConcurrentStack<T>::m_stack;
template<typename T> mutex ConcurrentStack<T>::m_mtx;

void client(int id) {
    ConcurrentStack<string> *sS = new ConcurrentStack<string>();
    if(id%2) {
        sS->push(to_string(id));
    }
    else {
        cout<<sS->pop()<<endl;
    }
    delete sS;
}

int main() {
    thread tPool[10];
    size_t sz = sizeof(tPool)/sizeof(thread);
    for(int i=0;i<sz;i++) {   
        tPool[i] = thread(client,i);
    }
    //this_thread::sleep_for(chrono::seconds(10));
    for(int i=0;i<sz;i++) {   
        tPool[i].join();
    }
}
