#pragma once

#include "common/CommonDefs.h"
#include <opencv2/core.hpp>

VOSLAM_NS_BEGIN
GUI_NS_BEGIN

class OdoVisualizer
{
public:
    OdoVisualizer();
    ~OdoVisualizer();

    void update();
    void update(const cv::Mat &img);
};

GUI_NS_END
VOSLAM_NS_END