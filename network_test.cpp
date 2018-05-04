#include "network.h"

int main(){
    Network net;
    net.request("https://api.vc.bilibili.com/dynamic_svr/v1/dynamic_svr/space_history?visitor_uid=475210&host_uid=82389&offset_dynamic_id=109154313202809631");
    return 0;
}