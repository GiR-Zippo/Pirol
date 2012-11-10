#ifndef __LOG_H
#define __LOG_H

#include <stdio.h>
#include <ace/Singleton.h>

class Log
{
public:
    void outString(const char * str, ... );//                 ATTR_PRINTF(2, 3);
    void outString( );
    void outError( );
    void outError(const char * str, ... );//                 ATTR_PRINTF(2, 3);

};

#define sLog ACE_Singleton<Log, ACE_Thread_Mutex>::instance()
#endif
