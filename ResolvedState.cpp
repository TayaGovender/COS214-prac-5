#include "ResolvedState.h"
#include "Incident.h"
#include "InvalidOperationException.h"

ResolvedState::ResolvedState() {
    name = "Resolved";
}

bool ResolvedState::dispatch(Incident& context) {
    throw InvalidOperationException(
        "Incident " + std::to_string(context.getId()) +
        " is already resolved and cannot be dispatched again.");
}

bool ResolvedState::markInProgress(Incident& context) {
    throw InvalidOperationException(
        "Incident " + std::to_string(context.getId()) +
        " is already resolved.");
}

bool ResolvedState::resolve(Incident& context) {
    throw InvalidOperationException(
        "Incident " + std::to_string(context.getId()) +
        " is already resolved.");
}

bool ResolvedState::cancel(Incident& context) {
    throw InvalidOperationException(
        "Incident " + std::to_string(context.getId()) +
        " is already resolved and cannot be cancelled.");
}

std::string ResolvedState::getStatus() const {
    return name;
}