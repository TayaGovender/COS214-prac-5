#include "CampusBlock.h"
#include "Building.h"
#include "LegacySecurity.h"
#include "CampusZoneAdapter.h"
#include "CampusGuardMediator.h"
#include "CampusGuardFacade.h"
#include "CommandDispatcher.h"
#include "Command.h"
#include "SecurityService.h"
#include "MedicalService.h"
#include "FacilitiesService.h"
#include "CampusAlertService.h"
#include "Incident.h"
#include "DispatchUnitCommand.h"
#include "LockdownAreaCommand.h"
#include "ActivateAlertCommand.h"
#include "IssueEvacuationCommand.h"
#include "InvalidOperationException.h"
#include "CampusTypes.h"

#include <iostream>
#include <memory>

int main()
{
    std::cout << "===== CampusGuard =====" << std::endl;

    
    // 1. Build the campus layout (Composite + Adapter)
    
    CampusBlock* north = new CampusBlock("North Block");
    CampusBlock* south = new CampusBlock("South Block");

    Building* chem = new Building("Chemistry Building");
    Building* med  = new Building("Medical Building");
    Building* it   = new Building("IT Building");
    Building* law  = new Building("Law Building");

    north->addChild(chem);
    north->addChild(med);
    south->addChild(it);
    south->addChild(law);

    LegacySecurity*    northGate   = new LegacySecurity("North Gate");
    CampusZoneAdapter* gateAdapter = new CampusZoneAdapter(northGate, "North Gate Access");
    north->addChild(gateAdapter);

    std::cout << "\nCampus layout:" << std::endl;
    north->print();
    south->print();

    
    // 2. Wire up the coordination layer (Mediator + Facade + Command)
    
    CampusAlertService alertService;
    CampusGuardMediator mediator;
    SecurityService     security(&mediator);
    MedicalService      medical(&mediator);
    FacilitiesService   facilities(&mediator);

    mediator.setSecurityService(&security);
    mediator.setMedicalService(&medical);
    mediator.setFacilitiesService(&facilities);
    mediator.setAlertService(&alertService);

    CommandDispatcher  dispatcher(&mediator);
    CampusGuardFacade  facade(&mediator, &dispatcher, &alertService);

    
    // 3. Scenario 1: fire in the Chemistry Building
    //    Facade -> Mediator -> State -> Composite -> Adapter -> Alert
    
    std::cout << "\n=== Scenario 1: Fire in Chemistry ===" << std::endl;

    Incident fire(1, {"Chemistry Building", "Lab 3"}, Severity::High,
                  "Chemical fire reported");
    fire.setMediator(&mediator);

    facade.handleEmergency(fire, *north);

    // Operator attempts a second dispatch on the same incident.
    // The State pattern rejects it — this is our failure case.
    std::cout << "\n-- Attempting redundant Medical dispatch --" << std::endl;
    dispatcher.executeCommand(std::unique_ptr<Command>(
        new DispatchUnitCommand(&mediator, &fire, UnitType::Medical)));

    dispatcher.executeCommand(std::unique_ptr<Command>(
        new ActivateAlertCommand(&alertService, AlertLevel::Critical,
                                 "Fire in Chemistry Building")));

    // Drive the incident through the rest of its lifecycle.
    fire.markInProgress();
    fire.resolve();

    
    // 4. Scenario 2: medical emergency and evacuation
    //    Facade -> Mediator -> Command -> Composite -> Adapter
    
    std::cout << "\n=== Scenario 2: Medical Emergency ===" << std::endl;

    Incident collapse(2, {"Medical Building", "Ward 3"}, Severity::Critical,
                      "Student collapsed in Ward 3");
    collapse.setMediator(&mediator);

    facade.handleEvacuation(collapse, *south, "Medical emergency");

    dispatcher.executeCommand(std::unique_ptr<Command>(
        new LockdownAreaCommand(south, LockLevel::Restricted)));

    dispatcher.executeCommand(std::unique_ptr<Command>(
        new IssueEvacuationCommand(&mediator, south, "Medical emergency")));

    collapse.markInProgress();

    
    // 5. Failure case — invalid State transition, caught explicitly
    
    std::cout << "\n=== Invalid transition test ===" << std::endl;

    try {
        Incident resolved(3, {"IT Building", "Room 101"}, Severity::Low,
                          "Test incident");
        resolved.setMediator(&mediator);
        resolved.dispatch();
        resolved.markInProgress();
        resolved.resolve();
        resolved.cancel();
    }
    catch (const InvalidOperationException& ex) {
        std::cout << "[main] Caught expected error: " << ex.what() << std::endl;
    }

    
    // 6. Undo the last command (Command pattern)
    
    std::cout << "\n=== Undo last command ===" << std::endl;
    dispatcher.undoLast();

    
    // 7. Status snapshot
    
    std::cout << "\n=== Status ===" << std::endl;
    std::cout << "Fire incident status:     " << fire.getStatus() << std::endl;
    std::cout << "Medical incident status:  " << collapse.getStatus() << std::endl;
    std::cout << "Alert active:             "
              << (alertService.isAlertActive() ? "yes" : "no") << std::endl;
    std::cout << "Alerts broadcast:         "
              << alertService.getBroadcastCount() << std::endl;

    
    // 8. Cleanup — top-level composites own their children
    
    std::cout << "\n=== Cleanup ===" << std::endl;

    delete north;
    delete south;

    std::cout << "Done." << std::endl;
    return 0;
}