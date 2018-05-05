#include "network.h"

int main(){
    Network net;
    net.request("https://api.vc.bilibili.com/dynamic_svr/v1/dynamic_svr/space_history?host_uid=82389");
    return 0;
}