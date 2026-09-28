#include "ReportedState.h"
#include "Incident.h"
#include "DispatchedState.h"
#include "CancelledState.h"
#include "InvalidOperationException.h"

ReportedState::ReportedState() {
    name = "Reported";
}

bool ReportedState::dispatch(Incident& context) {
    context.setState(
        std::unique_ptr<IncidentState>(new DispatchedState()));
    return true;
}

bool ReportedState::markInProgress(Incident& context) {
    throw InvalidOperationException(
        "Incident " + std::to_string(context.getId()) +
        " cannot move to InProgress before it is dispatched.");
}

bool ReportedState::resolve(Incident& context) {
    throw InvalidOperationException(
        "Incident " + std::to_string(context.getId()) +
        " cannot be resolved before it is dispatched.");
}

bool ReportedState::cancel(Incident& context) {
    context.setState(
        std::unique_ptr<IncidentState>(new CancelledState()));
    return true;
}

std::string ReportedState::getStatus() const {
    return name;
}