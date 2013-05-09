#ifndef __P_CONFIGURATION__
#define __P_CONFIGURATION__

#include <ace/Singleton.h>
#include <ace/Null_Mutex.h>

enum StringConfig
{
    WWW_DATA_PATH = 0,
    CACHE_FILES,
    MAX_STRING_CONFIG
};

enum BoolConfig
{
    USE_CACHE = 0,
    LOG_ENABLED,
    MAX_BOOL_CONFIG
};

enum IntConfig
{
    CACHE_TIME = 0,
    LISTEN_PORT,
    MAX_INT_CONFIG
};

class Configuration
{
    public:
        void Load();
        std::string GetStringConfig(StringConfig index) const
        {
            return index < MAX_STRING_CONFIG ? _strconfigdata[index]  : 0;
        }

        bool GetBoolConfig(BoolConfig index) const
        {
            return index < MAX_BOOL_CONFIG ? _boolconfigdata[index] : 0;
        }

        int GetIntConfig(IntConfig index) const
        {
            return index < MAX_INT_CONFIG ? _intconfigdata[index] : 0;
        }
    private:
        std::string _strconfigdata[MAX_STRING_CONFIG];
        bool   _boolconfigdata[MAX_BOOL_CONFIG];
        int    _intconfigdata[MAX_INT_CONFIG];
};
#define sConfiguration ACE_Singleton<Configuration, ACE_Null_Mutex>::instance()
#endif 
