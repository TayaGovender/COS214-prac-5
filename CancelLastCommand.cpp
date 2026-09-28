#include "CancelLastCommand.h"
#include "CommandDispatcher.h"

CancelLastCommand::CancelLastCommand(CommandDispatcher* dispatcher)
    : dispatcher(dispatcher) {
    description = "Cancel last command";
}

CancelLastCommand::~CancelLastCommand() {}

bool CancelLastCommand::execute() {
    if (!dispatcher) return false;
    return dispatcher->undoLast();
}

bool CancelLastCommand::undo() {
    // Undoing a cancel is not supported.
    return false;
}

std::string CancelLastCommand::getDescription() const {
    return description;
}