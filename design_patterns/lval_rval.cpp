#include<iostream>
#include<memory>
#include<thread>
// virtual constructors don't exist, but virtual destructors do
using namespace std;

class Base {
public:    int a;
    Base(int x): a(x) {}
    Base(const Base& other) {cout<<"base cpy &"<<endl;}; // copy constructor, cannot modify the other, hence set it to const lval ref
    Base(Base&& other): a(other.a) {cout<<"base mv &&"<<endl;} // move constructor, can reset the 'other' if we want
    Base& operator=(Base& other) {
        this->a=other.a;
        cout<<"cpy assng"<<endl;
        return *this;
    }
    Base& operator=(Base&& other) {//delete stuff for 'this' to prevent memleak
        this->a = other.a;
        //can clear with other
        cout<<"mov assgn"<<endl;
        return *this;
    }
    virtual ~Base() {cout<<"bse dst"<<endl;} // need virtual destructor to delete derived thru base ptr. but no need for virtual constructor as it doesnt make sense
};

class Derived: public Base {
public:    string name; int b;
    Derived(int x): name(move(to_string(x))),b(x),Base(x+5) {}
    Derived(Derived &src): Base(move(src)) {cout<<"der cpy &"<<endl;} // copy constr - using move on this calls Base move
    //Derived(const Derived &src) .......... // this cannot call move from base as it is a const lval ref even tho base mvoe doesn't change, 
    Derived(Derived &&src): Base(move(src)) {cout<<"der mv &&"<<endl;} // move constr, use move on base too as the name src is lvalue ref containing rval ref
    ~Derived() {cout<<"der dst"<<endl;}
};

int& bar(int inp){static int ret=-inp;return ret;} //returning reference of static var 'ret', can keep changing the var from somewhere else in the code

int bar1(int& a){return a=42;} // can be called only with a lval as lval ref can't be made from rval 
int bar2(const int& a) {return a;} // can now be called with both lval and rval
int bar3(int&& a) {return a;} // can only Be called with rvals

int main() {
    //Base* basePtr = new Derived(10);
    //shared_ptr<Derived> derivedPtr = make_shared<Derived>(20);
    //cout<<basePtr->a<<" "<<static_cast<Derived*>(basePtr)->b<<endl; // base ptr cannot access derived members, unless static cast
    //cout<<derivedPtr->a<<" "<<derivedPtr->b<<endl; // derived ptr can access both derived and base members
    //delete basePtr; // calls der dst, bse ds
    
    cout<<"BASE STUFF"<<endl;
    Base b1(50);
    Base b2 = b1; // will need b1 later, so just COPY it
    Base b3 = move(b2); // don't need b2, recursively move or steal its resources
    b3 = b1; // calls copy assng
    b3 = move(b1); // calls mov assng
    
    cout<<"DERIVED STUFF"<<endl;
    Derived d1(22);
    Derived d2 = d1;
    Derived d3 = move(d2);

    //Derived cpyDerivedPtr1 = *derivedPtr;
    //Derived cpyDerivedPtr2 = move(*derivedPtr);
    //shared_ptr<Derived> cpySharedDerivedPtr1 = derivedPtr;
    //shared_ptr<Derived> cpySharedDerivedPtr2 = move(derivedPtr);

    cout<<bar(59)<<" "; // print -59
    bar(100) = 7; // ret now carries '7'
    cout<<bar(0xDEAD)<<endl; // print 7

    int tmp = 555;
    cout<<tmp<<" "<<bar1(tmp)<<endl; // prints 555 42??
    //bar1(ref(8)); // can't call it like this
    cout<<bar2(tmp)<<" "<<bar2(8)<<endl; // prints 42 8 
    
    cout<<bar3(bar1(tmp))<<" "<<bar3(888)<<endl; // prints 42 888
    //bar3(tmp); // can't call it like this

    this_thread::sleep_for(chrono::seconds(10));
}

