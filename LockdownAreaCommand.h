#ifndef LOCKDOWN_AREA_COMMAND_H
#define LOCKDOWN_AREA_COMMAND_H

#include "Command.h"
#include "CampusTypes.h"

class CampusZone;

class LockdownAreaCommand : public Command {
public:
    LockdownAreaCommand(CampusZone* zone, LockLevel level);
    ~LockdownAreaCommand();

    bool execute();
    bool undo();
    std::string getDescription() const;

private:
    CampusZone* zone;
    LockLevel level;
};

#endif