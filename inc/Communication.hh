#pragma once

#include <mutex>

constexpr int PORT = 6217;

class Communication {
public:
    virtual bool OpenConnection();
    virtual int Send(const char *sMesg);
    virtual int Close();

    void lockAccess() { com_mx_.lock(); }
    void unlockAccess() { com_mx_.unlock(); }

private:
    int Socket4Sending_;
    std::mutex com_mx_;
};
