#include "network.h"
#include "rapidjson/document.h"
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <iostream>
#include <vector>
using namespace rapidjson;
using namespace std;

int main(int argc, char** argv) {
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stat;
    sql::ResultSet *res;
    int reconnection_times = 5;
    if(argc == 5)reconnection_times = atoi(argv[4]);
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect(argv[1],argv[2],argv[3]);
    stat = con->createStatement();
    /* reconnection to server */
    while(!con->isValid()&&reconnection_times)con->reconnect();
    if(!con->isValid()){
        std::cerr << "connection failed" << std::endl;
        return 0;
    }
    /* aquire upid list */
    res = stat->executeQuery("SELECT upid FROM upinfo");
    vector<int> uplist;
    while(res->next()){
        std::cout << res->getInt(1) << std::endl;
        uplist.push_back(res->getInt(1));
    }
    
    
    //TODO: insert cardinfo into table by uplist
    delete res;
    delete stat;
    delete con;
    return 0;
}