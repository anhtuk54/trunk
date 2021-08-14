#pragma once

#include <string>

#include "common/CommonDefs.h"

VOSLAM_NS_BEGIN
CORE_NS_BEGIN

class ConfigurationInfo
{
public:
    ConfigurationInfo();
    ~ConfigurationInfo();

    void getConfig();
    void setConfig();
};

class Configuration
{
public:
    Configuration();
    ~Configuration();

    void load(const std::string &cfg);

private:
    ConfigurationInfo mConfigInfo;
};

CORE_NS_END
VOSLAM_NS_END
