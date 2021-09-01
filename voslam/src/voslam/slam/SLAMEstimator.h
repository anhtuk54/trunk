#pragma once

#include "common/CommonDefs.h"

VOSLAM_NS_BEGIN
SLAM_NS_BEGIN
    
class SLAMEstimator
{
public:
    SLAMEstimator();
    ~SLAMEstimator();

    void initialize();
    void finalize();

private:
};

SLAM_NS_END
VOSLAM_NS_END
