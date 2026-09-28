#include "ActivateAlertCommand.h"
#include "AlertService.h"

ActivateAlertCommand::ActivateAlertCommand(AlertService* alertService,
                                           AlertLevel level,
                                           const std::string& message)
    : alertService(alertService), level(level), message(message) {
    description = "Activate alert";
}

ActivateAlertCommand::~ActivateAlertCommand() {}

bool ActivateAlertCommand::execute() {
    if (!alertService) return false;
    return alertService->broadcastAlert(level, message);
}

bool ActivateAlertCommand::undo() {
    if (!alertService) return false;
    return alertService->broadcastAlert(AlertLevel::Info,
                                        "All clear: " + message);
}

std::string ActivateAlertCommand::getDescription() const {
    return description;
}