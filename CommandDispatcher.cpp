#include "CommandDispatcher.h"
#include "Command.h"
#include "InvalidOperationException.h"
#include <iostream>

CommandDispatcher::CommandDispatcher(CampusGuardMediator* mediator)
    : mediator(mediator) {}

CommandDispatcher::~CommandDispatcher() {}

bool CommandDispatcher::executeCommand(std::unique_ptr<Command> command) {
    if (!command) return false;

    try {
        bool result = command->execute();
        if (result) {
            std::cout << "[Dispatcher] Executed: "
                      << command->getDescription() << "\n";
            history.push_back(std::move(command));
        } else {
            std::cout << "[Dispatcher] Command reported failure: "
                      << command->getDescription() << "\n";
        }
        return result;
    }
    catch (const InvalidOperationException& ex) {
        std::cout << "[Dispatcher] Invalid operation: " << ex.what() << "\n";
        return false;
    }
}

bool CommandDispatcher::undoLast() {
    if (history.empty()) {
        std::cout << "[Dispatcher] Nothing to undo.\n";
        return false;
    }
    std::unique_ptr<Command> last = std::move(history.back());
    history.pop_back();

    try {
        bool result = last->undo();
        std::cout << "[Dispatcher] Undo " << last->getDescription()
                  << ": " << (result ? "success" : "failed") << "\n";
        return result;
    }
    catch (const InvalidOperationException& ex) {
        std::cout << "[Dispatcher] Invalid undo: " << ex.what() << "\n";
        return false;
    }
}

int CommandDispatcher::getHistorySize() const {
    return static_cast<int>(history.size());
}

void CommandDispatcher::clearHistory() {
    history.clear();
}