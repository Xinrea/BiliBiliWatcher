bilibiliWatcher : bilibiliWatcher.cpp network.cpp
	g++ -o $(@) bilibiliWatcher.cpp network.cpp -std=c++11 -Wall

network_test : network.cpp network_test.cpp
	g++ -o $(@) network_test.cpp network.cpp -std=c++11 -Wall

clean:
	rm network_test
	rm bilibiliWatcher