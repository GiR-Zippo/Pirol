#ifndef _CLIENTSOCKET_H
#define _CLIENTSOCKET_H

#include "Define.h"
#include <ace/Synch_Traits.h>
#include <ace/Svc_Handler.h>
#include <ace/SOCK_Stream.h>
#include <ace/SOCK_Acceptor.h>

#include "Interpreter.h"

class Interpreter;
class ClientSocket: public ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_MT_SYNCH>
{
    friend class Interpreter;
    public:
        ClientSocket();
        virtual ~ClientSocket();

        virtual int svc(void);
        virtual int open(void * = 0);
        virtual int handle_close(ACE_HANDLE = ACE_INVALID_HANDLE, ACE_Reactor_Mask = ACE_Event_Handler::ALL_EVENTS_MASK);

    private:
        int recv_line(std::string& out_line);
        int recv_line(ACE_Message_Block& buffer);
        int process_command(const std::string& command);
        int SendRequest(const std::string& line);
        int send(const std::string& line);
    private:
        Interpreter* _ip;
};
#endif
