#pragma once

#include "CommonDefs.h"

#include <string>
#include <memory>

CAM_NS_BEGIN

class CWindow
{
public:
    CWindow();
    ~CWindow();

    void init(const int &w, const int &h);
    void putFrame(void *f, int len);

private:
    class CWindowImpl;
    std::unique_ptr<CWindowImpl> mImpl; 
};

CAM_NS_END