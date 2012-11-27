#include "Log.h"
#include "ClientSocket.h"
#include "Define.h"

#include <ace/os_include/arpa/os_inet.h>
#include <ace/os_include/netinet/os_tcp.h>
#include <ace/os_include/sys/os_types.h>
#include <ace/os_include/sys/os_socket.h>

ClientSocket::ClientSocket()
{}

ClientSocket::~ClientSocket()
{}

int ClientSocket::open(void *)
{
    ACE_INET_Addr remote_addr;

    if (peer().get_remote_addr(remote_addr) == -1)
    {
        sLog->outError("ClientSocket::open: peer().get_remote_addr error is %s", ACE_OS::strerror(errno));
        return -1;
    }

    sLog->outDebug("Incoming connection from %s", remote_addr.get_host_addr());

    static const int ndoption = 1;
    peer().set_option (ACE_IPPROTO_TCP, TCP_NODELAY, (void*)&ndoption, sizeof (int));
    static const int m_SockOutKBuff = -1;
    peer().set_option (SOL_SOCKET, SO_SNDBUF, (void*) & m_SockOutKBuff, sizeof (int));
    return activate();
}

int ClientSocket::handle_close(ACE_HANDLE, ACE_Reactor_Mask)
{
    sLog->outDebug("Closing connection");
    peer().close_reader();
    wait();
    destroy();
    return 0;
}

int ClientSocket::send(const std::string& line)
{
    return size_t(peer().send(line.c_str(), line.length(), MSG_NOSIGNAL));// == line.length() ? 0 : -1;
}

int ClientSocket::recv_line(ACE_Message_Block& buffer)
{
    char byte;
    for (;;)
    {
        ssize_t n = peer().recv(&byte, sizeof(byte));

        if (n < 0)
        {
            return -1;
        }

        if (n == 0)
        {
            // EOF, connection was closed
            errno = ECONNRESET;
            return -1;
        }

        ACE_ASSERT(n == sizeof(byte));

        if (byte == '\n')
            break;
        else if (byte == '\r') /* Ignore CR */
            continue;
        else if (buffer.copy(&byte, sizeof(byte)) == -1)
            return -1;
    }

    const char null_term = '\0';
    if (buffer.copy(&null_term, sizeof(null_term)) == -1)
        return -1;

    return 0;
}

int ClientSocket::recv_line(std::string& out_line)
{
    char buf[4096];

    ACE_Data_Block db(sizeof (buf),
            ACE_Message_Block::MB_DATA,
            buf,
            0,
            0,
            ACE_Message_Block::DONT_DELETE,
            0);

    ACE_Message_Block message_block(&db,
            ACE_Message_Block::DONT_DELETE,
            0);

    if (recv_line(message_block) == -1)
    {
        sLog->outString("Recv error %s", ACE_OS::strerror(errno));
        return -1;
    }

    out_line = message_block.rd_ptr();

    return 0;
}

int ClientSocket::process_command(const std::string& command)
{
    if (command.compare("")==0)
    {
        _ip->ProcessCommand();
        return -1;
    }
    
    sLog->outDebug("Got command: %s", command.c_str());
    _ip->CheckCommand(command);
    return 0;
}

int ClientSocket::SendRequest(const std::string& line)
{
    (void) send(line);
    (void) send("\n");
    (void) send("Server: Pirol Version 0.1\n");
    (void) send("\n");
    
    return 0;
}

int ClientSocket::svc(void)
{
    _ip = new Interpreter(this);
    for(;;)
    {
        std::string line;

        if (recv_line(line) == -1)
            return -1;

        if (process_command(line) == -1)
            return -1;
    }

    return 0;
}