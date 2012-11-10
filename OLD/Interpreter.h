#ifndef __INTERPRETER_
#define __INTERPRETER_

#include "InterpreterRunner.h"

class InterpreterRunner;
class Interpreter
{
public:
    Interpreter(InterpreterRunner* run);
    ~Interpreter();
    void Input(const char* args);
private:
    InterpreterRunner* _runner;
    
};

#endif