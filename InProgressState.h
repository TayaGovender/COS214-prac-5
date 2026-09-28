#ifndef IN_PROGRESS_STATE_H
#define IN_PROGRESS_STATE_H

#include "IncidentState.h"

class InProgressState : public IncidentState {
public:
    InProgressState();

    bool dispatch(Incident& context);
    bool markInProgress(Incident& context);
    bool resolve(Incident& context);
    bool cancel(Incident& context);
    std::string getStatus() const;
};

#endif