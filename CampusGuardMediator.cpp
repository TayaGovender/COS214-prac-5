#include "CampusGuardMediator.h"
#include "Incident.h"
#include "CampusZone.h"
#include <iostream>

CampusGuardMediator::CampusGuardMediator() {}
CampusGuardMediator::~CampusGuardMediator() {}


// Command + State dependencies


void CampusGuardMediator::onIncidentChanged(const Incident& incident) {
    std::cout << "[Mediator] onIncidentChanged: incident "
              << incident.getId()
              << " now " << incident.getStatus() << "\n";
}

bool CampusGuardMediator::dispatchUnit(Incident& incident, UnitType type) {
    std::cout << "[Mediator] dispatchUnit on incident "
              << incident.getId()
              << " type=" << static_cast<int>(type) << "\n";
    return incident.dispatch();
}

bool CampusGuardMediator::cancelDispatch(Incident& incident, UnitType type) {
    std::cout << "[Mediator] cancelDispatch on incident "
              << incident.getId()
              << " type=" << static_cast<int>(type) << "\n";
    return incident.cancel();
}

bool CampusGuardMediator::coordinateEvacuation(CampusZone& zone,
                                               const std::string& reason) {
    std::cout << "[Mediator] coordinateEvacuation reason="
              << reason << "\n";
    bool ok = zone.lock(LockLevel::Full);
    if (!ok) return false;
    return zone.restrict();
}


// Mediator function stub - update


bool CampusGuardMediator::coordinateAreaLockdown(CampusZone& zone,
                                                 LockLevel level) {
    std::cout << "[Mediator STUB] coordinateAreaLockdown\n";
    return zone.lock(level);
}