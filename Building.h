#ifndef BUILDING_H
#define BUILDING_H

#include <iostream>
#include <string>

#include "CampusZone.h"
#include "CampusTypes.h"

class Building : public CampusZone
{
    public:
        Building(std::string name) : CampusZone(name){};
        bool lock(LockLevel level) override;
        bool unlock() override;
        bool restrict() override;
        bool evacuate() override;
        bool isSecure() const override;
        virtual ~Building(){};
};

#endif //BUILDING_H