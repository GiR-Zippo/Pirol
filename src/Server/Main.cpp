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


extern int main(int argc, char **argv)
{   
    sLog->outString("Startup");
    ACE_Based::Thread socket_thread(new ClientSocketMgr);
    socket_thread.wait();
    
    return 0;
};
