#pragma once

#include <iostream>
#include <sstream>

#ifndef LOG_TAG
#error "Please define LOG_TAG"
#endif

#define LogInf()   Logger()<<"["<<LOG_TAG<<"][INF]["<<__PRETTY_FUNCTION__<<"]["<<__LINE__<<"]: "
#define LogWrn()   Logger()<<"["<<LOG_TAG<<"][WRN]["<<__PRETTY_FUNCTION__<<"]["<<__LINE__<<"]: "
#define LogErr()   Logger()<<"["<<LOG_TAG<<"][ERR]["<<__PRETTY_FUNCTION__<<"]["<<__LINE__<<"]: "
#define LogDBG()   Logger()<<"["<<LOG_TAG<<"][DBG]["<<__PRETTY_FUNCTION__<<"]["<<__LINE__<<"]: "

class Logger
{
    std::stringstream mBuffer;
public:
    Logger()
    {
        mBuffer.clear();
    }
    ~Logger()
    {
        std::cout << mBuffer.str() << "\n";
    }

    template<class T>
    Logger& operator<<(const T& v)
    {
        mBuffer << v;
        return *this;
    }
};