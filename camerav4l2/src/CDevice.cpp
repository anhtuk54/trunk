
#include "CDevice.h"
#include "CDeviceConfig.h"
#include "CWindow.h"
#include "utils/Logger.h"

// C++ headers
#include <thread>
#include <mutex>
#include <functional>

// C headers for linux
#include <string.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/v4l2-subdev.h>

using Guard = std::lock_guard<std::mutex>;

CAM_NS_BEGIN

class CDevice::CDeviceImpl
{
public:
    CDeviceImpl()
    {
    }

    CDeviceImpl(const std::shared_ptr<CDeviceConfig> &cfg)
        : mConfig{cfg}
    {
        init();
        initWindow();
    }

    ~CDeviceImpl()
    {
        denit();
    }

    void start()
    {
        mThread = std::make_unique<std::thread>(std::bind(&CDeviceImpl::doLoop,this));
    }

    void stop()
    {
        Guard g(mMutex);
        mDone = true;
    }

private:
    void init()
    {
        auto dev = mConfig->deviceName();
        mFd = open(dev.c_str(),O_RDWR);
        if (mFd<0) {
            LogError()  << "Failed to open device " << dev
                        << " with error: " << std::string(strerror(errno));
        }
        else {
            LogDebug() << "Succeeded to open device " << dev;
        }

        // Query capabilities
        if (ioctl(mFd,VIDIOC_QUERYCAP, &mCap)<0) {
            LogError() << "Cannot obtain video capabilities";
            exit(EXIT_FAILURE);
        }
        else {
            bool supp_capture = static_cast<bool>(mCap.capabilities & V4L2_CAP_VIDEO_CAPTURE);
            bool supp_stream = static_cast<bool>(mCap.capabilities & V4L2_CAP_STREAMING);
            LogDebug() << "V4L2_CAP_VIDEO_CAPTURE: " << std::boolalpha << supp_capture;
            LogDebug() << "V4L2_CAP_STREAMING: " << std::boolalpha << supp_stream;

            if (!(supp_capture && supp_stream)) {
                LogError() << "Device does not support capture and stream";
                exit(EXIT_FAILURE);
            }
        }

        // Setup video format
        mFormat.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        mFormat.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
        mFormat.fmt.pix.width = mConfig->width();
        mFormat.fmt.pix.width = mConfig->height();

        if (ioctl(mFd,VIDIOC_S_FMT,&mFormat) <0) {
            LogError() << "Cannot setup format of device";
            exit(EXIT_FAILURE);
        }
        else {
            LogDebug() "Succeeded to set up device";
        }

        // Init buffer
    
        mBufferReq.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        mBufferReq.memory = V4L2_MEMORY_MMAP;
        mBufferReq.count = 1; // TODO: Consider to add into config.json
        if (ioctl(mFd,VIDIOC_REQBUFS,&mBufferReq) <0) {
            LogError() << "Cannot request buffer";
            exit(EXIT_FAILURE);
        }
        mBufferInfo.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        mBufferInfo.memory = V4L2_MEMORY_MMAP;
        mBufferInfo.index = 0;
        if(ioctl(mFd,VIDIOC_QUERYBUF,&mBufferInfo)<0) {
            LogError() << "Cannot query buffer info";
            exit(EXIT_FAILURE);
        }

        // Obtain buffer via mmap
        mBufferStart = mmap(
            NULL,
            mBufferInfo.length,
            PROT_READ | PROT_WRITE,
            MAP_SHARED,
            mFd,
            mBufferInfo.m.offset
        );
        if (MAP_FAILED == mBufferStart) {
            LogError() << "Cannot obtain memory map of buffer";
            exit(EXIT_FAILURE);
        }
        else {
            // zero init
            memset(mBufferStart,0,mBufferInfo.length);
        }
    }

    void initWindow()
    {
        mWindow.init(mConfig->width(), mConfig->height());
    }

    void denit()
    {
        if (nullptr != mThread) {
            mThread->join();
        }

        if (mFd<0) {
            munmap(mBufferStart,mBufferInfo.length);
            close(mFd);
        }
    }

    void doLoop()
    {
        // Set thread name
        auto np = mThread->native_handle();
        pthread_setname_np(np,"CAM_RX");

        // Activate stream
        int type = mBufferInfo.type;
        if (ioctl(mFd,VIDIOC_STREAMON,&type)<0) {
            LogError() << "Cannot start stream";
            exit(EXIT_FAILURE);
        }

        bool isDone;
        while (true) {
            // Check stop condition
            {
                Guard g(mMutex); 
                isDone = mDone;
            }
            if (isDone) break;

            // Grab frame
            /* ioctl: VIDIOC_QBUF */
            if (ioctl(mFd,VIDIOC_QBUF,&mBufferInfo)<0) {
                LogError() << "Cannot put buffer to incoming queue";
                exit(EXIT_FAILURE);
            }

            /* ioctl: VIDIOC_DQBUF */
            if (ioctl(mFd,VIDIOC_DQBUF,&mBufferInfo)<0) {
                LogError() << "Cannot put buffer to incoming queue";
                exit(EXIT_FAILURE);
            }
            using namespace std::chrono_literals;
            mWindow.putFrame(mBufferStart,mBufferInfo.length);
            std::this_thread::sleep_for(10us);
            
        }

        if (ioctl(mFd,VIDIOC_STREAMOFF,&type)<0) {
            LogError() << "Cannot stop stream";
            exit(EXIT_FAILURE);
        }
    }

private:
    // Portable code
    std::string mDeviceName;
    std::shared_ptr<CDeviceConfig> mConfig=nullptr;
    std::unique_ptr<std::thread> mThread=nullptr;
    std::mutex mMutex;
    bool mDone = false;
    CWindow mWindow;

    // Linux code
    int mFd=-1;
    struct v4l2_capability mCap;
    struct v4l2_format mFormat;
    struct v4l2_requestbuffers mBufferReq;
    struct v4l2_buffer mBufferInfo;
    void *mBufferStart=NULL;
};

CDevice::CDevice(const std::shared_ptr<CDeviceConfig> &cfg)
{
    mImpl = std::make_unique<CDeviceImpl>(cfg);
}

CDevice::~CDevice()
{
}

void CDevice::start()
{
    if (nullptr != mImpl) {
        mImpl->start();
    }
}

void CDevice::stop()
{
    if (nullptr != mImpl) {
        mImpl->stop();
    }
}

CAM_NS_END