#ifndef CANCEL_LAST_COMMAND_H
#define CANCEL_LAST_COMMAND_H

#include "Command.h"

class CommandDispatcher;

class CancelLastCommand : public Command {
public:
    explicit CancelLastCommand(CommandDispatcher* dispatcher);
    ~CancelLastCommand();

    bool execute();
    bool undo();
    std::string getDescription() const;

private:
    CommandDispatcher* dispatcher;
};

#endif