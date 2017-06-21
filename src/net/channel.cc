#include "channel.h"
#include "eventLoop.h"

const uint32_t ReadEvent = EPOLLIN;
const uint32_t WriteEvent = EPOLLOUT;

namespace Explorer {

Channel::Channel(EventLoop* loop, int fd)
        : loop_(loop),
          fd_(fd),
          events_(0),
          revents_(0)
{ }

void
Channel::handleEvent()
{
        // 根据不同的事件进行不同的回调
        if (revents_ & ::ReadEvent)
        {
                if (readCallBack_)
                        readCallBack_();
        }
        if (revents_ & ::WriteEvent)
        {
                if (writeCallBack_)
                        writeCallBack_();
        }
}

void
Channel::setReadCallBack(const EventCallBack& cb)
{
        readCallBack_ = cb;
}

void
Channel::setWriteCallBack(const EventCallBack& cb)
{
        writeCallBack_ = cb;
}

void
Channel::enableRead()
{
        events_ |= ::ReadEvent;
        update();
}

void
Channel::enableWrite()
{
        events_ |= ::WriteEvent;
        update();
}

void
Channel::disableRead()
{
        events_ &= ~::ReadEvent;
        update();
}

void
Channel::disableWrite()
{
        events_ &= ~::WriteEvent;
        update();
}

void
Channel::update()
{
        loop_->updateChannel(this);
}

bool
Channel::readReady()
{
        return events_ & ::ReadEvent;
}

bool
Channel::writeReady()
{
        return events_ & ::WriteEvent;
}

} // namespace Explorer
