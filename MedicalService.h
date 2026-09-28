#ifndef MEDICALSERVICE_H
#define MEDICALSERVICE_H

class CampusGuardMediator;
class Incident;
class CampusZone;

class MedicalService{
    private:
        CampusGuardMediator* mediator;

    public:
        MedicalService(CampusGuardMediator* mediator);
        bool dispatch(Incident& incident);
        void standBy(Incident& incident);
};

#endif