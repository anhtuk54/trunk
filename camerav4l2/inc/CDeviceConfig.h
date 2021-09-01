#pragma once

#include "CommonDefs.h"

#include <string>
#include <memory>

CAM_NS_BEGIN

class CDeviceConfig
{
public:
    CDeviceConfig();
    ~CDeviceConfig();

    std::string deviceName() const;
    void setDeviceName(const std::string &devname);

    int width() const;
    void setWidth(const int &w);

    int height() const;
    void setHeight(const int &h);

private:
    class CDeviceConfigImpl;
    std::unique_ptr<CDeviceConfigImpl> mImpl;
};

CAM_NS_END