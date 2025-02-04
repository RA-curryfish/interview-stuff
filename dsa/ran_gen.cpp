#include<iostream>
#include<unordered_set>
#include<random>
#include<memory>

using namespace std;

class RandomGen{
private:
    int m_range;
    unordered_set<int> m_numSet;
    vector<int> m_numArr;
    void Swap(int& a, int& b) {
        int tmp = move(a);
        a = move(b);
        b = move(tmp);
    }
public:
    RandomGen(int N): m_range(N), m_numSet(), m_numArr(N,0){
        for(int i=1;i<=m_range;i++){
            m_numSet.insert(i);
            m_numArr[i-1] = i;
        }
    }
    void GetNum2() {
        random_device rd;
        mt19937 gen(rd()); 
        int n = m_numArr.size();
        uniform_int_distribution<> dist(0,n-1);
        int idx = dist(gen);        
        Swap(m_numArr[idx],m_numArr[n-1]);
        cout<<m_numArr[n-1]<<endl;
        m_numArr.pop_back();
    }
    void GetNum(){
        random_device rd;
        mt19937 gen(rd()); 
        uniform_int_distribution<> dist(1,m_numSet.size());
        int idx = dist(gen);
        auto el = m_numSet.begin();
        advance(el,idx-1); //
        cout<<*el<<endl;
        m_numSet.erase(el);
    }
    friend ostream& operator<<(ostream& os, RandomGen& r){
        for(auto& el: r.m_numSet){
            os<<el<<" ";
        }
        return os;
    }
};

int main(){
    int N = 10;
    unique_ptr<RandomGen> rgPtr = make_unique<RandomGen>(N);
//    cout<<*rgPtr<<endl;
    while(N>0){
//      rgPtr->GetNum();
        rgPtr->GetNum2();
        N--;
    }
    return 0;
}
