#ifndef DISPATCH_UNIT_COMMAND_H
#define DISPATCH_UNIT_COMMAND_H

#include "Command.h"
#include "CampusTypes.h"

class CampusGuardMediator;
class Incident;

class DispatchUnitCommand : public Command {
public:
    DispatchUnitCommand(CampusGuardMediator* mediator,
                        Incident* incident,
                        UnitType unitType);
    ~DispatchUnitCommand();

    bool execute();
    bool undo();
    std::string getDescription() const;

private:
    CampusGuardMediator* mediator;
    Incident* incident;
    UnitType unitType;
};

#endif