#include "FacilitiesService.h"
#include "CampusGuardMediator.h"
#include "Incident.h"
#include "CampusZone.h"

#include <iostream>

using namespace std;

FacilitiesService::FacilitiesService(CampusGuardMediator* mediator) : mediator(mediator){

}

bool FacilitiesService::dispatch(Incident& incident){
    std::cout << "[Facilities] Facilities unit dispatched to incident "<< incident.getId() << std::endl;

    return incident.dispatch();
}

bool FacilitiesService::restrictArea(CampusZone& zone){
    std::cout <<"[Facilities] Facilities restructs this area " << std::endl;

    return zone.restrict();
}