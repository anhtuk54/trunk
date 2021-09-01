#include "app/App.h"

VOSLAM_NS_BEGIN
APP_NS_BEGIN

class App::AppImpl
{
public:
    AppImpl()
    {
    }

    AppImpl(std::shared_ptr<Engine> engine=nullptr, App::E_MODE mode=App::E_MODE_GUI)
        :mEngine(engine), mMode(mode)
    {
    }

    ~AppImpl()
    {
    }

    int exec()
    {
    }

private:
    App::E_MODE mMode;
    std::shared_ptr<Engine> mEngine;
};

App::App(std::shared_ptr<Engine> engine, App::E_MODE mode)
{
    mImpl = std::make_unique<AppImpl>(engine,mode);
}

App::~App()
{
}

int App::exec()
{
    mImpl->exec();
}

APP_NS_END
VOSLAM_NS_END
