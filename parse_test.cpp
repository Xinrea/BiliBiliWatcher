/*
Author: Xinrea
Description: input: uid num output: n'th newest dynamic info
*/
#include "card.h"
#include "cVideo.h"
#include "cDynam.h"
#include "cForward.h"
#include "network.h"
#include "up.h"

#include <iostream>

int main(int argc, char const *argv[])
{
    Network net;
    char request_prefix[128]="https://api.vc.bilibili.com/dynamic_svr/v1/dynamic_svr/space_history?host_uid=";
    net.request(strcat(request_prefix,argv[1]));
    Document d,p;
    std::cout << "Request complete" << std::endl;
    d.Parse(net.data().c_str());
    int type;
    if(argc<3){
        p.Parse(d["data"]["cards"][0]["card"].GetString());
        type = d["data"]["cards"][0]["desc"]["type"].GetInt();
    }
    else {
        p.Parse(d["data"]["cards"][strtol(argv[2],NULL,10)]["card"].GetString());
        type = d["data"]["cards"][strtol(argv[2],NULL,10)]["desc"]["type"].GetInt();
    }
    card* c0;
    std::cout << "Card Part Get, Type: " << type << std::endl;
    //type[1,转发][2,动态][8,投稿]
    switch(type){
        case 1:{
            c0 = new cForward;
            break;
        }
        case 2:{
            c0 = new cDynam;
            break;
        }
        case 8:{
            c0 = new cVideo;
            break;
        }
    }
    c0->set_data(p);
    // string content = "osascript -e 'display notification \"";
    // content+=c0->get("desc");
    // content+=string("\" with title \"");
    // content+=c0->get("title");
    // content+=string("\"'");
    // system(content.c_str());
    std::cout << c0->get("title") << std::endl;
    std::cout << c0->get("desc") << std::endl;
    return 0;
}
