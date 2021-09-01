#include "CConfiguration.h"
#include "CDeviceConfig.h"
#include "utils/json.hpp"
#include "utils/Logger.h"

#include <fstream>

using namespace std;
using namespace nlohmann;

CAM_NS_BEGIN

class CConfiguration::CConfigurationImpl
{
public:
    CConfigurationImpl(const std::string &cfg)
        :mConfigFile(cfg)
    {
        ifstream ifs(mConfigFile);
        json jConfig = json::parse(ifs); 

        mDevConfigRef = std::make_shared<CDeviceConfig>();
        mDevConfigRef->setDeviceName(jConfig["dev"].get<std::string>());
        mDevConfigRef->setWidth(jConfig["width"].get<int>());
        mDevConfigRef->setHeight(jConfig["height"].get<int>());
    }

    ~CConfigurationImpl()
    {
    }

    std::shared_ptr<CDeviceConfig> getDeviceConfig()
    {
        return mDevConfigRef;
    }

private:
    std::string mConfigFile;
    std::shared_ptr<CDeviceConfig> mDevConfigRef;
};

CConfiguration::CConfiguration(const std::string &cfg)
{
    mImpl = std::make_unique<CConfigurationImpl>(cfg);
}

CConfiguration::~CConfiguration()
{
}

std::shared_ptr<CDeviceConfig> CConfiguration::getDeviceConfig()
{
    return mImpl->getDeviceConfig();
}

CAM_NS_END