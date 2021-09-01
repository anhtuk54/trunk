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

    void initialize();
    void finalize();
private:
};

ODO_NS_END
VOSLAM_NS_END
