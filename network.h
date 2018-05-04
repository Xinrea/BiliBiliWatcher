#ifndef BILIBILIWATCHER_NETWORK_H_
#define BILIBILIWATCHER_NETWORK_H_

#include <string>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using std::string;
class Network {
	private:
		string target_url;
		int json_length;
		char* json_data;
	public:
		explicit Network();
		Network(string url);
		~Network();
		bool request(string url);
		int length() {return json_length;}
		char* data() {return json_data;}
	private:
		string get_host_name(const string& url);
};

#endif