#ifndef RESOLVED_STATE_H
#define RESOLVED_STATE_H

#include "IncidentState.h"

class ResolvedState : public IncidentState {
public:
    ResolvedState();

    bool dispatch(Incident& context);
    bool markInProgress(Incident& context);
    bool resolve(Incident& context);
    bool cancel(Incident& context);
    std::string getStatus() const;
};

#endif