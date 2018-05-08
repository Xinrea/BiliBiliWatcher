bilibiliWatcher : bilibiliWatcher.cpp network.cpp
	g++ -o $(@) bilibiliWatcher.cpp network.cpp -std=c++11 -Wall

clean:
	rm network_test