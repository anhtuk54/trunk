#pragma once

#include "common/CommonDefs.h"
#include <opencv2/core.hpp>

VOSLAM_NS_BEGIN
CORE_NS_BEGIN

class Device
{
public:
    Device(){}
    virtual ~Device()=default;

    virtual void init()=0;
    virtual void deinit()=0;
    virtual cv::Mat grabInput() = 0;
};

CORE_NS_END
VOSLAM_NS_END