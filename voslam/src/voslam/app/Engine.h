#pragma once

#include "common/CommonDefs.h"
#include "odo/OdoEstimator.h"
#include "slam/SLAMEstimator.h"
#include "core/Configuration.h"

#include <string>

VOSLAM_NS_BEGIN
APP_NS_BEGIN

class Engine
{
public:
    Engine();
    ~Engine();

    /**
     * @brief This method is start point for starting application.
     * 
     * @param cfg 
     */
    void init(const std::string &cfg);

private:
    voslam::core::Configuration mConfig;
    voslam::odo::OdoEstimator mOdoEst;
    voslam::slam::SLAMEstimator mSLAMEst;
};

APP_NS_END
VOSLAM_NS_END
