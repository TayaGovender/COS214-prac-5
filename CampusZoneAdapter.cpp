#include "CampusZoneAdapter.h"

CampusZoneAdapter::CampusZoneAdapter(LegacySecurity* adaptee, std::string name) 
: CampusZone(name)
{
    this->adaptee = adaptee;
}

bool CampusZoneAdapter::lock(LockLevel level)
{
    if(level == LockLevel::None)
    {
        this->adaptee->sendAlert("Lock level had been decreased to None");
        this->secure = false;
        return false;
    }
    if(level == LockLevel::Full)
    {
        this->adaptee->lockGate();
        this->adaptee->sendAlert("Full Lockdown has been issued");
        this->secure = true;
        return true;
    }
    if(level ==  LockLevel::Restricted)
    {
        this->adaptee->sendAlert("Access to this area has been restricted");
        this->adaptee->checkPerimeter();
        this->secure = true;
        return true;
    }

    this->secure = false;
    return false;
}

bool CampusZoneAdapter::unlock()
{
    this->adaptee->unlockGate();
    this->adaptee->checkPerimeter();
    this->secure = false;
    return false;
}

bool CampusZoneAdapter::restrict()
{
    this->adaptee->sendAlert("Acess to area has been restricted");
    this->adaptee->checkPerimeter();
    this->secure = true;
    return true;
}

bool CampusZoneAdapter::evacuate()
{
    std::cout << "===Emergency Area Evacuation===\n";
    this->adaptee->lockGate();
    this->adaptee->sendAlert("Emergency Evacuation has been issued");
    this->adaptee->checkPerimeter();
    this->secure = true;
    return true;
}

bool CampusZoneAdapter::isSecure() const
{
    return this->secure;
}