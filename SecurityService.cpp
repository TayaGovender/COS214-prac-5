#include "SecurityService.h"
#include "CampusGuardMediator.h"
#include "Incident.h"
#include "CampusZone.h"

#include <iostream>

using namespace std;

SecurityService::SecurityService(CampusGuardMediator* mediator) : mediator(mediator){

}

bool SecurityService::dispatch(Incident& incident){
    std::cout << "[Security] Security unit dispatched to incident "<< incident.getId() << std::endl;

    return incident.dispatch();
}

bool SecurityService::secureArea(CampusZone& zone){
    std::cout <<"[Security] security reports an unsafe area " << std::endl;

    if(mediator != nullptr){
        mediator->reportUnsafeArea(zone);
        return true;
    }
    return false;
}