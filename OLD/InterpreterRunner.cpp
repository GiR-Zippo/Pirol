#include <string>
#include <iostream>
#include <ace/ACE.h>
#include <ace/Log_Msg.h>
#include <ace/Reactor.h>
#include <ace/Reactor_Impl.h>
#include <ace/TP_Reactor.h>
#include <ace/Dev_Poll_Reactor.h>
#include <ace/Guard_T.h>
#include <ace/Atomic_Op.h>
#include <ace/os_include/arpa/os_inet.h>
#include <ace/os_include/netinet/os_tcp.h>
#include <ace/os_include/sys/os_types.h>

#include "Log.h"
#include "InterpreterRunner.h"

InterpreterRunner::InterpreterRunner(): ACE_Task_Base(),
    _Reactor(0),
    _Counter(0),
    _ThreadId(-1)
{
    ACE_Reactor_Impl* imp = 0;

    #if defined (ACE_HAS_EVENT_POLL) || defined (ACE_HAS_DEV_POLL)

    imp = new ACE_Dev_Poll_Reactor();

    imp->max_notify_iterations (128);
    imp->restart (1);

    #else

    imp = new ACE_TP_Reactor();
    imp->max_notify_iterations (128);

    #endif

    _Reactor = new ACE_Reactor (imp, 1);
    _interpreter = new Interpreter(this);
}

InterpreterRunner::~InterpreterRunner( )
{
    Stop();
    Wait();

    delete _Reactor;
}

int InterpreterRunner::Start()
{
    if (_ThreadId != -1)
        return -1;
    return (_ThreadId = activate());
}

void InterpreterRunner::Stop()
{
    _Reactor->end_reactor_event_loop();
}

int InterpreterRunner::svc()
{
    sLog->outString("Running...");
    std::string name;
    while (!_Reactor->reactor_event_loop_done())
    {
        ACE_Time_Value interval (0, 100*1000);
         if (_Reactor->run_reactor_event_loop (interval) == -1)
            break;
         
        getline(std::cin, name);
        _interpreter->Input(name.c_str());
    }
    sLog->outString("Stop");
    return -1;
}


