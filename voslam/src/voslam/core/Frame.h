#pragma once

#include <opencv2/core.hpp>

#include "common/CommonDefs.h"

VOSLAM_NS_BEGIN
CORE_NS_BEGIN

class Frame
{
public:
    Frame();
    Frame(const Frame &other);
    ~Frame();

    std::vector<cv::KeyPoint> getKeyPoints();
    void setKeyPoints(const std::vector<cv::KeyPoint> &kpts);

private:
    std::vector<cv::KeyPoint> mKeyPoints;
    cv::Mat mRot;
    cv::Mat mTr;
};

CORE_NS_END
VOSLAM_NS_END