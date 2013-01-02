#ifndef __P_CACHE__
#define __P_CACHE__

#include <ace/Singleton.h>
#include <vector>
#include <algorithm>

#include "Define.h"
#include "UnorderedMap.h"
#include "Configuration.h"

struct CacheItem
{
    uint32 lifetime;
    std::string content;
};

typedef UNORDERED_MAP<std::string, CacheItem> CacheItemContainer;

class Cache
{
    public:
        void Initialize();
        CacheItem const* GetItem(std::string path);

        ///- File Input
        bool ReadFromFile(std::string path);
        
    private:
        void _Insert(std::string path, CacheItem *item);
        bool _Check(std::string path);
        
        std::vector<std::string> _servedfiles;
        ACE_RW_Thread_Mutex rwMutex_;
        CacheItemContainer _cachecontainer;
        
};
#define sCache ACE_Singleton<Cache, ACE_Null_Mutex>::instance()
#endif

