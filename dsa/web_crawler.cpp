#include<iostream>
#include<thread>
#include<queue>
#include<vector>
#include<unordered_set>

class WebCrawler{
private:
    const std::string m_startUrl;
    std::string m_hostName;
    std::unordered_set<std::string> m_urlSet;
    bool SameHost(std::string url){
        //std::cout<<"checking "<<url<<std::endl;
        if(m_hostName.length() > url.length()) return false;
        for(int i=0;i<m_hostName.size();i++){
            if(url[i+8]!=m_hostName[i]) return false;
        }
        if(m_hostName.size()+8 < url.size() && url[m_hostName.size()+8]!='/') return false;// longer domain, so incorrect
        return true;
    }
public:
    WebCrawler(std::string&& hostUrl): m_startUrl(std::move(hostUrl)), m_urlSet() {
        m_hostName = "";
        for(int i=8;i<m_startUrl.size();i++){ // skip https..
            if(m_startUrl[i] == '/') // url ends
                break;
            m_hostName += m_startUrl[i];
        }
        std::cout<<"HostName "<<m_hostName<<std::endl;
    }
    std::vector<std::string> Crawl(){
        std::queue<std::string> urlQueue;
        urlQueue.push(m_startUrl);
        //m_urlSet.insert(m_startUrl);
        while(!urlQueue.empty()){
            std::string curUrl = urlQueue.front();
            urlQueue.pop();
            m_urlSet.insert(curUrl);
            std::vector<std::string> list = getUrls(curUrl);
            for(auto& l: list){
                if(m_urlSet.find(l) == m_urlSet.end() && SameHost(l)){ // q only contains valid urls, set always contains unique valid urls
                    urlQueue.push(l);
                }
            }
        }
        
        std::vector<std::string> validUrl;
        for(auto u: m_urlSet) validUrl.push_back(u);
        return validUrl;
    }
    std::vector<std::string> getUrls(std::string curUrl) {
        return {"https://olds.xyz","https://news.xyz", "https://news.xyz/this", "https://news.pqqq", "https://news.xyzz"};
    }
};

int main(){
    WebCrawler wc("https://news.xyz/that");
    std::vector<std::string> ans = wc.Crawl();
    for(auto& s: ans)
        std::cout<<s<<std::endl;
    return 0;
}
