#ifndef __INT_RUNNER
#define __INT_RUNNER

#include <ace/Version.h>
#include <ace/Synch_Traits.h>
#include <ace/Svc_Handler.h>
#include <ace/Object_Manager.h>
#include <ace/Sig_Handler.h>

#include "Interpreter.h"

class Interpreter;
class InterpreterRunner : protected ACE_Task_Base
{
public:
    InterpreterRunner();
    virtual ~InterpreterRunner(void );
    int Start();
    void Stop();
    void Wait() { ACE_Task_Base::wait(); }
    
protected:
    virtual int svc();
   
private:
        typedef ACE_Atomic_Op<ACE_SYNCH_MUTEX, long> AtomicInt;

        ACE_Reactor* _Reactor;
        AtomicInt _Counter;
        int _ThreadId;
        Interpreter* _interpreter;
};
 
#endif