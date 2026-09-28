#ifndef CAMPUS_GUARD_MEDIATOR_H
#define CAMPUS_GUARD_MEDIATOR_H

#include <string>
#include "CampusTypes.h"

class Incident;
class CampusZone;
class SecurityService;
class MedicalService;
class FacilitiesService;
class AlertService;


class CampusGuardMediator {
    private:
        SecurityService* security;
        MedicalService* medical;
        FacilitiesService* facilities;
        AlertService* alertService;
public:
    CampusGuardMediator();
    void setSecurityService(SecurityService* service);
    void setMedicalService(MedicalService* service);
    void setFacilitiesService(FacilitiesService* service);
    void setAlertService(AlertService* service);

    bool dispatchUnit(Incident& incident, UnitType type);
    bool cancelDispatch(Incident& incident, UnitType type);

    void onIncidentChanged(const Incident& incident);
    
    void reportUnsafeArea(CampusZone& zone);
    void reportMedicalEmergency(Incident& incident);
    
    bool coordinateAreaLockdown(CampusZone& zone, LockLevel level);
    bool coordinateEvacuation(CampusZone& zone, const std::string& reason);
};

#endif