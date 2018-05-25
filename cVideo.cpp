#include "cVideo.h"

void cVideo::set_data(Document& content) {
    aid = content["stat"]["aid"].GetInt();
    title = string(content["title"].GetString());
    pic = string(content["pic"].GetString());
    desc = string(content["desc"].GetString());
    time = content["pubdate"].GetInt();
    owner.set_from_json(content);
}

string cVideo::get(const string& tag) {
    if(!tag.compare("mid"))return std::to_string(owner.get_mid());
    if(!tag.compare("name"))return owner.get_name();
    if(!tag.compare("face"))return owner.get_face();
    if(!tag.compare("aid"))return std::to_string(aid);
    if(!tag.compare("title"))return title;
    if(!tag.compare("pic"))return pic;
    if(!tag.compare("desc"))return desc;
    if(!tag.compare("time"))return std::to_string(time);
    return string("");
}