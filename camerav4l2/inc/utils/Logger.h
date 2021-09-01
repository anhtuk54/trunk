#pragma once

#include <iostream>
#include <sstream>
#include <cstdbool>
#include <cstdint>

#include "CommonDefs.h"

#if LOG_ENABLE

#define LogInfo()   camera::utils::Logger(camera::utils::Logger::LogLevel::LogLvInfo)<<"["<<__FILE__<<"]["<<__LINE__<<"]["<<__FUNCTION__<<"]: "
#define LogDebug()  camera::utils::Logger(camera::utils::Logger::LogLevel::LogLvDebug)<<"["<<__FILE__<<"]["<<__LINE__<<"]["<<__FUNCTION__<<"]: "
#define LogWarn()   camera::utils::Logger(camera::utils::Logger::LogLevel::LogLvWarn)<<"["<<__FILE__<<"]["<<__LINE__<<"]["<<__FUNCTION__<<"]: "
#define LogError()  camera::utils::Logger(camera::utils::Logger::LogLevel::LogLvError)<<"["<<__FILE__<<"]["<<__LINE__<<"]["<<__FUNCTION__<<"]: "

#else

#define LogInfo()   camera::utils::Logger()
#define LogDebug()  camera::utils::Logger()
#define LogWarn()   camera::utils::Logger()
#define LogError()  camera::utils::Logger()

#endif
CAM_NS_BEGIN
UTILS_NS_BEGIN

class Logger
{
    
public:

    enum LogLevel : int {
        LogLvMin=0,
        LogLvError,
        LogLvWarn,
        LogLvDebug,
        LogLvInfo,
        LogLvVerbose,
        LogLvMax
    };


    Logger(LogLevel lv) : mLevel(lv)
    {
        mBuffer.clear();
    }
    
    ~Logger()
    {
        #if LOG_ENABLE
        
        if (mLevel <= LOGLEVEL_SETUP) {
            switch (mLevel) 
            {
            case LogLvError:
                std::cout << "[ERR]" << mBuffer.str() << std::endl;
                break;
            case LogLvWarn:
                std::cout << "[WRN]" << mBuffer.str() << std::endl;
                break;
            case LogLvDebug:
                std::cout << "[DBG]" << mBuffer.str() << std::endl;
                break;
            case LogLvInfo:
                std::cout << "[INF]" << mBuffer.str() << std::endl;
                break;
            default:
                break;
            }
        }
        #endif
    }

    template <class T>
    Logger& operator<<(const T& d) 
    {
        #if LOG_ENABLE
        mBuffer << d;
        #endif
        return *this;
    }

    static void init(LogLevel lv=LogLvError) 
    {
        LOGLEVEL_SETUP = lv;
    }

private:
    std::ostringstream mBuffer;
    LogLevel mLevel= LogLvMin;
    static LogLevel LOGLEVEL_SETUP;
};

UTILS_NS_END
CAM_NS_END