
#include <ClientToServer.h>
#include <ConnectionHandler.h>

#include "ClientToServer.h"
#include <boost/algorithm/string.hpp>

using namespace std;


ClientToServer::ClientToServer(ConnectionHandler *connectionHandler, condition_variable &cv ,mutex &mutex) :
connectionHandler(connectionHandler), cv(cv) ,mutex1(mutex),toTerminate(false) {
}


void ClientToServer::run() {
    while (!toTerminate) {
        const short bufsize = 1024;
        char buf[bufsize];
        cin.getline(buf, bufsize);
        string line(buf);

        vector<string> splitted;

        boost::split(splitted, line, boost::is_any_of(" "));

        char opCode[2];

        if (splitted[0] == "ADMINREG") {
            string userName(splitted[1]);
            string password(splitted[2]);
            shortToBytes(1, opCode);

            connectionHandler->sendBytes(opCode, 2);
            connectionHandler->sendLine(userName);
            connectionHandler->sendLine(password);
        }
            else if (splitted[0] == "STUDENTREG"){
                string userName(splitted[1]);
                string password(splitted[2]);
                shortToBytes(2, opCode);
                connectionHandler->sendBytes(opCode, 2);
                connectionHandler->sendLine(userName);
                connectionHandler->sendLine(password);
        }else if(splitted[0] == "LOGIN"){
            string userName(splitted[1]);
            string password(splitted[2]);
            shortToBytes(3, opCode);
            connectionHandler->sendBytes(opCode, 2);
            connectionHandler->sendLine(userName);
            connectionHandler->sendLine(password);

        }else if(splitted[0] == "LOGOUT") {
            shortToBytes(4, opCode);
            connectionHandler->sendBytes(opCode, 2);
            unique_lock<mutex> lock{mutex1};
            cv.wait(lock);
        }
        else if (splitted[0] == "COURSEREG"){
                //sends the opCode
                shortToBytes(5, opCode);
                connectionHandler->sendBytes(opCode, 2);

                //sends the courseNum
                int intCourseNum = stoi(splitted[1]);
                short courseNum = (short)intCourseNum;
                char bytesShortNum[2];
                shortToBytes(courseNum,bytesShortNum);
                connectionHandler->sendBytes(bytesShortNum , 2);

         }
        else if (splitted[0] == "KDAMCHECK"){
            //sends the opCode
            shortToBytes(6, opCode);
            connectionHandler->sendBytes(opCode, 2);

            //sends the courseNum
            int intCourseNum = stoi(splitted[1]);
            short courseNum = (short)intCourseNum;
            char bytesShortNum[2];
            shortToBytes(courseNum,bytesShortNum);
            connectionHandler->sendBytes(bytesShortNum , 2);

        }
        else if (splitted[0] == "COURSESTAT"){
            //sends the opCode
            shortToBytes(7, opCode);
            connectionHandler->sendBytes(opCode, 2);

            //sends the courseNum
            int intCourseNum = stoi(splitted[1]);
            short courseNum = (short)intCourseNum;
            char bytesShortNum[2];
            shortToBytes(courseNum,bytesShortNum);
            connectionHandler->sendBytes(bytesShortNum , 2);

        }
        else if (splitted[0] == "STUDENTSTAT") {
            //sends the opCode
            shortToBytes(8, opCode);
            connectionHandler->sendBytes(opCode, 2);

            //sends the username
            string userName(splitted[1]);
            connectionHandler->sendLine(userName);
        }
        else if (splitted[0] == "ISREGISTERED"){
        //sends the opCode
        shortToBytes(9, opCode);
             connectionHandler->sendBytes(opCode, 2);

        //sends the courseNum
        int intCourseNum = stoi(splitted[1]);
        short courseNum = (short)intCourseNum;
        char bytesShortNum[2];
        shortToBytes(courseNum,bytesShortNum);
        connectionHandler->sendBytes(bytesShortNum , 2);
        }
        else if (splitted[0] == "UNREGISTER"){
        //sends the opCode
        shortToBytes(10, opCode);
        connectionHandler->sendBytes(opCode, 2);

            //sends the courseNum
            int intCourseNum = stoi(splitted[1]);
            short courseNum = (short)intCourseNum;
            char bytesShortNum[2];
            shortToBytes(courseNum,bytesShortNum);
            connectionHandler->sendBytes(bytesShortNum , 2);
    }
    else if (splitted[0] == "MYCOURSES"){
        //sends the opCode
        shortToBytes(11, opCode);
        connectionHandler->sendBytes(opCode, 2);
    }

        }
    }


void ClientToServer::shortToBytes(short num, char* bytesArr) {
    bytesArr[0] = ((num >> 8) & 0xFF);
    bytesArr[1] = (num & 0xFF);
}

void ClientToServer::setToTerminate(bool toTerminate) {
    ClientToServer::toTerminate = toTerminate;
}
