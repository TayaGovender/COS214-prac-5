#include "InProgressState.h"
#include "Incident.h"
#include "ResolvedState.h"
#include "CancelledState.h"
#include "InvalidOperationException.h"

InProgressState::InProgressState() {
    name = "In Progress";
}

bool InProgressState::dispatch(Incident& context) {
    throw InvalidOperationException(
        "Incident " + std::to_string(context.getId()) +
        " is already in progress; cannot dispatch again.");
}

bool InProgressState::markInProgress(Incident& context) {
    throw InvalidOperationException(
        "Incident " + std::to_string(context.getId()) +
        " is already in progress.");
}

bool InProgressState::resolve(Incident& context) {
    context.setState(
        std::unique_ptr<IncidentState>(new ResolvedState()));
    return true;
}

bool InProgressState::cancel(Incident& context) {
    context.setState(
        std::unique_ptr<IncidentState>(new CancelledState()));
    return true;
}

std::string InProgressState::getStatus() const {
    return name;
}