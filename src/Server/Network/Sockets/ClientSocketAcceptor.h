#ifndef __CLIENTSOCKETACCEPTOR_H_
#define __CLIENTSOCKETACCEPTOR_H_

#include "Define.h"

#include <ace/Acceptor.h>
#include <ace/SOCK_Acceptor.h>

#include "Log.h"
#include "ClientSocket.h"

class ClientSocketAcceptor : public ACE_Acceptor<ClientSocket, ACE_SOCK_Acceptor>
{
public:
    ClientSocketAcceptor(void) { }
    virtual ~ClientSocketAcceptor(void)
    {
        if (reactor())
            reactor()->cancel_timer(this, 1);
    }

protected:

    virtual int handle_timeout(const ACE_Time_Value& /*current_time*/, const void* /*act = 0*/)
    {
        sLog->outString("Resuming acceptor");
        reactor()->cancel_timer(this, 1);
        return reactor()->register_handler(this, ACE_Event_Handler::ACCEPT_MASK);
    }

    virtual int handle_accept_error(void)
    {
#if defined(ENFILE) && defined(EMFILE)
        if (errno == ENFILE || errno == EMFILE)
        {
            sLog->outError("Client: Out of file descriptors, suspending incoming connections for 10 seconds");
            reactor()->remove_handler(this, ACE_Event_Handler::ACCEPT_MASK | ACE_Event_Handler::DONT_CALL);
            reactor()->schedule_timer(this, NULL, ACE_Time_Value(10));
        }
#endif
        return 0;
    }
};

#endif /* __CLIENTSOCKETACCEPTOR_H_ */
/// @}
