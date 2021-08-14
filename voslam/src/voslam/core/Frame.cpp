#include "core/Frame.h"


VOSLAM_NS_BEGIN
CORE_NS_BEGIN

Frame::Frame()
{}
Frame::Frame(const Frame &other)
{
    mKeyPoints = other.mKeyPoints;
}

Frame::~Frame()
{}

std::vector<cv::KeyPoint> Frame::getKeyPoints()
{
    return mKeyPoints;
}
void Frame::setKeyPoints(const std::vector<cv::KeyPoint> &kpts)
{
    mKeyPoints = kpts;
}

CORE_NS_END
VOSLAM_NS_END