#include<iostream>
#include<thread>
#include<vector>
#include<mutex>
#include<condition_variable>

using namespace std;

class RD {
private:
    bool m_repTurn;
    uint8_t m_occLim;
    uint8_t m_occCnt;
    mutex mtx;
    condition_variable cv;
public:
    RD(int n): m_occLim(n), m_occCnt(0) {}
    bool CanEnter(bool& rep){
        return m_occCnt==0 || (m_repTurn==rep && m_occCnt<m_occLim);
    }
    void Occupy(bool& rep){
        if(rep)
            cout<<"REP USING"<<endl;
        else
            cout<<"DEM USING"<<endl;
        this_thread::sleep_for(chrono::seconds(3));
    }
    void TryEnter(bool&& rep){
        unique_lock<mutex> lck(mtx,defer_lock);
        lck.lock();
        cv.wait(lck,[&](){return CanEnter(rep);}); // no one is inside OR person who is inside is same as requesting and we have space
        // everyone who reaches here are same
        if(m_occCnt == 0){
            m_repTurn = rep; // set turn
        }
        m_occCnt++; // inc cnt
        lck.unlock();

        Occupy(rep); // do stuff
        
        lck.lock(); // reaquire lock, decrement stuff
        m_occCnt--;
        lck.unlock();
        cv.notify_all(); // notify
    }
};

int main() {
    unique_ptr<RD> rdPtr = make_unique<RD>(3);
    thread t1,t2,t3,t4,t5;
    t1 = thread(&RD::TryEnter,rdPtr.get(),1); // 1 - rep, 0 - dem
    this_thread::sleep_for(chrono::seconds(4));
    t2 = thread(&RD::TryEnter,rdPtr.get(),0);
    t3 = thread(&RD::TryEnter,rdPtr.get(),1);
    //this_thread::sleep_for(chrono::seconds(4));
    t4 = thread(&RD::TryEnter,rdPtr.get(),0);
    t5 = thread(&RD::TryEnter,rdPtr.get(),1);
    t1.join();t3.join();t5.join();
    t2.join();t4.join();
    return 0;
}
