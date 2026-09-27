#ifndef CAMPUS_ZONE_H
#define CAMPUS_ZONE_H

#include "CampusTypes.h"

class CampusZone {
public:
    CampusZone() {}
    virtual ~CampusZone() {}

    // Access-control operations
    virtual bool lock(LockLevel level) = 0;
    virtual bool unlock() = 0;
    virtual bool restrict() = 0;
    virtual bool evacuate() = 0;

    // State query
    virtual bool isSecure() const = 0;

    // Composite child management (no-op in leaves, overridden in composites)
    virtual void addChild(CampusZone* child) {}
    virtual void removeChild(CampusZone* child) {}
};

#endif