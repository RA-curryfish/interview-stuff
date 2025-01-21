#include<iostream>
#include<mutex>
#include<memory>
#include<thread>
#include<vector>
#include<algorithm>
#include<chrono>
#include<condition_variable>

using namespace std;

class Client {
    public:
    virtual void getUpdate(int v) {}
};

class GameUpdate {
    static int version;
    static mutex mtx;
    vector<shared_ptr<Client>> clients; // shared_ptr clients
    public:
    
    static condition_variable cv_update;
    void clock() { // update comes every 3 sec
        while(true) {
            this_thread::sleep_for(chrono::seconds(3));
            version++;
            cv_update.notify_one();
        }
    }
    
    void addClient(shared_ptr<Client> client) {
        unique_lock<mutex> lck(mtx);
        clients.push_back(client);
    }

    void removeClient(shared_ptr<Client> client) {
        unique_lock<mutex> lck(mtx);
        clients.erase(remove(clients.begin(),clients.end(),client),clients.end());
    }
    
    void notifyClient() {
        for(auto& c: clients) {
            c->getUpdate(version);
        }
    }

    int curVersion() { return version;}
};

mutex GameUpdate::mtx;
int GameUpdate::version=0;
condition_variable GameUpdate::cv_update;

class Steam: public Client {
    public:
    void getUpdate(int v) override {
        cout<<"steam dloadinng "<<v<<endl;
    }
};

class Epic: public Client {
    public:
    void getUpdate(int v) override {
        cout<<"Epic dloadinng "<<v<<endl;
    }
};

int main() {
    shared_ptr<GameUpdate> gu = make_shared<GameUpdate>(); // create observer and subject sharedptrs
    shared_ptr<Client> s1 = make_shared<Steam>();
    shared_ptr<Client> s2 = make_shared<Epic>();
    
    thread t2(&GameUpdate::clock,gu); // start clock

    thread t1(&GameUpdate::addClient,gu,s2); // add clients
    gu->addClient(s1);

    t1.join();
    mutex umtx;
    unique_lock<mutex> lck(umtx,defer_lock);
    int i=0;
    while(i++<10){
        gu->cv_update.wait(lck); // wait for update trigger
        gu->notifyClient();
        if(gu->curVersion()>3) gu->removeClient(s2);
    }
    this_thread::sleep_for(chrono::seconds(100));
    return 0;
}
