#include<iostream>
#include<memory>
#include<thread>
// virtual constructors don't exist, but virtual destructors do
using namespace std;

class Base {
public:    int a;
    Base(int x): a(x) {}
    virtual ~Base() {cout<<"bse dst"<<endl;} // need virtual destructor to delete derived thru base ptr. but no need for virtual constructor as it doesnt make sense
};

class Derived: public Base {
public:    int b;
    Derived(int x): b(x),Base(x+5) {}
    ~Derived() {cout<<"der dst"<<endl;}
};

class Game {
public:
string name;
int cost;
Game(): name(""),cost(0){}; //declaring constructor
Game(string &&nameParam, int costParam): name(move(nameParam)),cost(costParam){}
~Game() {cout<<"game destructor"<<endl;}
};

class PCGame: public Game{
public:
int tax;
PCGame(): Game(){};
PCGame(string &&nameParam,int costParam,int taxParam): tax(),Game(move(nameParam),costParam+taxParam) {}
};

// the obj isn't copied but just referenced, no destructor called
void fooLRef(Game &g){
    cout<<"lref "<<g.name<<" "<<g.cost<<endl;
    g.name = "FAKE";
    g.cost = 0;
}

void fooRRef(Game &&g) {
    cout<<"rref "<<g.name<<" "<<g.cost<<endl;
    g.name = "FAKE2";
    g.cost = 0;
}
// since object is copied to the param, the destructor is called on 'G'
void foo(Game g){
    cout<<"do something"<<endl;
    g.name = "fake 3";
    g.cost = 10000;
}

int main() {
    Base* basePtr = new Derived(10);
    shared_ptr<Derived> derivedPtr = make_shared<Derived>(20);
    cout<<basePtr->a<<" "<<static_cast<Derived*>(basePtr)->b<<endl; // base ptr cannot access derived members, unless static cast
    cout<<derivedPtr->a<<" "<<derivedPtr->b<<endl; // derived ptr can access both derived and base members
    delete basePtr; // calls der dst, bse dst*/
    PCGame pcGame("Pokemon",100,5);
    
}

