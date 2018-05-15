#include "card.h"
#include "cVideo.h"
#include "cDynam.h"
#include "network.h"
#include "up.h"
#include "notifier.h"

#include <iostream>

int main(int argc, char const *argv[])
{
    Network net;
    net.request("https://api.vc.bilibili.com/dynamic_svr/v1/dynamic_svr/space_history?host_uid=3100644");
    Document d,p;
    std::cout << "request complete" << std::endl;
    d.Parse(net.data().c_str());
    p.Parse(d["data"]["cards"][0]["card"].GetString());
    card* c0 = new cVideo;
    c0->set_data(p);
    // string content = "osascript -e 'display notification \"";
    // content+=c0->get("desc");
    // content+=string("\" with title \"");
    // content+=c0->get("title");
    // content+=string("\"'");
    // system(content.c_str());
    Notifier no;
    no.notify(c0->get("title"),c0->get("desc"));
    std::cout << c0->get("title") << std::endl;
    std::cout << c0->get("desc") << std::endl;
    return 0;
}
