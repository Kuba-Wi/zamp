#pragma once

#include "Communication.hh"

class CommunicationFake : public Communication {
public:
    bool OpenConnection() override { return true; }
    int Send(const char *sMesg) override { return 0; }
    int Close() override { return 0; }
};
