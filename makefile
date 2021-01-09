BOOST = -lboost_system -lpthread

# All Targets
all: Assignment3-Client

# Tool invocations
Assignment3-Client: bin/ConnectionHandler.o bin/Client.o bin/ClientToServer.o bin/ServerToClient.o $(BOOST)
	@echo 'Building target: BGSclient'
	@echo 'Invoking: C++ Linker'
	g++ -o Bin/Assignment3-Client bin/Client.o bin/ConnectionHandler.o bin/ClientToServer.o bin/ServerToClient.o $(BOOST)
	@echo 'Finished building target: BGSclient'
	@echo ' '


bin/Client.o: src/Client.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Client.o src/Client.cpp

bin/ConnectionHandler.o: src/ConnectionHandler.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/ConnectionHandler.o src/ConnectionHandler.cpp

bin/ClientToServer.o: src/ClientToServer.cpp.cpp.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/ClientToServer.o src/ClientToServer.cpp

bin/ServerToClient.o: src/ServerToClient.cpp.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/ServerToClient.o src/ServerToClient.cpp


#Clean the build directory
clean:
	rm -f bin/*


