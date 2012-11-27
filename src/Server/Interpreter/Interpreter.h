#ifndef __INTERPRETER__
#define __INTERPRETER__

#include "ClientSocket.h"
class ClientSocket;
class Interpreter
{
    public:
        Interpreter(ClientSocket *sock);
        ~Interpreter();
        void CheckCommand(const std::string& args);
        void ProcessCommand();
    private:
        
        void GetDatas(std::string file);

        void ReadStream();
        
        ClientSocket *_sock;
        std::string _file;
};
#endif
