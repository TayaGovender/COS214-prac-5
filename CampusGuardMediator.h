#ifndef CAMPUS_GUARD_MEDIATOR_H
#define CAMPUS_GUARD_MEDIATOR_H

#include <string>
#include "CampusTypes.h"

class Incident;
class CampusZone;

class CampusGuardMediator {
public:
    CampusGuardMediator();
    ~CampusGuardMediator();

    void onIncidentChanged(const Incident& incident);
    bool dispatchUnit(Incident& incident, UnitType type);
    bool cancelDispatch(Incident& incident, UnitType type);
    bool coordinateAreaLockdown(CampusZone& zone, LockLevel level);
    bool coordinateEvacuation(CampusZone& zone, const std::string& reason);
};

#endif