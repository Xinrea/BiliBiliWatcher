#include "up.h"

UP::UP() {

}

void UP::set_from_json(Document& owner) {
    if(owner.HasMember("mid")){// video card
        mid = owner["mid"].GetInt();
        name = string(owner["name"].GetString());
        face = string(owner["face"].GetString());
    }
    else {
        mid = owner["uid"].GetInt();
        name = string(owner["name"].GetString());
        face = string(owner["head_url"].GetString());
    }

}
