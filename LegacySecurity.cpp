#include "LegacySecurity.h"

LegacySecurity::LegacySecurity(std::string name)
{
    this->name = name;
}

void LegacySecurity::lockGate()
{
    std::cout << this->name << ": Gates being locked now...\n";
    std::cout << "Gates locked.\n";
}

void LegacySecurity::unlockGate()
{
    std::cout << this->name << ": Gates being unlocked now...\n";
    std::cout << "Gates unlocked.\n";
}
void LegacySecurity::sendAlert(std::string reason)
{
    std::cout << "sending alert to nearby staff...\n";
    std::cout << "Reason: " << reason << std::endl;
}

void LegacySecurity::checkPerimeter()
{
    std::cout << "Security is surverying the area...\n";
}


