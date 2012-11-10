#include <ace/Version.h>
#include <ace/Synch_Traits.h>
#include <ace/Svc_Handler.h>
#include <ace/SOCK_Stream.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/Object_Manager.h>
#include <ace/Sig_Handler.h>

#include "ClientSocketMgr.h"
#include "ClientSocket.h"


#include "Log.h"
#include "Config.h"
#include "Configuration.h"

#ifndef _WEB_SERVER_CONFIG
# define _WEB_SERVER_CONFIG "webserver.conf"
#endif //_WEB_SERVER_CONFIG

extern int main(int argc, char **argv)
{
    sLog->outString("Startup");
    sLog->outString("Using config dir: %s", _WEB_SERVER_CONFIG);
    if (!ConfigMgr::Load(_WEB_SERVER_CONFIG))
        return 0;
    sConfiguration->Load();
    
    ACE_Based::Thread socket_thread(new ClientSocketMgr);
    socket_thread.wait();
    
    return 0;
};
