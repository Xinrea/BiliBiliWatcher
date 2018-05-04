#include <string>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

using std::string;
class Network {
	private:
		string target_url;
	public:
		explicit Network();
		Network(string url);
		~Network();
		bool request(string url);
	private:
		char* get_host_name(string url);
};