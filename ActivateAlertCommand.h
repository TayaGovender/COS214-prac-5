#ifndef ACTIVATE_ALERT_COMMAND_H
#define ACTIVATE_ALERT_COMMAND_H

#include "Command.h"
#include "CampusTypes.h"
#include <string>

class AlertService;

class ActivateAlertCommand : public Command {
public:
    ActivateAlertCommand(AlertService* alertService,
                         AlertLevel level,
                         const std::string& message);
    ~ActivateAlertCommand();

    bool execute();
    bool undo();
    std::string getDescription() const;

private:
    AlertService* alertService;
    AlertLevel level;
    std::string message;
};

#endif