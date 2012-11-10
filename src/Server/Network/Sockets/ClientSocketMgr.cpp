#include "Log.h"
#include "ClientSocketMgr.h"

#include <ace/Reactor_Impl.h>
#include <ace/TP_Reactor.h>
#include <ace/Dev_Poll_Reactor.h>
#include <ace/Acceptor.h>
#include <ace/SOCK_Acceptor.h>

#include "ClientSocket.h"

ClientSocketMgr::ClientSocketMgr() : m_Reactor(NULL)
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

    m_Reactor = new ACE_Reactor (imp, 1);
}

ClientSocketMgr::~ClientSocketMgr()
{
    delete m_Reactor;
}

void ClientSocketMgr::run()
{
    ACE_Acceptor<ClientSocket, ACE_SOCK_ACCEPTOR> acceptor;

    uint16 raport = 3000;
    std::string stringip = "0.0.0.0";

    ACE_INET_Addr listen_addr(raport, stringip.c_str());

    if (acceptor.open(listen_addr, m_Reactor) == -1)
    {
        sLog->outError("Strawberry RA can not bind to port %d on %s", raport, stringip.c_str());
        return;
    }

    sLog->outString("Starting Strawberry RA on port %d on %s", raport, stringip.c_str());

    while (true)
    {
        // don't be too smart to move this outside the loop
        // the run_reactor_event_loop will modify interval
        ACE_Time_Value interval(0, 100000);

        if (m_Reactor->run_reactor_event_loop(interval) == -1)
            break;
    }

    sLog->outString("Strawberry RA thread exiting");
}
