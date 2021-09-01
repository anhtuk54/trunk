#include "CDevice.h"
#include "CDeviceConfig.h"
#include "CConfiguration.h"
#include "utils/Logger.h"
#include "utils/json.hpp"

#include <fstream>
#include <string>

using namespace std;
using namespace nlohmann;
using namespace camera;
using namespace camera::utils;

// Global definition of logger
Logger::LogLevel Logger::LOGLEVEL_SETUP = Logger::LogLvVerbose;

int main(int ac, char **av)
{
    // Log init
    Logger::init(Logger::LogLvInfo);

    // Read config file
    CConfiguration config("config.json");

    // Device creation
    CDevice cam(config.getDeviceConfig());
    cam.start();

    return EXIT_SUCCESS;
}