#pragma once

#include "common/CommonDefs.h"

#include <string>

VOSLAM_NS_BEGIN
CORE_NS_BEGIN

class ConfigurationInfo
{
public:
    ConfigurationInfo();
    ~ConfigurationInfo();

    template<typename T>
    T getConfig(const std::string &key)
    {
        return T();
    }

    template<typename T>
    void setConfig(const std::string &key, const T &value)
    {
    }

private:
    
};

class Configuration
{
public:
    Configuration();
    ~Configuration();

    void load(const std::string &cfg);
    ConfigurationInfo getDeviceConfig();
    ConfigurationInfo getOdoConfig();
    ConfigurationInfo getSLAMConfig();

private:
    ConfigurationInfo mConfigInfo;
};

CORE_NS_END
VOSLAM_NS_END
