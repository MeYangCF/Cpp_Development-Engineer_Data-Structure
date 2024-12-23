/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2024 24-12-23 下午2:23
@description:
*/

#include <iostream>
#include <string>
#include <set>
#include <list>
#include <map>
using namespace std;

#include "md5.h"
using uint = unsigned int;

class PhscialHost;

class VirtualHost{
public:
    VirtualHost(string ip, PhscialHost* p)
        : ip_(ip)
        , phscialHost_(p){
        md5_ = ::getMD5(ip_.c_str());
    }
    bool operator<(const VirtualHost& host) const{
        return md5_ < host.md5_;
    }
    bool operator==(const VirtualHost& host) const{
        return ip_ == host.ip_;
    }
    uint getMD5() const{
        return md5_;
    }
    const PhscialHost* getPhscialHost() const{
        return phscialHost_;
    }

private:
    string ip_;
    uint md5_;
    PhscialHost* phscialHost_;
};

class PhscialHost{
public:
    PhscialHost(string ip, int vnumber)
        : ip_(ip){
        for(int i = 0; i < vnumber; i++){
            virtualHosts_.emplace_back(
                    ip + '#' + ::to_string(i),
                    this);
        }
    }
    string getIP() const{
        return ip_;
    }
    const list<VirtualHost>& getVirtualHosts() const{
        return virtualHosts_;
    }
private:
    string ip_;
    list<VirtualHost> virtualHosts_;
};

class ConsistentHash{
public:
    void addHost(PhscialHost& host){
        auto list = host.getVirtualHosts();
        for(auto host : list)
            hashCircle_.insert(host);
    }
    void delHost(PhscialHost& host){
        auto list = host.getVirtualHosts();
        for(auto host : list){
            auto it = hashCircle_.find(host);
            if(it != hashCircle_.end())
                hashCircle_.erase(it);
        }
    }
    string getHost(string clientip) const{
        uint md5 = ::getMD5(clientip.c_str());
        for(auto vhost : hashCircle_){
            if(vhost.getMD5() > md5)
                return vhost.getPhscialHost()->getIP();
        }
        return hashCircle_.begin()->getPhscialHost()->getIP();
    }
private:
    set<VirtualHost> hashCircle_;
};

void ShowConsistentHash(ConsistentHash& chash);

int main(){
    PhscialHost host1("10.117.124.10", 150);
    PhscialHost host2("10.117.124.20", 150);
    PhscialHost host3("10.117.124.30", 150);

    ConsistentHash chash;
    chash.addHost(host1);
    chash.addHost(host2);
    chash.addHost(host3);

    ShowConsistentHash(chash);

    // 模拟host1有故障
    chash.delHost(host1);

    ShowConsistentHash(chash);
    return 0;
}

void ShowConsistentHash(ConsistentHash& chash){
    list<string> iplists{
            "192.168.1.123",
            "192.168.1.12",
            "192.168.1.13",
            "192.168.1.23",
            "192.168.1.54",
            "192.168.1.89",
            "192.168.1.21",
            "192.168.1.27",
            "192.168.1.49",
            "192.168.1.145",
            "192.168.2.34",
            "192.168.6.78",
            "192.168.2.90",
            "192.168.4.5"
    };
    map<string, list<string>> logMap;
    for (auto clientip : iplists){
        string host = chash.getHost(clientip);
        logMap[host].emplace_back(clientip);
    }
    for (auto pair : logMap){
        cout << "物理主机:" << pair.first << endl;
        cout << "客户端映射的数量:" << pair.second.size() << endl;
        for (auto ip : pair.second)
            cout << ip << endl;
        cout << "----------------------------" << endl;
    }
    cout << endl;
}