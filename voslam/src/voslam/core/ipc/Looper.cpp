#include "core/ipc/Looper.h"

VOSLAM_NS_BEGIN
CORE_NS_BEGIN
IPC_NS_BEGIN
///////////////////////////////////////////////////////////////////////////////////////
Handler::Handler(HandlerCb cb, const std::string &loopId)
    :mCb{cb}, mLooperId{loopId}
{
}

Handler::~Handler()
{
}

void Handler::post(const Message &msg)
{
    Looper::get(mLooperId)->post(msg);
}

void Handler::process(const Message &msg)
{
    if (nullptr != mCb) {
        mCb(msg);
    }
}

HandlerBuilder::HandlerBuilder()
{
}

HandlerBuilder& HandlerBuilder::addCallback(HandlerCb cb)
{
    mCb = cb;
    return *this;
}

HandlerBuilder& HandlerBuilder::addLooperId(const std::string &id)
{
    mLooperId = id;
    return *this;
}

std::shared_ptr<Handler> HandlerBuilder::build()
{
    auto hdl = std::make_shared<Handler>(mCb,mLooperId);
    Looper::get(mLooperId)->attachHandler(hdl);

    return hdl;
}

///////////////////////////////////////////////////////////////////////////////////////

std::map<std::string, std::shared_ptr<Looper>> Looper::LooperPool={};

std::shared_ptr<Looper> Looper::create(const std::string &id)
{
    auto e = std::find_if(LooperPool.cbegin(), LooperPool.cend(), [&](const auto &e) {
        return id == e.first;
    });

    if (LooperPool.cend() == e) {
        LogDebug() << "Create new looper with id: " << id;
        std::shared_ptr<Looper> lp = std::make_shared<Looper>(id);
        LooperPool.insert({id, lp});
        return lp;
    }
    else {
        LogWarn() << "Looper with id " << id << " has already existed, ignore request";
        return e->second;
    }
    
}

std::shared_ptr<Looper> Looper::get(const std::string &id)
{
    return LooperPool.at(id);
}


Looper::Looper(const std::string &id): mId{id}
{
}

Looper::~Looper()
{
    if (nullptr != mThread && mThread->joinable()) {
        mThread->join();
    }
}

void Looper::run()
{
    mThread = std::make_unique<std::thread>(std::bind(&Looper::process, this));
}

void Looper::quit()
{
    std::lock_guard<std::mutex> g(mMutexMsgQueue);
    mIsDone = true;
    mCondVar.notify_one();
}

void Looper::post(const Message &msg)
{
    std::lock_guard<std::mutex> g(mMutexMsgQueue);
    mMessageQueue.push(msg);
    mCondVar.notify_one();
}

void Looper::attachHandler(std::shared_ptr<Handler> hdl)
{
    std::lock_guard<std::mutex> g(mMutexHdl);
    mHandlers.push_back(hdl);
}

void Looper::process()
{
    auto np = mThread->native_handle();
    pthread_setname_np(np,mId.c_str());

    while (true) {
        using namespace std::chrono_literals;
        bool res = false;
        {
            std::unique_lock<std::mutex> lk(mMutexMsgQueue);
            res = mCondVar.wait_for(lk,1000ms,[this]()->bool{
                return (mMessageQueue.empty()==false) || mIsDone;
            });
        }

        if (mIsDone) {
            break;
        }

        if (res) {
            Message msg;
            {
                std::lock_guard<std::mutex> g(mMutexMsgQueue);
                msg = mMessageQueue.front();
                mMessageQueue.pop();
            }

            LogDebug() << "Has message with id: " << msg.getId();

            {
                std::lock_guard<std::mutex> g(mMutexHdl);
                for (auto &e : mHandlers) {
                    e->process(msg);
                }
            }
        }
        else {
            LogDebug() << "Wait for event";
        }
    }
}

IPC_NS_END
CORE_NS_END
VOSLAM_NS_END