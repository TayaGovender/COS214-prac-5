#ifndef CAMPUS_ZONE_H
#define CAMPUS_ZONE_H

#include <string>
#include "CampusTypes.h"

class CampusZone {
public:
    explicit CampusZone(const std::string& name) : name(name) {}
    virtual ~CampusZone() {}

    virtual bool lock(LockLevel level) = 0;
    virtual bool unlock() = 0;
    virtual bool restrict() = 0;
    virtual bool isSecure() const = 0;

    std::string getName() const { return name; }

protected:
    std::string name;
};

#endif