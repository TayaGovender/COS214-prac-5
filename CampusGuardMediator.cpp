#include "CampusGuardMediator.h"
#include "Incident.h"
#include "CampusZone.h"
#include "SecurityService.h"
#include "MedicalService.h"
#include "FacilitiesService.h"
#include "AlertService.h"
#include <iostream>

CampusGuardMediator::CampusGuardMediator() : security(nullptr), medical(nullptr), facilities(nullptr), alertService(nullptr) {}



// Command + State dependencies
void CampusGuardMediator::setSecurityService(SecurityService* service){
    security = service;
}

void CampusGuardMediator::setMedicalService(MedicalService* service){
    medical = service;
}

void CampusGuardMediator::setFacilitiesService(FacilitiesService* service){
    facilities = service;
}

void CampusGuardMediator::setAlertService(AlertService* service){
    alertService = service;
}

bool CampusGuardMediator::dispatchUnit(Incident& incident, UnitType type) {
    std::cout << "[Mediator] Dispatch request recieved."<<std::endl;

    switch(type){
        case UnitType::Security:
            if(security != nullptr){
                return security->dispatch(incident);
            }
            std::cout << "[Mediator] No SecurityService registered." << std::endl;
            return false;

        case UnitType::Medical:
            if(medical != nullptr){
                return medical->dispatch(incident);
            }
            std::cout << "[Mediator] No MedicalService registered." << std::endl;
            return false;

        case UnitType::Facilities:
            if(facilities != nullptr){
                return facilities->dispatch(incident);
            }
            std::cout << "[Mediator] No FacilitiesService registered." << std::endl;
            return false;
    }
    return false;
}

bool CampusGuardMediator::cancelDispatch(Incident& incident, UnitType type) {
    std::cout << "[Mediator] cancelDispatch on incident "
              << incident.getId()
              << " type=" << static_cast<int>(type) << "\n";
    return incident.cancel();
}



void CampusGuardMediator::onIncidentChanged(const Incident& incident) {
    std::cout << "[Mediator] onIncidentChanged: incident "
              << incident.getId()
              << " now " << incident.getStatus() << "\n";
}

void CampusGuardMediator::reportUnsafeArea(CampusZone& zone){
    std::cout << "[Mediator] Unsafe area reported" << std::endl;

    if(facilities != nullptr){
        facilities->restrictArea(zone);
    }
}

void CampusGuardMediator::reportMedicalEmergency(Incident& incident){
    std::cout<<"[Mediator] Medical emergency reported." << std::endl;

    if(security != nullptr){
        security->dispatch(incident);
    }
}



bool CampusGuardMediator::coordinateEvacuation(CampusZone& zone,
                                               const std::string& reason) {
    std::cout << "[Mediator] coordinateEvacuation reason="
              << reason << "\n";
    
    return zone.evacuate();
}





bool CampusGuardMediator::coordinateAreaLockdown(CampusZone& zone,
                                                 LockLevel level) {
    std::cout << "[Mediator STUB] coordinateAreaLockdown\n";
    return zone.lock(level);
}