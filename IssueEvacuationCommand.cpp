#include "IssueEvacuationCommand.h"
#include "CampusGuardMediator.h"
#include "CampusZone.h"

IssueEvacuationCommand::IssueEvacuationCommand(CampusGuardMediator* mediator,
                                               CampusZone* zone,
                                               const std::string& reason)
    : mediator(mediator), zone(zone), reason(reason) {
    description = "Issue evacuation";
}

IssueEvacuationCommand::~IssueEvacuationCommand() {}

bool IssueEvacuationCommand::execute() {
    if (!mediator || !zone) return false;
    return mediator->coordinateEvacuation(*zone, reason);
}

bool IssueEvacuationCommand::undo() {
    // Evacuation instructions cannot be un-issued in this system.
    return false;
}

std::string IssueEvacuationCommand::getDescription() const {
    return description;
}