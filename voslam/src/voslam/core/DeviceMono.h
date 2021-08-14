#pragma once

#include "core/Device.h"
#include <memory>

VOSLAM_NS_BEGIN
CORE_NS_BEGIN

class DeviceMono : public Device
{
private:
    
public:
    DeviceMono();
    ~DeviceMono();

    virtual void init() override;
    virtual void deinit() override;
    virtual cv::Mat grabInput() override;

private:
    class DeviceMonoImpl;
    std::unique_ptr<DeviceMonoImpl> mImpl;

};

CORE_NS_END
VOSLAM_NS_END