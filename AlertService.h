#ifndef ALERT_SERVICE_H
#define ALERT_SERVICE_H

#include <string>
#include "CampusTypes.h"

class AlertService {
public:
    virtual ~AlertService() {}

    virtual bool broadcastAlert(AlertLevel level,
                                const std::string& message) = 0;
};

#endif