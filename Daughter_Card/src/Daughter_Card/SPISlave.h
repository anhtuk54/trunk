#pragma once

#include <variant.h>
#include <stdio.h>

typedef void(*InitCallbackType)(void);
typedef void(*InterruptCallbackType)(void);

class SPISlaveClass
{
public:
    SPISlaveClass(Spi *spi, uint32_t id, InitCallbackType cb);
    ~SPISlaveClass();

    void begin(InterruptCallbackType cb);
    void callIntrHandler();

private:
    void init();

private:
    Spi *mSPI=nullptr;
    uint32_t mId=0;
    bool mInitialized = false;
    InitCallbackType mInitCb = nullptr;
    InterruptCallbackType mIntrCb = nullptr;
};

#if SPI_INTERFACES_COUNT > 0
extern SPISlaveClass SPISlave;
#endif