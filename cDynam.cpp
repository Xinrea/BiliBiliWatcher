#include "cDynam.h"

void cDynam::set_data(Document& content, Document& own) {
    desc = string(content["description"].GetString());
    time = content["upload_time"].GetInt();
    owner.set_from_json(own);
}

string cDynam::get(const string& tag) {
    if(!tag.compare("desc"))return desc;
    if(!tag.compare("time"))return std::to_string(time);
    return string("");
}