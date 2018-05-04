#include "network.h"

#include <iostream>
using std::clog;
using std::endl;

#define LOG(T) clog<<"NetLog: "<<T<<endl

Network::Network() {

}

Network::Network(string url): target_url(url) {

}

Network::~Network() {

}

bool Network::request(string url) {
    /* Get Host IP Address */
    target_url = url;
    string host_name = get_host_name(url);
    LOG(host_name);
    hostent *host_info = gethostbyname(host_name.c_str());
    in_addr host_addr;
    /* DEBUG_BEGIN */
    LOG("Resolve Host Name");
    for(auto i = host_info->h_addr_list; *i != nullptr; ++i) {
        host_addr.s_addr = *((unsigned int *)i);
        LOG(inet_ntoa(host_addr));
    }
    /* DEBGU_END */
    host_addr.s_addr = *((unsigned int *)host_info->h_addr_list[0]);

    /* Create TCP Socket Use 80 Port (Http) */
    int sock_to_server;
    sockaddr_in target_server;
    sock_to_server = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock_to_server < 0){
        LOG(sock_to_server << " | Create Socket Error");
        return false;
    }
    /* Init sockaddr_in */
    memset(&target_server,0,sizeof(sockaddr));
    target_server.sin_family = AF_INET; //IPv4
    target_server.sin_addr.s_addr = host_addr.s_addr;
    target_server.sin_port = htons(80);
    /* Establish Connection */
    int res = connect(sock_to_server,(sockaddr*)&target_server,sizeof(target_server));
    if(res < 0){
        LOG(res << " | Connect Error");
        close(sock_to_server);
        return false;
    }
    /* Construct Request */
    string request_s = 
    "GET /dynamic_svr/v1/dynamic_svr/space_history?host_uid=82389 HTTP/1.1\n\rHost: " + host_name + "\n\r" +
    "Connection: keep-alive";
    LOG(request_s);
    res = send(sock_to_server,request_s.c_str(),request_s.length(),0);
    LOG("Send Finish");
    if(res != request_s.length()){
        LOG(res<<"/"<<request_s.length()<<" | Send Miss");
        close(sock_to_server);
        return false;
    }
    char buffer[2000];
    LOG("Recv Start");
    res = recv(sock_to_server,buffer,2000,0);
    LOG("Recv Finish");
    LOG("\n"<<buffer);
    /* Free Memory */
    close(sock_to_server);
    return true;
}

// To find the domain in url (http://xxx.xxx.com/xxx => xxx.xxx.com)
string Network::get_host_name(const string& url) {
    string host_name;
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
    host_name = url.substr(begin+1,end-begin-1);
    return host_name;
}