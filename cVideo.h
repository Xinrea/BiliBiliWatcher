#pragma once
#include "card.h"

class cVideo : public card {
    public:
        unsigned int aid;// video id
        string title;
        string pic;
        string desc;
        unsigned int time;
        void set_data(Document& content);
        string get(const string& tag);
};