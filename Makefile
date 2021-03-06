CPPFLAGS =  -I$(PWD)/include
all: bilibiliWatcher network_test parse_test
bilibiliWatcher : bilibiliWatcher.cpp network.cpp up.cpp cVideo.cpp cDynam.cpp cForward.cpp card.cpp
	g++ -o $(@) $(CPPFLAGS) bilibiliWatcher.cpp network.cpp up.cpp cVideo.cpp cDynam.cpp cForward.cpp card.cpp -lmysqlcppconn -std=c++11 -Wall
network_test : network.cpp network_test.cpp
	g++ -o $(@) network_test.cpp network.cpp -std=c++11 -Wall
parse_test : parse_test.cpp network.cpp up.cpp cVideo.cpp cDynam.cpp card.cpp
	g++ -o $(@) parse_test.cpp network.cpp up.cpp cVideo.cpp cDynam.cpp cForward.cpp card.cpp -std=c++11 -Wall
clean:
	rm network_test
	rm bilibiliWatcher
	rm parse_test