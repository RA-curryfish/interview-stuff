#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<fstream>

using namespace std;

class RW {
private:
    mutex m_wMutex;
    bool m_writing; // only 1 writer
    int m_readers; // multiple readers
//    mutex m_rMutex;
    string m_fileName;
    condition_variable m_wCV, m_rCV;
public:
    RW(string& file): m_fileName(file), m_writing(false), m_readers(0){
        //if(!m_file.is_open())
        //    m_file.open(file);
    }
    ~RW() = default;
    void Write(string&& s){
        {
            unique_lock<mutex> lck(m_wMutex);
            m_wCV.wait(lck,[&](){return m_readers == 0 && !m_writing;});
            m_writing = true;
        }
        fstream fileHandle(m_fileName,ios::out | ios::app);
        fileHandle<<s<<endl;
        fileHandle.close();
        {
            unique_lock<mutex> lck(m_wMutex);
            m_writing = false;
            m_rCV.notify_all();
            m_wCV.notify_one();
        }
    }
    void Read(int&& lines){
        {
            unique_lock<mutex> lck(m_wMutex);
            m_rCV.wait(lck,[&](){return !m_writing;}); // signalled by writer after done
            // allow everyone as all reading
            /*if(!m_file.is_open()) {
                cerr<<"unable to open"<<endl;
            */
            m_readers++;
        }
        fstream fileHandle(m_fileName,ios::in);
        string s;string total;
        while(getline(fileHandle,s) && lines>0){
            total += s;
            total += "\n";
            lines--;
        }
        fileHandle.close();
        {
            unique_lock<mutex> lck(m_wMutex);
            m_readers--;
            if(m_readers <= 0) {
                m_readers=0;    // need to signal writer saying done
                m_wCV.notify_one();
            }
            cout<<total;
        }   
    }
};

int main(){ 
    string name = "tmp";
    shared_ptr<RW> rwPtr = make_shared<RW>(name);
    thread t1,t2,t3,t4,t5;
    t1 = thread(&RW::Read,rwPtr.get(),1);
    t2 = thread(&RW::Read,rwPtr.get(),2);
    t3 = thread(&RW::Write,rwPtr.get(),"THIS IS NICE");
    t4 = thread(&RW::Write,rwPtr.get(),"THIS IS ALSO NICE");
    t5 = thread(&RW::Read,rwPtr.get(),10);
    
    t1.join();t2.join();
    t3.join();
    t4.join();t5.join();
    return 0;
}
