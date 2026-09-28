#include "CancelledState.h"
#include "Incident.h"
#include "InvalidOperationException.h"

CancelledState::CancelledState() {
    name = "Cancelled";
}

bool CancelledState::dispatch(Incident& context) {
    throw InvalidOperationException(
        "Incident " + std::to_string(context.getId()) +
        " was cancelled and cannot be dispatched.");
}

bool CancelledState::markInProgress(Incident& context) {
    throw InvalidOperationException(
        "Incident " + std::to_string(context.getId()) +
        " was cancelled.");
}

bool CancelledState::resolve(Incident& context) {
    throw InvalidOperationException(
        "Incident " + std::to_string(context.getId()) +
        " was cancelled and cannot be resolved.");
}

bool CancelledState::cancel(Incident& context) {
    throw InvalidOperationException(
        "Incident " + std::to_string(context.getId()) +
        " is already cancelled.");
}

std::string CancelledState::getStatus() const {
    return name;
}