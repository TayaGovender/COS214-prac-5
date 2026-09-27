#ifndef CANCELLED_STATE_H
#define CANCELLED_STATE_H

#include "IncidentState.h"

class CancelledState : public IncidentState {
public:
    CancelledState();

    bool dispatch(Incident& context);
    bool markInProgress(Incident& context);
    bool resolve(Incident& context);
    bool cancel(Incident& context);
    std::string getStatus() const;
};

#endif