
#include "../include/ServerToClient.h"
using namespace std;

ServerToClient::ServerToClient(ConnectionHandler *connectionHandler, condition_variable &cv ,mutex &mutex):
connectionHandler(connectionHandler) ,cv(cv) ,mutex1(mutex), toTerminate(false) {

}

void ServerToClient::run() {
    while (!toTerminate){
        string message;

        char opCode[2];

        //gets opcode from user and converting it to short
        connectionHandler->getBytes(opCode, 2);
        short op = bytesToShort(opCode);

        string ans;
        if(op == 12){
            ans = "ACK";
            char opCode2[2];
            //gets the second opcode from user and converting it to short
            connectionHandler->getBytes(opCode2, 2);
            short op2 = bytesToShort(opCode2);
            ans = ans + " " + to_string(op2);

            //checks if it is special message we need to continue process
            if (op2 == 6 || op2 == 7 || op2 == 8 || op2 == 9 || op2 == 11){
                    string serverMessage;
                    connectionHandler->getFrameAscii(serverMessage, '\0');
                    cout << ans << endl;
                    cout << serverMessage << endl;
                }
            else if (op2 == 4){
                cout << ans << endl;
                toTerminate =   true;
            }else{
                //IF its empty string we need to pull the zeroByte
                string empty;
                connectionHandler->getLine(empty);
                cout << ans << endl;
            }

        }
        else if(op == 13){
            ans = "ERROR";
            //gets opcode from user and converting it to short
            char opCode2[2];
            connectionHandler->getBytes(opCode2, 2);
            short op2 = bytesToShort(opCode2);
            ans = ans + " " + to_string(op2);

            cout << ans << endl;
            cv.notify_all();// realese the keyboard
        }
    }

}

short ServerToClient::bytesToShort(char *bytesArr) {
    short result = (short)((bytesArr[0] & 0xff) << 8);
    result += (short)(bytesArr[1] & 0xff);
    return result;
}


