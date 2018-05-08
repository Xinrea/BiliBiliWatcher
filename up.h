#include <string>
#include <vector>
using std::string;
using std::vector;
class UP {
    private:
        const unsigned int uid;
    public:
        explicit UP(unsigned int init_uid);
        ~UP();
        unsigned int get_uid() {return uid;}
};