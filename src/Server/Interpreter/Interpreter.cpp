#include "Interpreter.h"
#include "Configuration.h"
#include "ClientSocket.h"
#include "Define.h"

#include "Log.h"
#include <iostream>
#include <fstream>
#include <string>

inline bool strContains(const std::string inputStr, const std::string searchStr)
{
        size_t contains;

        contains = inputStr.find(searchStr);

        if(contains != string::npos)
                return true;
        else
                return false;
}

Interpreter::Interpreter::Interpreter(ClientSocket* sock): _sock(sock)
{

}

Interpreter::Interpreter::~Interpreter()
{

}

void Interpreter::CheckCommand(const std::string& args)
{
    if (strContains(args, "GET"))
    {
        std::string req = args;
        _file = req.substr(req.find(" ")+1);
        _file = _file.substr(0, _file.find(" "));
    }
}

void Interpreter::ProcessCommand()
{
    GetDatas(_file);
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
            (void) _sock->send(line);
            (void) _sock->send("\n");
        }
        myfile.close();
    }
    else
        _sock->SendRequest("HTTP/1.1 404 Not Found");
}

