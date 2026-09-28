#ifndef INCIDENT_STATE_H
#define INCIDENT_STATE_H

#include <string>

class Incident;

class IncidentState {
public:
    virtual ~IncidentState() {}

    virtual bool dispatch(Incident& context) = 0;
    virtual bool markInProgress(Incident& context) = 0;
    virtual bool resolve(Incident& context) = 0;
    virtual bool cancel(Incident& context) = 0;
    virtual std::string getStatus() const = 0;

protected:
    std::string name;
};

#endif