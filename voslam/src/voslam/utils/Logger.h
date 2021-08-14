#pragma once

#include <iostream>
#include <sstream>

#include "common/CommonDefs.h"

#if LOG_ENABLE

#define LogInfo()   voslam::utils::Logger(voslam::utils::Logger::LogLevel::LogLvInfo)<<"["<<__FILE__<<"]["<<__LINE__<<"]["<<__FUNCTION__<<"]: "
#define LogDebug()  voslam::utils::Logger(voslam::utils::Logger::LogLevel::LogLvDebug)<<"["<<__FILE__<<"]["<<__LINE__<<"]["<<__FUNCTION__<<"]: "
#define LogWarn()   voslam::utils::Logger(voslam::utils::Logger::LogLevel::LogLvWarn)<<"["<<__FILE__<<"]["<<__LINE__<<"]["<<__FUNCTION__<<"]: "
#define LogError()  voslam::utils::Logger(voslam::utils::Logger::LogLevel::LogLvError)<<"["<<__FILE__<<"]["<<__LINE__<<"]["<<__FUNCTION__<<"]: "

#else

#define LogInfo()   voslam::utils::Logger()
#define LogDebug()  voslam::utils::Logger()
#define LogWarn()   voslam::utils::Logger()
#define LogError()  voslam::utils::Logger()

#endif

VOSLAM_NS_BEGIN
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
VOSLAM_NS_END