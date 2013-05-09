#include "Config.h"
#include "Configuration.h"
#include "Log.h"

void Configuration::Load()
{
    _intconfigdata[LISTEN_PORT]   = ConfigMgr::GetIntDefault("ListenPort", 3000);
    _strconfigdata[WWW_DATA_PATH] = ConfigMgr::GetStringDefault("DataDir", "/var/www");
    _strconfigdata[CACHE_FILES] = ConfigMgr::GetStringDefault("Cache.Files", "");
    _boolconfigdata[USE_CACHE] = ConfigMgr::GetBoolDefault("Cache.Enabled", false);
    _intconfigdata[CACHE_TIME] = ConfigMgr::GetIntDefault("Cache.Time", 60);
}

