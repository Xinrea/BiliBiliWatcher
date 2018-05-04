#include "network.h"

#include <iostream>
using std::clog;
using std::endl;

#define LOG(T) clog<<"NetworkLog: "<<T<<endl

Network::Network() {

}

Network::Network(string url): target_url(url) {

}

Network::~Network() {

}

bool Network::request(string url) {
    target_url = url;
    char *host_name = get_host_name(url);
    LOG(host_name);
    hostent *host_info = gethostbyname(host_name);
    in_addr host_addr;
    //DEBUG_BEGIN
    LOG("Resolve Host Name");
    for(auto i = host_info->h_addr_list; *i != nullptr; ++i) {
        host_addr.s_addr = *((unsigned int *)i);
        LOG(inet_ntoa(host_addr));
    }
    //DEBGU_END
    host_addr.s_addr = *((unsigned int *)host_info->h_addr_list[0]);

    //free memory
    delete[] host_name;
    return true;
}

// To find the domain in url
char* Network::get_host_name(string url) {
    char *host_name = new char[50];
    int begin = 0, end = 0, count = 0;
    bool search_begin = true;
    for(int i = 0; i < url.length(); ++i) {
        if(url[i] == '/')count++;
        if(count == 2 && search_begin) {
            begin = i;
            search_begin = false;
        }
        if(count == 3) {
            end = i;
            break;
        }
    }
    strcpy(host_name,url.substr(begin+1,end-begin-1).c_str());
    return host_name;
}