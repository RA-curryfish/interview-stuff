#include<iostream>
#include<thread>
#include<queue>
#include<mutex>
#include<chrono>
#include<condition_variable>
/*****************************************************************************/
/* 2 producers and 2 consumer using 2 cond variables and max buffer length of 2*/
/*****************************************************************************/

// cv has a associated mutex lock to ensure that predicate is checked atomically
// while() is used to make sure the size is checked again after the cv is signalled??
// 2 cvs need to be used to make sure producers don't wake up producers

using namespace std;

int q_max_size=2;
mutex mtx;
condition_variable cv_not_full,cv_not_empty;

void produce(int id,queue<int> &q) {
	int i=0;
	unique_lock<mutex> lck(mtx,defer_lock);
	while(i<5) {
		lck.lock();
		//while(q.size() == q_max_size)  // OR without the while, use a predicate in the wait()
		//	cv_not_full.wait(lck); 
		cv_not_full.wait(lck,[&q](){return q.size() != q_max_size;}); // wait until predicate becomes true and pass reference of q
		cout<<id<<":ADD:"<<q.size()<<endl;
		q.push(1);
		i++;
		lck.unlock(); // unlock before notifyiNg the threads so they don't immediately block 
		cv_not_empty.notify_one();
	}	
}

void consume(int id,queue<int> &q) {
	int i =0;
	unique_lock<mutex> lck(mtx,defer_lock);
	while(true) {
		lck.lock();
		//while(q.empty()) 
		//	cv_not_empty.wait(lck); 
		cv_not_empty.wait(lck,[&q](){return !q.empty();});	
		cout<<id<<":REM:"<<q.size()<<endl;
		q.pop();
		i++;
		lck.unlock();
		cv_not_full.notify_one();
	}
}

int main() {
	queue<int> q;
	thread t1,t2,t3,t4;
	t1 = thread(produce,0,ref(q));
	t3 = thread(produce,1,ref(q));
	t2 = thread(consume,2,ref(q));
	t4 = thread(consume,3,ref(q));

	cout<<"abc"<<endl;
	t1.detach();
	t3.detach();
	t2.detach();
	t4.detach();
	cout<<"xyz"<<endl;
	this_thread::sleep_for(chrono::seconds(100));
}
