# include "Log.h"

#include <stdarg.h>
#include <stdio.h>

void Log::outString(const char * str, ...)
{
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
    printf("\n");
}

void Log::outError( )
{
    printf("\n");
}

void Log::outError(const char * str, ...)
{
    if (!str)
        return;

  va_list args;
  va_start (args, str);
  vprintf (str, args);
  va_end (args);
  printf("\n");
}