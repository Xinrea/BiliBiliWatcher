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

int main() {
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stat;
    sql::ResultSet *res;
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("*","*","*");
    stat = con->createStatement();
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