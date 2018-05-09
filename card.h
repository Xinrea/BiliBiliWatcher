#include "up.h"
#include "rapidjson/document.h"
#include <string>
using std::string;
using rapidjson::Document;
class card {
    public:
        UP owner; 
        virtual void set_data(Document& content, Document& stat);
        virtual string get(const string& tag);
};