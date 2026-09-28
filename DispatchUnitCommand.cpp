#include "DispatchUnitCommand.h"
#include "CampusGuardMediator.h"
#include "Incident.h"

DispatchUnitCommand::DispatchUnitCommand(CampusGuardMediator* mediator,
                                         Incident* incident,
                                         UnitType unitType)
    : mediator(mediator), incident(incident), unitType(unitType) {
    description = "Dispatch unit";
}

DispatchUnitCommand::~DispatchUnitCommand() {}

bool DispatchUnitCommand::execute() {
    if (!mediator || !incident) return false;
    return mediator->dispatchUnit(*incident, unitType);
}

bool DispatchUnitCommand::undo() {
    if (!mediator || !incident) return false;
    return mediator->cancelDispatch(*incident, unitType);
}

std::string DispatchUnitCommand::getDescription() const {
    return description;
}