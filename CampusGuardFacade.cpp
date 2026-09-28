#include "CampusGuardMediator.h"
#include "CampusGuardFacade.h"
#include "Incident.h"
#include "CampusZone.h"

#include <iostream>

CampusGuardFacade::CampusGuardFacade(CampusGuardMediator* mediator, CommandDispatcher* dispatcher, AlertService* alertService) : mediator(mediator), dispatcher(dispatcher), alertService(alertService){}

bool CampusGuardFacade::handleEmergency(Incident& incident, CampusZone& zone){
    std::cout << "[Facade] Starting emergency response." << std::endl;

    if (!mediator->coordinateAreaLockdown(zone, LockLevel::Full)) {
        std::cout << "[Facade] Failed to lock area." << std::endl;
        return false;
    }

    if (!mediator->dispatchUnit(incident, UnitType::Security)) {
        std::cout << "[Facade] Failed to dispatch security." << std::endl;
        return false;
    }

    if (alertService != nullptr) {
        alertService->broadcastAlert(
            AlertLevel::Critical,
            "Emergency at " + zone.getName() + " — stay clear");
    }

    mediator->reportUnsafeArea(zone);

    std::cout << "[Facade] Emergency response initiated." << std::endl;
    return true;
}

bool CampusGuardFacade::handleEvacuation(Incident& incident, CampusZone& zone, const std::string& reason){
    std::cout << "[Facade] Starting evacuation process" << std::endl;

    bool securityDispatched = mediator->dispatchUnit(incident, UnitType::Security);

    if(!securityDispatched){
        std::cout << "[Facade] Security dispatch failed."<<std::endl;

        return false;
    }

    bool evacuated = mediator->coordinateEvacuation(zone, reason);

    if(!evacuated){
        std::cout << "[Facade] Evacuation failed." << std::endl;

        return false;
    }

    mediator->reportUnsafeArea(zone);
    std::cout << "[Facade] Evacuation response completed." << std::endl;

    return true;
}