network_test : network_test.cpp network.cpp
	g++ -o $(@) network_test.cpp network.cpp

clean:
	rm network_test