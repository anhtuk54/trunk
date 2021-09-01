#pragma once

#include "common/CommonDefs.h"
#include <memory>

VOSLAM_NS_BEGIN
APP_NS_BEGIN

class Engine;

class App
{
public:
    enum E_MODE
    {
        E_MODE_GUI=0,
        E_MODE_REMOTE,
        E_MODE_MAX
    };

    /**
     * @brief Construct a new App object
     * 
     */
    App() = delete;

    /**
     * @brief Construct a new App object
     * 
     * @param engine 
     * @param mode 
     */
    App(std::shared_ptr<Engine> engine=nullptr, App::E_MODE mode=App::E_MODE_GUI);

    /**
     * @brief Destroy the App object
     * 
     */
    ~App();

    /**
     * @brief 
     * 
     * @return int 
     */
    int exec();

private:
    class AppImpl;
    std::unique_ptr<AppImpl> mImpl=nullptr;
};

APP_NS_END
VOSLAM_NS_END