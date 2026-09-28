#ifndef INCIDENT_H
#define INCIDENT_H

#include <memory>
#include <string>
#include "CampusTypes.h"

class IncidentState;
class CampusGuardMediator;

class Incident {
public:
    Incident(IncidentId id,
             const Location& location,
             Severity severity,
             const std::string& description);
    ~Incident();

    bool dispatch();
    bool markInProgress();
    bool resolve();
    bool cancel();

    std::string getStatus() const;

    IncidentId getId() const          { return id; }
    Location getLocation() const      { return location; }
    Severity getSeverity() const      { return severity; }
    std::string getDescription() const { return description; }

    void setMediator(CampusGuardMediator* m) { mediator = m; }

    // Public because state objects need to call it. Intended for internal use.
    void setState(std::unique_ptr<IncidentState> newState);

private:
    IncidentId id;
    Location location;
    Severity severity;
    std::string description;
    std::unique_ptr<IncidentState> state;
    CampusGuardMediator* mediator;
};

#endif