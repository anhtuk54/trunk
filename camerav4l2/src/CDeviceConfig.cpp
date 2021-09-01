
#include "CDeviceConfig.h"

CAM_NS_BEGIN

class CDeviceConfig::CDeviceConfigImpl
{
public:
    CDeviceConfigImpl()
    {
    }

    ~CDeviceConfigImpl()
    {
    }

    std::string deviceName() const
    {
        return mDeviceName;
    }

    void setDeviceName(const std::string &devname)
    {
        if (mDeviceName != devname) {
            mDeviceName = devname;
        }
    }

    int width() const
    {
        return mWidth;
    }
    void setWidth(const int &w)
    {
        if (mWidth != w) {
            mWidth = w;
        }
    }

    int height() const
    {
        return mHeight;
    }
    void setHeight(const int &h)
    {
        if (mHeight != h) {
            mHeight = h;
        }
    }

private:
    std::string mDeviceName;
    int mWidth=-1;
    int mHeight=-1;
};

CDeviceConfig::CDeviceConfig()
{
    mImpl = std::make_unique<CDeviceConfigImpl>();
}

CDeviceConfig::~CDeviceConfig()
{
}

std::string CDeviceConfig::deviceName() const
{
    return mImpl->deviceName();
}

void CDeviceConfig::setDeviceName(const std::string &devname)
{
    mImpl->setDeviceName(devname);
}

int CDeviceConfig::width() const
{
    return mImpl->width();
}
void CDeviceConfig::setWidth(const int &w)
{
    mImpl->setWidth(w);
}

int CDeviceConfig::height() const
{
    return mImpl->height();
}
void CDeviceConfig::setHeight(const int &h)
{
    mImpl->setHeight(h);
}

CAM_NS_END