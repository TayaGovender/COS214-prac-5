#ifndef CAMPUS_ZONE_ADAPTER_H
#define CAMPUS_ZONE_ADAPTER_H

#include <iostream>

#include "LegacySecurity.h"
#include "CampusZone.h"

class Locklevel; // forward declaration

class CampusZoneAdapter : public CampusZone
{
    public:
        CampusZoneAdapter();
        bool lock(Locklevel level) override;
        bool unlock() override; 
        bool restrict() override;
        bool evacuate() override;
        CampusZoneAdapter();
    private:
        LegacySecurity* adaptee;
};

#endif //CAMPUS_ZONE_ADAPTER_H