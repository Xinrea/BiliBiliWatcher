#pragma once
#include "card.h"

class cForward : public card {
    public:
        string desc;
        unsigned int time;
        void set_data(Document& content);
        string get(const string& tag);
};