#include "network.h"
#include "card.h"
#include "cDynam.h"
#include "cForward.h"
#include "cVideo.h"

#include "rapidjson/document.h"
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
using namespace rapidjson;
using namespace std;

int timegap;
string server;
string username;
string password;
int reconnection_times;
time_t now;
ofstream log;

string datatime(long int timestamp){
    char timebuffer[128];
    struct tm *t = localtime(((time_t *)&timestamp));
    strftime(timebuffer,128,"%F %T",t);
    return string(timebuffer);
}

void LOG(string x){
    log << "[" << datatime(now) << "] " << x << endl;
}

int main(int argc, char** argv) {
    /* log file */
    string logfilename;
    time(&now);
    tm* tm_t = localtime(&now);
    logfilename = string("log/")+to_string(tm_t->tm_year+1900)+"-"+to_string(tm_t->tm_mon+1)+"-"+to_string(tm_t->tm_mday)+".log";
    log.open(logfilename,ios::app);
    LOG("Log Init");
    /* load settings */
    LOG("Load settings");
    Document settings;
    ifstream set;
    string set_string;
    // * read setting file */
    set.open("config/bwSettings.json");
    stringstream buffer;
    buffer << set.rdbuf();
    set_string = buffer.str();
    cout << set_string << endl;
    settings.Parse(set_string.c_str());
    timegap = settings["basic"]["timegap"].GetInt();
    LOG(string("set timegap: ")+to_string(timegap));
    server = settings["basic"]["database"]["server"].GetString();
    LOG(string("set server: ")+server);
    username = settings["basic"]["database"]["username"].GetString();
    LOG(string("set username: ")+username);
    password = settings["basic"]["database"]["password"].GetString();
    LOG(string("set password: ")+password);
    reconnection_times = settings["basic"]["database"]["reconnect"].GetInt();
    LOG(string("set reconnection: ")+to_string(reconnection_times));
    set.close();
    /* connect to database */
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stat;
    sql::ResultSet *res;
    if(argc == 5)reconnection_times = atoi(argv[4]);
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect(server.c_str(),username.c_str(),password.c_str());
    stat = con->createStatement();
    /* reconnect to server */
    while(!con->isValid()&&reconnection_times--)con->reconnect();
    if(!con->isValid()){
        std::cerr << "connection failed" << std::endl;
        return 0;
    }
    /* acquire upid list */
    res = stat->executeQuery("SELECT upid FROM upinfo");
    vector<int> uplist;
    while(res->next()){
        std::cout << res->getInt(1) << std::endl;
        uplist.push_back(res->getInt(1));
    }
    Network net;
    string request_prefix="https://api.vc.bilibili.com/dynamic_svr/v1/dynamic_svr/space_history?host_uid=";
    while(true){
        for(auto i : uplist){
            LOG(string("begin get card: ")+to_string(i));
            net.request(request_prefix+to_string(i));
            Document d,p;
            d.Parse(net.data().c_str());
            /* analyze json data */
            int type;
            uint64_t dynamic_id;
            p.Parse(d["data"]["cards"][0]["card"].GetString());
            type = d["data"]["cards"][0]["desc"]["type"].GetInt();
            dynamic_id = d["data"]["cards"][0]["desc"]["dynamic_id"].GetUint64();
            card* c0;
            //type[1,转发][2,动态][8,投稿]
            switch(type){
                case 1:{
                    c0 = new cForward();
                    c0->set_data(p);
                    /* check connection */
                    while(!con->isValid()&&reconnection_times--)con->reconnect();
                    if(!con->isValid()){
                        std::cerr << "connection failed" << std::endl;
                        return 0;
                    }
                    res = stat->executeQuery(string("SELECT * FROM cards where cardid='")+to_string(dynamic_id)+"'");
                    if(res->rowsCount())break;// already exist in table
                    int timestamp = stoi(c0->get("time"));
                    LOG(string("get Forward_card: ")+datatime(timestamp));
                    // else insert new data into table
                    string sqlstat = string("INSERT INTO cards VALUES('")+to_string(dynamic_id)+"',"+c0->get("mid")+","+"'forward','"+c0->get("desc")+"','"+datatime(timestamp)+"')";
                    LOG(sqlstat);
                    int num = stat->executeUpdate(sqlstat);
                    break;
                }
                case 2:{
                    c0 = new cDynam();
                    c0->set_data(p);
                    /* check connection */
                    while(!con->isValid()&&reconnection_times--)con->reconnect();
                    if(!con->isValid()){
                        std::cerr << "connection failed" << std::endl;
                        return 0;
                    }
                    res = stat->executeQuery(string("SELECT * FROM cards where cardid='")+to_string(dynamic_id)+"'");
                    if(res->rowsCount())break;// already exist in table
                    int timestamp = stoi(c0->get("time"));
                    LOG(string("get Dynam_card: ")+datatime(timestamp));
                    // else insert new data into table
                    string sqlstat = string("INSERT INTO cards VALUES('")+to_string(dynamic_id)+"',"+c0->get("mid")+","+"'dynam','"+c0->get("desc")+"','"+datatime(timestamp)+"')";
                    LOG(sqlstat);
                    int num = stat->executeUpdate(sqlstat);
                    break;
                }
                case 8:{
                    c0 = new cVideo();
                    c0->set_data(p);
                    /* check connection */
                    while(!con->isValid()&&reconnection_times--)con->reconnect();
                    if(!con->isValid()){
                        std::cerr << "connection failed" << std::endl;
                        return 0;
                    }
                    res = stat->executeQuery(string("SELECT * FROM cards where cardid='")+to_string(dynamic_id)+"'");
                    if(res->rowsCount())break;// already exist in table
                    int timestamp = stoi(c0->get("time"));
                    LOG(string("get Video_card: ")+datatime(timestamp));
                    string sqlstat = string("INSERT INTO cards VALUES('")+to_string(dynamic_id)+"',"+c0->get("mid")+",'"+c0->get("title")+"','"+c0->get("desc")+"','"+datatime(timestamp)+"')";
                    LOG(sqlstat);
                    // else insert new data into table
                    int num = stat->executeUpdate(sqlstat);
                    break;
                }
            }
        }
        sleep(timegap);
    }
    log.close();
    delete res;
    delete stat;
    delete con;
    return 0;
}