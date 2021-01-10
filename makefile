CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS:=-lboost_system -lboost_thread -lpthread

all: BGRSclient
	g++ -o bin/BGRSclient bin/ConnectionHandler.o bin/ClientToServer.o bin/ServerToClient.o bin/BGRSclient.o $(LDFLAGS)

BGRSclient: bin/ConnectionHandler.o bin/ClientToServer.o bin/ServerToClient.o bin/BGRSclient.o

bin/ConnectionHandler.o: src/ConnectionHandler.cpp
	g++ $(CFLAGS) -o bin/ConnectionHandler.o src/ConnectionHandler.cpp


bin/ClientToServer.o: src/ClientToServer.cpp
	g++ $(CFLAGS) -o bin/ClientToServer.o src/ClientToServer.cpp


bin/ServerToClient.o: src/ServerToClient.cpp
	g++ $(CFLAGS) -o bin/ServerToClient.o src/ServerToClient.cpp


bin/BGRSclient.o: src/BGRSclient.cpp
	g++ $(CFLAGS) -o bin/BGRSclient.o src/BGRSclient.cpp

.PHONY: clean
clean:
	rm -f bin/*
