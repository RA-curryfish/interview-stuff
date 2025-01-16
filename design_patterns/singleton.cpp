#include<iostream>
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
	Settings(int i) {x=i;}
	Settings(const Settings& s) = delete;
	Settings& operator=(const Settings& s) = delete;
public:
	static Settings* GetInstance(int i) {
		static Settings* instance = new Settings(i);	
		return instance; 
	}
	int GetX() {
		return this->x;
	}
};

int main() {
	Settings *s = Settings::GetInstance(5);
	Settings *s2 = Settings::GetInstance(23);
	cout<<s->GetX()<<" "<<s2->GetX()<<endl; // prints 5 5
	
	StaticSettings::CreateSS(-3);
	cout<<StaticSettings::GetX()<<" "<<StaticSettings::GetY()<<endl; // prints -3 9
	
	StaticSettings::CreateSS(4); // should not create new	
	cout<<StaticSettings::GetX()<<" "<<StaticSettings::GetY()<<endl; // prints -3 9
	
	return 0;
}
