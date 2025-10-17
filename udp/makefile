.PHONY:all
all:udpclient udpserver
udpclient:udpclient.cpp
	g++ -o $@ $^ -std=c++17
udpserver:main.cpp
	g++ -o $@ $^ -std=c++17
.PHONY:clean
clean:
	rm -f udpclient udpserver
