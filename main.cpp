#include <iostream>
#include <memory>
#include <exception>

#include "Incident.h"
#include "CampusGuardMediator.h"
#include "CommandDispatcher.h"
#include "DispatchUnitCommand.h"
#include "CancelLastCommand.h"
#include "LockdownAreaCommand.h"
#include "InvalidOperationException.h"
#include "CampusTypes.h"

// Pull in TestZone from above.
#include "TestZone.h"

int main() {
    CampusGuardMediator mediator;

    Incident incident(1, {"Science Building", "Lab 204"},
                      Severity::High, "Fire reported");
    incident.setMediator(&mediator);

    CommandDispatcher dispatcher(&mediator);

    TestZone scienceBuilding("Science Building");

    // 1) Dispatch security -> exercises Command + State transition
    dispatcher.executeCommand(
        std::unique_ptr<Command>(
            new DispatchUnitCommand(&mediator, &incident, UnitType::Security)));

    std::cout << "Status after dispatch: "
              << incident.getStatus() << "\n";

    // 2) Lockdown the zone -> exercises Command + CampusZone
    dispatcher.executeCommand(
        std::unique_ptr<Command>(
            new LockdownAreaCommand(&scienceBuilding, LockLevel::Full)));

    // 3) Advance the incident to In Progress, then resolve
    incident.markInProgress();
    std::cout << "Status after markInProgress: "
              << incident.getStatus() << "\n";

    incident.resolve();
    std::cout << "Status after resolve: "
              << incident.getStatus() << "\n";

    // 4) Invalid operation: try to cancel a resolved incident
    std::cout << "\nAttempting invalid cancel on resolved incident...\n";
    try {
        incident.cancel();
    } catch (const InvalidOperationException& ex) {
        std::cout << "Caught expected exception: " << ex.what() << "\n";
    }

    // 5) Undo the last command (cancel the lockdown)
    dispatcher.undoLast();

    // 6) CancelLastCommand exercise
    dispatcher.executeCommand(
        std::unique_ptr<Command>(new CancelLastCommand(&dispatcher)));

    std::cout << "\nHistory size: " << dispatcher.getHistorySize() << "\n";
    return 0;
}