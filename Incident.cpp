#include "Incident.h"
#include "IncidentState.h"
#include "ReportedState.h"
#include "CampusGuardMediator.h"

Incident::Incident(IncidentId id,
                   const Location& location,
                   Severity severity,
                   const std::string& description)
    : id(id),
      location(location),
      severity(severity),
      description(description),
      mediator(nullptr) {
    state = std::unique_ptr<IncidentState>(new ReportedState());
}

Incident::~Incident() {}

bool Incident::dispatch() {
    return state->dispatch(*this);
}

bool Incident::markInProgress() {
    return state->markInProgress(*this);
}

bool Incident::resolve() {
    return state->resolve(*this);
}

bool Incident::cancel() {
    return state->cancel(*this);
}

std::string Incident::getStatus() const {
    return state->getStatus();
}

void Incident::setState(std::unique_ptr<IncidentState> newState) {
    state = std::move(newState);
    if (mediator) {
        mediator->onIncidentChanged(*this);
    }
}