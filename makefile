CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS:=-lboost_system -lboost_thread -lpthread

all: Client
	g++ -o bin/Client bin/ConnectionHandler.o bin/ClientToServer.o bin/ServerToClient.o bin/Client.o $(LDFLAGS)

Client: bin/ConnectionHandler.o bin/ClientToServer.o bin/ServerToClient.o bin/Client.o

bin/ConnectionHandler.o: src/ConnectionHandler.cpp
	g++ $(CFLAGS) -o bin/ConnectionHandler.o src/ConnectionHandler.cpp


bin/ClientToServer.o: src/ClientToServer.cpp
	g++ $(CFLAGS) -o bin/ClientToServer.o src/ClientToServer.cpp


bin/ServerToClient.o: src/ServerToClient.cpp
	g++ $(CFLAGS) -o bin/ServerToClient.o src/ServerToClient.cpp


bin/Client.o: src/Client.cpp
	g++ $(CFLAGS) -o bin/Client.o src/Client.cpp

.PHONY: clean
clean:
	rm -f bin/*
