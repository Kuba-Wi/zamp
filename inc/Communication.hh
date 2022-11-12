#pragma once

constexpr int PORT = 6217;

class Communication {
public:
    bool OpenConnection();
    int Send(const char *sMesg);
    int Close();

private:
    int Socket4Sending_;
};
