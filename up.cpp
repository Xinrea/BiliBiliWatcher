#include "up.h"

UP::UP() {

}

void UP::set_from_json(Document& owner) {
    if(owner["owner"].HasMember("mid")){// video card
        mid = owner["owner"]["mid"].GetInt();
        name = string(owner["owner"]["name"].GetString());
        face = string(owner["owner"]["face"].GetString());
    }
    else {
        mid = owner["uid"].GetInt();
        name = string(owner["owner"]["name"].GetString());
        face = string(owner["owner"]["head_url"].GetString());
    }

}
