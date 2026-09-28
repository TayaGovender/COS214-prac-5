#ifndef SECURITYSERVICE_H
#define SECURITYSERVICE_H

class CampusGuardMediator;
class Incident;
class CampusZone;

class SecurityService{
    private:
        CampusGuardMediator* mediator;

    public:
        SecurityService(CampusGuardMediator* mediator);
        bool dispatch(Incident& incident);
        bool secureArea(CampusZone& zone);
};

#endif