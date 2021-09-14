
#ifndef CLIENT_SERVERTOCLIENT_H
#define CLIENT_SERVERTOCLIENT_H

#include <mutex>
#include <condition_variable>
#include "ConnectionHandler.h"

using namespace std;

class ServerToClient {
private:
    ConnectionHandler *connectionHandler;
    condition_variable &cv;
    mutex &mutex1;
    bool toTerminate;

public:
    ServerToClient(ConnectionHandler *connectionHandler,condition_variable &cv ,mutex &mutex1);
    void run();
    short bytesToShort(char* bytesArr);

};


#endif //CLIENT_SERVERTOCLIENT_H
