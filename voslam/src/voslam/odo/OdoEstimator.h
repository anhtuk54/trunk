#pragma once

#include "common/CommonDefs.h"
#include "core/Frame.h"
#include "core/Device.h"
#include "gui/OdoVisualizer.h"

#include <memory>
#include <thread>

VOSLAM_NS_BEGIN
ODO_NS_BEGIN
class OdoEstimator
{
public:
    OdoEstimator();
    ~OdoEstimator();

    void init();
    void deinit();
    void update();
    
private:
    std::unique_ptr<voslam::core::Device> mDevice;
    std::unique_ptr<voslam::gui::OdoVisualizer> mViewer;
    std::unique_ptr<std::thread> mThread;
    voslam::core::Frame mFrame;
};

ODO_NS_END
VOSLAM_NS_END
