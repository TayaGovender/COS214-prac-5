#ifndef ISSUE_EVACUATION_COMMAND_H
#define ISSUE_EVACUATION_COMMAND_H

#include "Command.h"
#include <string>

class CampusGuardMediator;
class CampusZone;

class IssueEvacuationCommand : public Command {
public:
    IssueEvacuationCommand(CampusGuardMediator* mediator,
                           CampusZone* zone,
                           const std::string& reason);
    ~IssueEvacuationCommand();

    bool execute();
    bool undo();
    std::string getDescription() const;

private:
    CampusGuardMediator* mediator;
    CampusZone* zone;
    std::string reason;
};

#endif