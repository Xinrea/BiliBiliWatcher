#include "network.h"
#include "rapidjson/document.h"

#include <iostream>
using namespace rapidjson;

int main() {
    Network net;
    net.request("https://api.vc.bilibili.com/dynamic_svr/v1/dynamic_svr/space_history?host_uid=82389");
    Document d;
    d.Parse(net.data().c_str());
    Value& s = d["data"]["has_more"];
    std::cout << s.GetInt() << std::endl;
    return 0;
}