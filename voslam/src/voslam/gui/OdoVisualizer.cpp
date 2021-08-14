#include "gui/OdoVisualizer.h"
#include <opencv2/opencv.hpp>

VOSLAM_NS_BEGIN
GUI_NS_BEGIN

OdoVisualizer::OdoVisualizer()
{
}

OdoVisualizer::~OdoVisualizer()
{}

void OdoVisualizer::update()
{
    // cv::imshow("Odometry viewer",tmp);
}

void OdoVisualizer::update(const cv::Mat &img)
{
}


GUI_NS_END
VOSLAM_NS_END