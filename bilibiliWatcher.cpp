#include "network.h"
#include "rapidjson/document.h"
#include <mysql_driver.h>
#include <mysql_connection.h>

#include <iostream>
using namespace rapidjson;

int main() {
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://mimori.app:3306","bw_admin","test");
    std::cout << "connected\n";
    std::cout << con->isValid() << std::endl;
    delete con;
    return 0;
}