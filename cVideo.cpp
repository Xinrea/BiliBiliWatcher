#include "cVideo.h"

void cVideo::set_data(Document& content, Document& own) {
    title = string(content["title"].GetString());
    pic = string(content["pic"].GetString());
    desc = string(content["desc"].GetString());
    time = content["pubdate"].GetInt();
    owner.set_from_json(own);
}

string cVideo::get(const string& tag) {
    if(!tag.compare("title"))return title;
    if(!tag.compare("pic"))return pic;
    if(!tag.compare("desc"))return desc;
    if(!tag.compare("time"))return std::to_string(time);
    return string("");
}