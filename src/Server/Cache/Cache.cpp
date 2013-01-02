#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>


#include "Cache.h"
#include "Misc.h"

void Cache::Initialize()
{
    uint32 pos = 0;
    std::string src;
    std::string delim = ",";
    src = sConfiguration->GetStringConfig(CACHE_FILES);
    
    bool datas = true;
    
    std::string::size_type start = 0;
    std::string::size_type end;

    for ( ; ; ) {
      end = src.find ( delim, start );
      _servedfiles.push_back ( "." + src.substr ( start, end - start ) );

      // We just copied the last token
      if ( end == std::string::npos )
        break;

      // Exclude the delimiter in the next search
      start = end + delim.size();
    }

    _servedfiles.swap ( _servedfiles );
}

CacheItem const* Cache::GetItem(std::string path)
{
    if (!_Check(path))
        return NULL;
    
    CacheItemContainer::const_iterator itr = _cachecontainer.find(path);
    if (itr != _cachecontainer.end())
    {
        if (itr->second.lifetime > time(0))
            return &(itr->second);
        else
        {
            TRINITY_WRITE_GUARD(ACE_RW_Thread_Mutex, rwMutex_);
            _cachecontainer.erase(itr);
        }
    }

    if (ReadFromFile(path))
    {
        CacheItemContainer::const_iterator itr = _cachecontainer.find(path);
        if (itr != _cachecontainer.end())
            return &(itr->second);
    }

    return NULL;
}

bool Cache::ReadFromFile(std::string path)
{
    std::string line;
    ifstream myfile (path.c_str());

    std::stringstream os;

    if (myfile.is_open())
    {
        while ( myfile.good() )
        {
            getline(myfile,line);
            os << line << "\n";
        }
        myfile.close();

        CacheItem *item = new CacheItem;
        item->lifetime = time(0) + sConfiguration->GetIntConfig(CACHE_TIME);
        item->content = os.str();
        _Insert(path, item);

        return true;
    }
    return false;
}

void Cache::_Insert(std::string path, CacheItem* item)
{
    //To prevent a crash we should set an Mutex here
    TRINITY_WRITE_GUARD(ACE_RW_Thread_Mutex, rwMutex_);

    CacheItem& m_item = _cachecontainer[path];
    m_item = *item;
    return;
}

bool Cache::_Check(std::string path)
{
    for (std::vector<std::string>::iterator itr = _servedfiles.begin(); itr != _servedfiles.end(); ++itr)
    {
        std::string container = *itr;
        if (strContains(path, container))
            return true;

        std::transform(container.begin(), container.end(),container.begin(), ::toupper);
        if (strContains(path, container))
            return true;
    }
    return false;
}