#include<iostream>
#include<vector>
using namespace std;

class A {
    int a;
    public:
    A(): a(0) {} // constructor
    explicit A(int x): a(x) {} // constructor
    A(A& op1) { // copy constructor 
        this->a = op1.a;
    }
    A(A&& op1) noexcept = default; // move constructor, no exceptions, optimize
    A operator+(A&& op2) {
        cout<<"Rvalue"<<endl;
        A ret = A();
        ret.a = this->a+1 + op2.a+1;
        return ret;
    }   
    A& operator+(A& op2) {
        cout<<"Lvalue"<<endl;
        this->a = this->a+1 + op2.a+1;
        return *this; // return *this to allow funciton chaining
    }
    A& operator=(A& op) noexcept = default; // assignment overload for copy
    A& operator=(A&& op) noexcept = default; // assignment overaload for move
    ~A() {} // destructor
    int getMember() { return this->a;}
};

int main() {
    A a1,a2,a3; a1= a2 = A(1);
    A a4 = a1+move(a2); // value copied before returning??
    A& a5 = a1+a3; // lvalue reference??
    cout<<a4.getMember()<<endl;
    cout<<a5.getMember()<<endl;
    cout<<(a1+a3).getMember()<<endl;
    A a6(a5);
    return 0;
}
