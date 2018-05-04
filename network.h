#include <string>
using std::string;
class Network {
 private:
  string target_url;
 public:
  Network();
  Network(string url);
  ~Network();
};