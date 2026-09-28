#ifndef FACILITIESSERVICE_H
#define FACILITIESSERVICE_H

class CampusGuardMediator;
class Incident;
class CampusZone;

class FacilitiesService{
    private:
        CampusGuardMediator* mediator;

    public:
        FacilitiesService(CampusGuardMediator* mediator);
        bool dispatch(Incident& incident);
        bool restrictArea(CampusZone& zone);
};

#endif