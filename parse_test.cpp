#include "card.h"
#include "cVideo.h"
#include "cDynam.h"
#include "network.h"
#include "up.h"

#include <iostream>

int main(int argc, char const *argv[])
{
    Network net;
    net.request("https://api.vc.bilibili.com/dynamic_svr/v1/dynamic_svr/space_history?host_uid=82389");
    Document d,p;
    d.Parse(net.data().c_str());
    p.Parse(d["data"]["cards"]["0"]["card"].GetString());
    card* c0 = new cVideo;
    c0->set_data(p,p["owner"]);
    std::cout << c0->get("desc") << std::endl;
    return 0;
}
