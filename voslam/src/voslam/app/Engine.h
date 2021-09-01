#pragma once

#include "common/CommonDefs.h"

#include <string>

VOSLAM_NS_BEGIN
APP_NS_BEGIN

class Engine
{
public:
    Engine();
    ~Engine();

    /**
     * @brief This method is start point for starting application.
     * 
     * @param cfg 
     */
    void init(const std::string &cfg);

private:
    class EngineImpl;
    std::unique_ptr<EngineImpl> mImpl=nullptr;
};

APP_NS_END
VOSLAM_NS_END
