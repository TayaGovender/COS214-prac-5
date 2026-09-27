#ifndef COMMAND_DISPATCHER_H
#define COMMAND_DISPATCHER_H

#include <memory>
#include <vector>

class Command;
class CampusGuardMediator;

class CommandDispatcher {
public:
    explicit CommandDispatcher(CampusGuardMediator* mediator);
    ~CommandDispatcher();

    bool executeCommand(std::unique_ptr<Command> command);
    bool undoLast();
    int getHistorySize() const;
    void clearHistory();

private:
    std::vector<std::unique_ptr<Command>> history;
    CampusGuardMediator* mediator;
};

#endif