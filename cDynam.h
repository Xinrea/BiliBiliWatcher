#include "card.h"

class cDynam : public card {
    public:
        string desc;
        unsigned int time;
        void set_data(Document& content, Document& own);
        string get(const string& tag);
};