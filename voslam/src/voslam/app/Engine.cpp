#include "app/Engine.h"

#include "core/Configuration.h"
#include "odo/OdoEstimator.h"
#include "slam/SLAMEstimator.h"
#include "utils/Logger.h"

#include <opencv2/highgui.hpp>
#include <functional>

using namespace std;
using namespace std::chrono_literals;
using namespace voslam;
using namespace voslam::core;
using namespace voslam::odo;
using namespace voslam::slam;
using namespace voslam::utils;

Logger::LogLevel Logger::LOGLEVEL_SETUP = Logger::LogLvMin;

VOSLAM_NS_BEGIN
APP_NS_BEGIN

class Engine::EngineImpl
{
public:
    EngineImpl()
    {
        
    }

    ~EngineImpl()
    {
        mOdoEst->finalize();
    }

    void init(const std::string &cfg)
    {
        mConfig->load(cfg);


        mOdoEst->initialize();
        mSLAMEst->initialize();
    }

private:
    shared_ptr<Configuration>   mConfig;
    shared_ptr<Device>          mDevice;
    shared_ptr<OdoEstimator>    mOdoEst;
    shared_ptr<SLAMEstimator>   mSLAMEst;
};

Engine::Engine()
{
    Logger::init(Logger::LogLvInfo);
    mImpl = make_unique<EngineImpl>();
}

Engine::~Engine()
{    
}

void Engine::init(const std::string &cfg)
{
    mImpl->init(cfg);
}

APP_NS_END
VOSLAM_NS_END