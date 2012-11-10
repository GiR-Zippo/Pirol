#include "Interpreter.h"



#include "Log.h"
#include <string>
#include <iostream>


inline bool strContains(const std::string inputStr, const std::string searchStr)
{
        size_t contains;
        contains = inputStr.find(searchStr);
        if(contains != std::string::npos)
                return true;
        return false;
}

Interpreter::Interpreter(InterpreterRunner* run): _runner(run)
{

}

Interpreter::~Interpreter()
{

}

void Interpreter::Input(const char* args)
{
    sLog->outString("->%s", args);
    if (strContains(args,"quit"))
    {
        sLog->outString("Bye.");
        _runner->Stop();
    }
    
}














