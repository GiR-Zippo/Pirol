#ifndef __INTERPRETER__
#define __INTERPRETER__

#include "ClientSocket.h"
class ClientSocket;
class Interpreter
{
    public:
        Interpreter(ClientSocket *sock, const char *args);
        ~Interpreter();
    private:
        
        void GetDatas(std::string file);
        ClientSocket *_sock;
};
#endif
