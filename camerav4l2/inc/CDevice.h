#pragma once

#include <string>
#include <memory>

#include "CommonDefs.h"

CAM_NS_BEGIN

class CDeviceConfig;
class CDevice
{
public:
    CDevice(const std::shared_ptr<CDeviceConfig> &cfg);
    ~CDevice();

    void start();
    void stop();

private:
    class CDeviceImpl;
    std::unique_ptr<CDeviceImpl> mImpl;
};

CAM_NS_END
