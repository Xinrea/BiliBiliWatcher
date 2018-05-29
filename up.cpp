#include "up.h"

UP::UP() {

}

void UP::set_from_json(Document& owner) {
    if(owner.HasMember("user")){
        mid = owner["user"]["uid"].GetInt();
        if(owner["user"].HasMember("name"))name = string(owner["user"]["name"].GetString());
        if(owner["user"].HasMember("uname"))name = string(owner["user"]["uname"].GetString());
        if(owner["user"].HasMember("head_url"))face = string(owner["user"]["head_url"].GetString());
        if(owner["user"].HasMember("face"))face = string(owner["user"]["face"].GetString());
        return;
    }
    mid = owner["owner"]["mid"].GetInt();
    name = string(owner["owner"]["name"].GetString());
    face = string(owner["owner"]["face"].GetString());

}
