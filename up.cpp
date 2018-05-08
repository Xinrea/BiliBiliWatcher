#include "up.h"

UP::UP() {

}

void UP::set_from_json(Document& owner) {
    mid = owner["mid"].GetInt();
    name = string(owner["name"].GetString());
    face = string(owner["face"].GetString());
}
