#include "Building.h"

bool Building::lock(LockLevel level)
{
    if(level == LockLevel::None)
    {
        std::cout << getName() << " has free access\n";
        this->secure = false;
        return false;
    }
    if(level == LockLevel::Full)
    {
        std::cout << getName() << " is going under full lockdown now\n";
        this->secure = true;
        return true;
    }
    if(level == LockLevel::Restricted)
    {
        std::cout << getName() << "  is now restricted.";
        this->secure = true;
        return true;
    }
    
    this->secure = false;
    return false;
}

bool Building::unlock()
{
    std::cout << "Building is being unlocked now\n";
    this->secure = false;
    return false;
}

bool Building::restrict()
{
    std::cout << "Building is now limiting access\n";
    this->secure = true;
    return true;
}

bool Building::evacuate()
{
    std::cout << getName() << " is undergoing locked emergency evacuation\n";
    this->secure = true;
    return true;
}

bool Building::isSecure() const
{
    return this->secure;
}