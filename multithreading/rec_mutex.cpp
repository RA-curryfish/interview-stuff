#include<thread>
#include<mutex>
#include<iostream>

using namespace std;

class Test {
	static recursive_mutex mtx;

public:
	void add(int a,int b) {
		lock_guard<recursive_mutex> lck(mtx);
		cout<<a+b<<endl;
	}
	static void sub(int a,int b) {
		lock_guard<recursive_mutex> lck(mtx);
		cout<<a-b<<endl;
	}

	void both(int a,int b) {
		lock_guard<recursive_mutex> lck(mtx);
		sub(a,b);
		this->add(a,b);
	}
};

recursive_mutex Test::mtx;

int main() {
	thread t1,t2,t3;
	Test tObj = Test();
	
	//t1 = thread(&Test::sub,10,20); // calling static function
	//t2 = thread(&Test::add,&tObj,1,1); // calling non-static function with reference to object
	t3 = thread(&Test::both,&tObj,20,10); 
	t1 = thread(&Test::both,&tObj,0,0); 
	
	t1.join();
	//t2.join();
	t3.join();
	return 0;
}
