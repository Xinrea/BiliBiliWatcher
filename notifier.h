#pragma once
#include <string>

class Notifier {
    public:
        Notifier();
        void notify(std::string title, std::string message){
            notifyMM(title,message);
        }
    private:
    #ifdef __APPLE__
        void notifyMM(std::string title, std::string message);
    #else
        void notifyMM(std::string title, std::string message){

        }
    #endif
};