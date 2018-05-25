#include "up.h"

UP::UP() {

}

void UP::set_from_json(Document& owner) {
    if(!owner.HasMember("owner")){
        mid = owner["user"]["uid"].GetInt();
        name = string(owner["user"]["name"].GetString());
        face = string(owner["user"]["head_url"].GetString());
        return;
    }
    mid = owner["owner"]["mid"].GetInt();
    name = string(owner["owner"]["name"].GetString());
    face = string(owner["owner"]["face"].GetString());

}
