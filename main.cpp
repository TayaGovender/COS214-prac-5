#include "CampusBlock.h"
#include "Building.h"
#include "LegacySecurity.h"
#include "CampusZoneAdapter.h"
#include "CampusTypes.h"

#include "Incident.h"
#include "CampusGuardMediator.h"
#include "CommandDispatcher.h"
#include "DispatchUnitCommand.h"
#include "CancelLastCommand.h"
#include "LockdownAreaCommand.h"
#include "InvalidOperationException.h"
#include "TestZone.h"

#include <iostream>
#include <memory>
#include <exception>

int main()
{
    // ===== Composite / Adapter / Building / Zone tests =====
    std::cout << "Testing composite\n";
    CampusBlock* NorthBlock = new CampusBlock("North Block");
    CampusBlock* SouthBlock = new CampusBlock("South Block");
    CampusBlock* WestBlock  = new CampusBlock("West Block");
    CampusBlock* EastBlock = new CampusBlock("EastBlock");

    Building* IT = new Building("IT building");
    Building* Eng = new Building("Engineering");
    Building* Med = new Building("Medicinal Building");
    Building* ems = new Building("Economics");
    Building* math = new Building("Mathematics Buidling");
    Building* Law = new Building("Law Building");
    Building* Chem = new Building("Chemistry Building");

    std::cout << "Nodes and leaves created\n";
    std::cout << "Adding and removing children\n";

    NorthBlock->addChild(Med);
    NorthBlock->addChild(Chem);

    SouthBlock->addChild(IT);
    SouthBlock->addChild(math);

    WestBlock->addChild(Law);
    WestBlock->addChild(ems);

    EastBlock->addChild(Eng);

    std::cout << "Adding legacy systems\n";

    LegacySecurity* EngPark = new LegacySecurity("Engineering parking");
    LegacySecurity* EngBack = new LegacySecurity("Eng back entrance");
    LegacySecurity* MedMain = new LegacySecurity("Medicine Entrance");

    CampusZoneAdapter* EngP = new CampusZoneAdapter(EngPark, "Parking");
    CampusZoneAdapter* EngB = new CampusZoneAdapter(EngBack, "Back Entrance");
    CampusZoneAdapter* MedM = new CampusZoneAdapter(MedMain, "Main entrance");

    EastBlock->addChild(EngB);
    EastBlock->addChild(EngP);
    NorthBlock->addChild(MedM);

    std::cout << "Printing\n";

    NorthBlock->print();
    std::cout << "\n";

    SouthBlock->print();
    std::cout << "\n";

    WestBlock->print();
    std::cout << "\n";

    EastBlock->print();
    std::cout << "\n";

    std::cout << "removing\n";

    NorthBlock->removeChild(Chem);
    delete Chem;

    NorthBlock->print();

    std::cout << "Testing adpater.\n";

    std::cout << "\n";

    std::cout << "Testing Building functionality.\n";

    IT->lock(LockLevel::Full);
    Med->lock(LockLevel::Restricted);
    Eng->lock(LockLevel::None);
    IT->unlock();
    Med->restrict();
    Eng->evacuate();
    std::cout << std::endl;

    std::cout << "Testing Zone functionality.\n";
    NorthBlock->lock(LockLevel::Full);
    std::cout << std::endl;
    SouthBlock->lock(LockLevel::None);
    std::cout << std::endl;
    WestBlock->lock(LockLevel::Restricted);
    std::cout << std::endl;
    EastBlock->evacuate();
    std::cout << std::endl;
    NorthBlock->unlock();
    std::cout << std::endl;
    NorthBlock->restrict();
    std::cout << std::endl;

    std::cout << "Cleaning up\n";
    delete NorthBlock;
    delete SouthBlock;
    delete WestBlock;
    delete EastBlock;

    // ===== Command / Mediator / Incident tests =====
    std::cout << "\n--- Command / Mediator tests ---\n";

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