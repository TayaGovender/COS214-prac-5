#include "LockdownAreaCommand.h"
#include "CampusZone.h"

LockdownAreaCommand::LockdownAreaCommand(CampusZone* zone, LockLevel level)
    : zone(zone), level(level) {
    description = "Lockdown area";
}

LockdownAreaCommand::~LockdownAreaCommand() {}

bool LockdownAreaCommand::execute() {
    if (!zone) return false;
    return zone->lock(level);
}

bool LockdownAreaCommand::undo() {
    if (!zone) return false;
    return zone->unlock();
}

std::string LockdownAreaCommand::getDescription() const {
    return description;
}