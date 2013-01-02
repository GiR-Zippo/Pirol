#ifndef __P_MISC__
#define __P_MISC__

#include <string.h>

inline bool strContains(const std::string inputStr, const std::string searchStr)
{
        size_t contains;

        contains = inputStr.find(searchStr);

        if(contains != std::string::npos)
                return true;
        else
                return false;
}


#endif
