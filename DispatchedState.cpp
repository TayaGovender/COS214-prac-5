#include "DispatchedState.h"
#include "Incident.h"
#include "InProgressState.h"
#include "CancelledState.h"
#include "InvalidOperationException.h"

DispatchedState::DispatchedState() {
    name = "Dispatched";
}

bool DispatchedState::dispatch(Incident& context) {
    throw InvalidOperationException(
        "Incident " + std::to_string(context.getId()) +
        " is already dispatched.");
}

bool DispatchedState::markInProgress(Incident& context) {
    context.setState(
        std::unique_ptr<IncidentState>(new InProgressState()));
    return true;
}

bool DispatchedState::resolve(Incident& context) {
    throw InvalidOperationException(
        "Incident " + std::to_string(context.getId()) +
        " cannot be resolved while it is only dispatched.");
}

bool DispatchedState::cancel(Incident& context) {
    context.setState(
        std::unique_ptr<IncidentState>(new CancelledState()));
    return true;
}

std::string DispatchedState::getStatus() const {
    return name;
}