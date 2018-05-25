#include "cDynam.h"

void cDynam::set_data(Document& content) {
    desc = string(content["item"]["description"].GetString());
    time = content["item"]["upload_time"].GetInt();
    owner.set_from_json(content);
}

string cDynam::get(const string& tag) {
    if(!tag.compare("mid"))return std::to_string(owner.get_mid());
    if(!tag.compare("name"))return owner.get_name();
    if(!tag.compare("face"))return owner.get_face();
    if(!tag.compare("desc"))return desc;
    if(!tag.compare("time"))return std::to_string(time);
    return string("");
}