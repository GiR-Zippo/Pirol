# include "Log.h"

#include <stdarg.h>
#include <stdio.h>

Log::Log()
{
    enabled = true;
}

void Log::outString(const char * str, ...)
{
    if (!enabled)
        return;
    
    if (!str)
        return;

  va_list args;
  va_start (args, str);
  vprintf (str, args);
  va_end (args);
  printf("\n");
}

void Log::outString()
{
    if (!enabled)
        return;
    
    printf("\n");
}

void Log::outError( )
{
    if (!enabled)
        return;
    
    printf("\n");
}

void Log::outError(const char * str, ...)
{
    if (!enabled)
        return;
    
    if (!str)
        return;

  va_list args;
  va_start (args, str);
  vprintf (str, args);
  va_end (args);
  printf("\n");
}