#include "Interpreter.h"
#include "Log.h"
#include <iostream>
#include <fstream>
#include <string>

Interpreter::Interpreter::Interpreter(ClientSocket* sock, const char* args): _sock(sock)
{
    if (strchr(args,'GET'))
    {
        std::string req = std::string(args);
        std::string file = req.substr(4);
        file = file.substr(0, file.find(" "));
        sLog->outString("%s", file.c_str());
        GetDatas(file);
    }
}

Interpreter::Interpreter::~Interpreter()
{

}

void Interpreter::GetDatas(std::string file)
{
    if (file.compare("/") == 0)
        file = "/index.html";
    
    file = "/var/www" + file;

    std::string line;
    sLog->outString("%s", file.c_str());
    ifstream myfile (file.c_str());
    
    if (myfile.is_open())
    {
        _sock->SendRequest("HTTP/1.1 200 OK");
        while ( myfile.good() )
        {
            getline (myfile,line);
            (void) _sock->send(line);
            (void) _sock->send("\n");
        }
        myfile.close();
    }
    
}

