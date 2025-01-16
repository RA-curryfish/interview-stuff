#include<iostream>
#include<thread>
#include<queue>
#include<mutex>
#include<chrono>
#include<condition_variable>
/*****************************************************************************/
/* 2 producers and 1 consumer using 2 cond variables and max buffer length of 2*/
/*****************************************************************************/

// cv has a associated mutex lock to ensure that predicate is checked atomically
// while() is used to make sure the size is checked again after the cv is signalled??
// 2 cvs need to be used to make sure producers don't wake up producers

using namespace std;

int q_max_size=2;
queue<int> q;
mutex mtx;
condition_variable cv_not_full,cv_not_empty;

void produce(int id) {
	int i=0;
	unique_lock<mutex> lck(mtx,defer_lock);
	while(i<10) {
		lck.lock();
		while(q.size() == q_max_size) 
			cv_not_full.wait(lck);
		cout<<id<<":ADD:"<<q.size()<<endl;
		q.push(1);
		i++;
		cv_not_empty.notify_one();
		lck.unlock();
	}	
}

void consume() {
	int i =0;
	unique_lock<mutex> lck(mtx,defer_lock);
	while(true) {
		lck.lock();
		while(q.empty()) 
			cv_not_empty.wait(lck);	
		cout<<"REM"<<q.size()<<endl;
		q.pop();
		i++;
		cv_not_full.notify_one();
		lck.unlock();
	}
}

int main() {
	thread t1,t2,t3;
	t1 = thread(produce,0);
	t3 = thread(produce,1);
	t2 = thread(consume);
	cout<<"abc"<<endl;
	t1.detach();
	t3.detach();
	t2.detach();
	cout<<"xyz"<<endl;
	this_thread::sleep_for(chrono::seconds(100));
}
