#ifndef CAMPUS_TYPES_H
#define CAMPUS_TYPES_H

#include <string>

enum class UnitType   { Security, Medical, Facilities };
enum class LockLevel  { None, Restricted, Full };
enum class AlertLevel { Info, Warning, Critical };
enum class Severity   { Low, Medium, High, Critical };
enum class ResponseEvent {
    UnitDispatched,
    UnitArrived,
    AreaSecured,
    AreaBreached,
    CasualtyFound,
    EvacuationComplete,
    StandDown
};

using IncidentId = int;
using AreaId     = int;

struct Location {
    std::string building;
    std::string room;
};

#endif