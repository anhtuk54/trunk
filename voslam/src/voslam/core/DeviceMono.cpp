#include "core/DeviceMono.h"
#include <opencv2/opencv.hpp>

VOSLAM_NS_BEGIN
CORE_NS_BEGIN

class DeviceMono::DeviceMonoImpl
{
public:
    DeviceMonoImpl()
    {
        mCapture.open(0);
    }

    ~DeviceMonoImpl()
    {}

    cv::Mat grabInput()
    {
        cv::Mat frame;
        mCapture >> frame;
        return frame;
    }

private:
    cv::VideoCapture mCapture;
};

DeviceMono::DeviceMono()
{}

DeviceMono::~DeviceMono()
{}

void DeviceMono::init() 
{
    mImpl = std::make_unique<DeviceMonoImpl>();
}

void DeviceMono::deinit()
{}

cv::Mat DeviceMono::grabInput()
{
    return mImpl->grabInput();
}

CORE_NS_END
VOSLAM_NS_END