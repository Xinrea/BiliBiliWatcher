#include "card.h"

class cVideo : card {
    public:
        unsigned int aid;// video id
        string title;
        string pic;
        string desc;
        unsigned int time;
        void set_data(Document& content, Document& stat);
        string get(const string& tag);
};