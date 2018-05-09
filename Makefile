bilibiliWatcher : bilibiliWatcher.cpp network.cpp
	g++ -o $(@) bilibiliWatcher.cpp network.cpp -std=c++11 -Wall

network_test : network.cpp network_test.cpp
	g++ -o $(@) network_test.cpp network.cpp -std=c++11 -Wall
parse_test : parse_test.cpp network.cpp up.cpp cVideo.cpp cDynam.cpp
	g++ -o $(@) parse_test.cpp network.cpp up.cpp cVideo.cpp cDynam.cpp -std=c++11 -Wall
clean:
	rm network_test
	rm bilibiliWatcher
	rm parse_test