#include<thread>
#include<mutex>
#include<iostream>

using namespace std;
static int ctr = 0; 
mutex mtx;

void fn(){
	unique_lock<mutex> lck(mtx);
	cout<<"hello"<<ctr<<endl;
	ctr++;
}

int main(){
	thread t1,t2,t3; 
	t1 = thread(fn); t2 = thread(fn); t3 = thread(fn);
	t1.join();
	t2.join();
	t3.join();
	cout<<"done"<<endl;
	return 0;
}
