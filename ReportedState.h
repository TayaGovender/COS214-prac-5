#ifndef REPORTED_STATE_H
#define REPORTED_STATE_H

#include "IncidentState.h"

class ReportedState : public IncidentState {
public:
    ReportedState();

    bool dispatch(Incident& context);
    bool markInProgress(Incident& context);
    bool resolve(Incident& context);
    bool cancel(Incident& context);
    std::string getStatus() const;
};

#endif