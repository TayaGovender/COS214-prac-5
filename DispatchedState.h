#ifndef DISPATCHED_STATE_H
#define DISPATCHED_STATE_H

#include "IncidentState.h"

class DispatchedState : public IncidentState {
public:
    DispatchedState();

    bool dispatch(Incident& context);
    bool markInProgress(Incident& context);
    bool resolve(Incident& context);
    bool cancel(Incident& context);
    std::string getStatus() const;
};

#endif