#include<iostream>
#include<mutex>
#include<thread>

using namespace std;

class StaticSettings {
private:
	static int x;
	inline static int y = 10;
public:
	static void CreateSS(int i) {
		static bool done = false;
		if(!done) {
			done = true;
			x=i;
			y = x*x;
		}
	}
	static int GetX() {
		return x;
	}
	static int GetY() {
		return y;
	}
};
int StaticSettings::x = 0; // private member outside??

class Settings {
private:
	int x;
	static mutex mtx;
	static Settings* sing;
	Settings(int i) {x=i;}
	Settings(const Settings& s) = delete;
	Settings& operator=(const Settings& s) = delete;
public:
	static Settings* GetInstance(int i) {
		unique_lock<mutex> lck(mtx);
//		static Settings* instance = new Settings(i); // this is thread safe? 	
		if(sing == NULL) {
			sing = new Settings(i);
		}
		lck.unlock();
		return sing; 
	}
	int GetX() {
		return this->x;
	}
};
mutex Settings::mtx;
Settings* Settings::sing = NULL;

void CreateInstance1(int i) {
	Settings *s = Settings::GetInstance(i);
	cout<<s->GetX()<<endl; // prints same values
}

void CreateInstance2(int i) {
	Settings *s = Settings::GetInstance(i);
	cout<<s->GetX()<<endl; // prints same values
}


int main() {
	thread t1,t2;	
	t1 = thread(CreateInstance2,5);
	t2 = thread(CreateInstance1,23);
	t1.join();
	t2.join();
	StaticSettings::CreateSS(-3);
	cout<<StaticSettings::GetX()<<" "<<StaticSettings::GetY()<<endl; // prints -3 9
	
	StaticSettings::CreateSS(4); // should not create new	
	cout<<StaticSettings::GetX()<<" "<<StaticSettings::GetY()<<endl; // prints -3 9
	
	return 0;
}
