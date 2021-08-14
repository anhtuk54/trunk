#include "odo/OdoEstimator.h"
#include "core/DeviceMono.h"


using namespace std::chrono_literals;

VOSLAM_NS_BEGIN
ODO_NS_BEGIN


OdoEstimator::OdoEstimator()
{
}

OdoEstimator::~OdoEstimator()
{
    if (nullptr != mThread) {
        if (mThread->joinable()) {
            mThread->join();
        }
    }
}

void OdoEstimator::init()
{
    // check device type
    mDevice.reset(new voslam::core::DeviceMono);
    mDevice->init();

    mViewer.reset(new voslam::gui::OdoVisualizer);

    mThread = std::make_unique<std::thread>([this]() {
        while(true) {
            auto input = mDevice->grabInput();
            mViewer->update(input);
            std::this_thread::sleep_for(10us);
        }
    });
}

void OdoEstimator::deinit()
{
    mDevice->deinit();
}

void OdoEstimator::update()
{
    
}

VOSLAM_NS_END
ODO_NS_END