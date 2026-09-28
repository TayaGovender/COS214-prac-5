#ifndef LEGACY_SECURITY_H
#define LEGACY_SECURITY_H

#include <iostream>
#include <string>

class LegacySecurity
{
    public:
        LegacySecurity(std::string name);
        void lockGate();
        void unlockGate();
        void sendAlert();
        void checkPerimeter();
        ~LegacySecurity();
};

#endif //LEGACY_SECURITY_H