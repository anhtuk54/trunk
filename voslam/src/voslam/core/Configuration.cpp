#include "core/Configuration.h"
#include "utils/Logger.h"

#include <opencv2/core.hpp>

VOSLAM_NS_BEGIN
CORE_NS_BEGIN

ConfigurationInfo::ConfigurationInfo()
{
}

ConfigurationInfo::~ConfigurationInfo()
{
}

Configuration::Configuration()
{
}

Configuration::~Configuration()
{
}

void Configuration::load(const std::string &cfg)
{
    cv::FileStorage fs;
    fs.open(cfg,cv::FileStorage::READ);
    if (fs.isOpened()) {
        // Read the configuration file
    }
    else {
        LogWarn() << "Unable to open " << cfg;
        LogWarn() << "Fallback to default case";
    }
}

CORE_NS_END
VOSLAM_NS_END