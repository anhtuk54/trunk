#pragma once

#include "common/CommonDefs.h"
#include "utils/Logger.h"

#include <memory>
#include <string>
#include <functional>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <thread>
#include <condition_variable>

VOSLAM_NS_BEGIN
CORE_NS_BEGIN
IPC_NS_BEGIN

class Message
{

public:
    /**
     * @brief Construct a new Message object
     * 
     */
    Message()
    {
    }

    /**
     * @brief Copy construct a new Message object
     * 
     * @param other 
     */
    Message(const Message &other) : mId{other.mId}, mPayload{other.mPayload}
    {
    }

    template<typename T>
    void setPayload(const T &pl)
    {
        mPayload = std::make_shared<T>(pl);   
    }

    template<typename T>
    T getPlayload() const
    {
        const T pl = *(T*)mPayload.get();
        return pl;
    }

    void setId(const std::string &id)
    {
        mId = id;
    }

    std::string getId() const
    {
        return mId;
    }


private:
    std::string mId="";
    mutable std::shared_ptr<void> mPayload=nullptr;
};


class Handler
{
    using HandlerCb = std::function<void(const Message&)>; 
public:

    /**
     * @brief Construct a new Handler object
     * 
     */
    Handler(HandlerCb cb, const std::string &loopId);

    /**
     * @brief Destroy the Handler object
     * 
     */
    ~Handler();

    void build();

    /**
     * @brief Post a message to message queue of looper the handler belong to
     * 
     * @param msg 
     */
    void post(const Message &msg);

    /**
     * @brief Processing specific message.
     * 
     */
    void process(const Message &msg);

private:
    HandlerCb mCb=nullptr;
    std::string mLooperId="";
};

class HandlerBuilder
{
    using HandlerCb = std::function<void(const Message&)>; 
public:
    HandlerBuilder();
    ~HandlerBuilder()=default;
    HandlerBuilder& addCallback(HandlerCb cb);
    HandlerBuilder& addLooperId(const std::string &id);
    std::shared_ptr<Handler> build();

    HandlerCb mCb;
    std::string mLooperId;
};


class Looper
{
public:
    /**
     * @brief Constructor.
     * 
     */
    Looper() = delete;

    /**
     * @brief Copy constructor.
     * 
     * @param other 
     * 
     */
    Looper(const Looper &other) = delete;

    /**
     * @brief Construct a new Looper object
     *  
     * @param id 
     * 
     */
    Looper(const std::string &id);    
    /**
     * @brief Destroy the Looper object
     * 
     */
    ~Looper();

    /**
     * @brief Start execution of looper
     * 
     */
    void run();

    /**
     * @brief Stop execution of looper
     * 
     */
    void quit();

    /**
     * @brief Post a message into queue.
     * 
     * @param msg 
     * 
     * @private
     */
    void post(const Message &msg);


    /**
     * @brief Adding a Handler to the list for listening notification.
     * 
     * @param hdl 
     * 
     * @private
     */
    void attachHandler(std::shared_ptr<Handler> hdl);

    /**
     * @brief Method for creating and resgitering looper object.
     * 
     * @param id 
     */
    static std::shared_ptr<Looper> create(const std::string &id);

    /**
     * @brief Access to the looper object corresponding to id.
     * 
     * @param id 
     * @return std::shared_ptr<Looper> 
     */
    static std::shared_ptr<Looper> get(const std::string &id);

protected:
    virtual void process();

private:
    // The pool
    static std::map<std::string, std::shared_ptr<Looper>> LooperPool;

    // Message and Handler lists
    std::string mId;
    std::vector<std::shared_ptr<Handler>> mHandlers={};
    std::queue<Message> mMessageQueue={};

    // Thread handling
    bool mIsDone=false;
    std::unique_ptr<std::thread> mThread=nullptr;
    std::mutex mMutexMsgQueue;
    std::mutex mMutexHdl;
    std::condition_variable mCondVar;
};


IPC_NS_END
CORE_NS_END
VOSLAM_NS_END
