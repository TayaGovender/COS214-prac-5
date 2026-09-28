#ifndef CAMPUS_ZONE_ADAPTER_H
#define CAMPUS_ZONE_ADAPTER_H

#include <iostream>

#include "LegacySecurity.h"
#include "CampusZone.h"
#include "CampusTypes.h"


class CampusZoneAdapter : public CampusZone
{
    public:
        CampusZoneAdapter(LegacySecurity* adaptee, std::string name);
        bool lock(LockLevel level) override;
        bool unlock() override; 
        bool restrict() override;
        bool evacuate() override;
        bool isSecure() const override;
        ~CampusZoneAdapter(){delete adaptee;};
    private:
        LegacySecurity* adaptee;
};

#endif //CAMPUS_ZONE_ADAPTER_H