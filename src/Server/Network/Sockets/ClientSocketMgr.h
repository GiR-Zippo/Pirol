#ifndef _CLIENTSOCKETMGR_H_
#define _CLIENTSOCKETMGR_H_

#include <ace/Reactor.h>
#include "Threading.h"

class ClientSocketMgr : public ACE_Based::Runnable
{
public:
    ClientSocketMgr();
    virtual ~ClientSocketMgr();
    void run();

private:
    ACE_Reactor* m_Reactor;

};

#endif /* _CLIENTSOCKETMGR_H_ */

