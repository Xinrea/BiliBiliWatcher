#include "rapidjson/document.h"
#include <string>
using std::string;
using rapidjson::Document;

class UP {
    private:
        unsigned int mid;
        string name;
        string face;
    public:
        explicit UP();
        ~UP();
        unsigned int get_mid() {return mid;}
        string get_name() {return name;}
        string get_face() {return face;}
        void set_mid(unsigned int _mid) {
            mid = _mid;
        }
        void set_name(const string& _name) {
            name = _name;
        }
        void set_face(const string& _face) {
            face = _face;
        }
        void set_from_json(Document& owner);
};