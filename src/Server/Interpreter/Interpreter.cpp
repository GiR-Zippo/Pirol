#include "Interpreter.h"
#include "Configuration.h"
#include <ClientSocket.h>

#include "Log.h"
#include <iostream>
#include <fstream>
#include <string>

Interpreter::Interpreter::Interpreter(ClientSocket* sock, const char* args): _sock(sock)
{
    if (strchr(args,'GET'))
    {
        std::string req = std::string(args);
        std::string file = req.substr(req.find(" ")+1);
        file = file.substr(0, file.find(" "));
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
    
    file = sConfiguration->GetStringConfig(WWW_DATA_PATH) + file;

    std::string line;
    ifstream myfile (file.c_str());
    
    if (myfile.is_open())
    {
        _sock->SendRequest("HTTP/1.1 200 OK");
        while ( myfile.good() )
        {
            getline(myfile,line);
            _sock->send(line);
            _sock->send("\n");
        }
        myfile.close();
    }
    else
        _sock->SendRequest("HTTP/1.1 404 Not Found");
}

