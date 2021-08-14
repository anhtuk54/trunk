#include "app/Engine.h"
#include "utils/Logger.h"

#include <opencv2/highgui.hpp>
#include <functional>

using namespace std::chrono_literals;
using namespace voslam;
using namespace voslam::utils;

Logger::LogLevel Logger::LOGLEVEL_SETUP = Logger::LogLvMin;

VOSLAM_NS_BEGIN
APP_NS_BEGIN

Engine::Engine()
{
    Logger::init(Logger::LogLvInfo);
}

Engine::~Engine()
{
    mOdoEst.deinit();
}

void Engine::init(const std::string &cfg)
{
    mConfig.load(cfg);
    mOdoEst.init();
    mSLAMEst.init();
}

APP_NS_END
VOSLAM_NS_END