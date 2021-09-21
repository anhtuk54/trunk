#ifndef XENO4COMMANDINTERFACE_H
#define XENO4COMMANDINTERFACE_H

#include "CommandInterface.h"

#include <memory>
#include <thread>
#include <evl/xbuf.h>

class Xeno4Device;

class Xeno4CommandInterface : public CommandInterface
{
public:
    Xeno4CommandInterface();

    // CommandInterface interface
public:
    virtual int start() override;
    virtual int stop() override;
    virtual int changeSpeed(const int &speed) override;

private:
    std::unique_ptr<Xeno4Device> _device;
};

#endif // XENO4COMMANDINTERFACE_H
