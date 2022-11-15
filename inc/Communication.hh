#pragma once

constexpr int PORT = 6217;

class Communication {
public:
    virtual bool OpenConnection();
    virtual int Send(const char *sMesg);
    virtual int Close();

private:
    int Socket4Sending_;
};
