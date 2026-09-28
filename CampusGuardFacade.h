#ifndef CAMPUSGUARDFACADE_H
#define CAMPUSGUARDFACADE_H

#include <string>
#include "CampusTypes.h"

class CampusGuardMediator;
class CommandDispatcher;
class Incident;
class CampusZone;
class AlertService;


class CampusGuardFacade{
    private:
        CampusGuardMediator* mediator;

    public:
        CampusGuardFacade(CampusGuardMediator* mediator, CommandDispatcher* dispatcher, AlertService* alertService);
        bool handleEmergency(Incident& incident, CampusZone& zone);
        bool handleEvacuation(Incident& incident, CampusZone& zone, const std::string& reason);

};

#endif
