#include "MedicalService.h"
#include "CampusGuardMediator.h"
#include "Incident.h"
#include "CampusZone.h"

#include <iostream>

using namespace std;
MedicalService::MedicalService(CampusGuardMediator* mediator) : mediator(mediator){

}

bool MedicalService::dispatch(Incident& incident){
    std::cout << "[Medical] Medical unit dispatched to incident "<< incident.getId() << std::endl;

    return incident.dispatch();
}

void MedicalService::standBy(Incident& incident){
    std::cout <<"[Medical] Medical is standing by " << std::endl;

    if(mediator != nullptr){
        mediator->reportMedicalEmergency(indident);
    }

    
}