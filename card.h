#pragma once
#include "up.h"
#include "rapidjson/document.h"
#include <string>
using std::string;
using rapidjson::Document;
class card {
    public:
        UP owner; 
        virtual void set_data(Document& content) = 0;
        virtual string get(const string& tag) = 0;
};