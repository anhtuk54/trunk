#pragma once

#include "CommonDefs.h"

#include <string>
#include <memory>

CAM_NS_BEGIN
class CDeviceConfig;
class CConfiguration
{
public:

    CConfiguration(const std::string &cfg="default.json");
    ~CConfiguration();

    std::shared_ptr<CDeviceConfig> getDeviceConfig();
    
private:
    class CConfigurationImpl;
    std::unique_ptr<CConfigurationImpl> mImpl;
};

CAM_NS_END