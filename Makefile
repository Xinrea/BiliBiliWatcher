network_test : network_test.cpp network.cpp
	g++ -o $(@) network_test.cpp network.cpp -std=c++11 -Wall

clean:
	rm network_test