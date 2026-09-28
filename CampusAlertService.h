#ifndef CAMPUS_ALERT_SERVICE_H
#define CAMPUS_ALERT_SERVICE_H

#include "AlertService.h"
#include "CampusTypes.h"
#include <string>

class CampusAlertService : public AlertService {
public:
    CampusAlertService();
    ~CampusAlertService() override;

    // AlertService interface
    bool broadcastAlert(AlertLevel level, const std::string& message) override;

    // Domain helpers — useful for demo and validation
    bool isAlertActive() const;
    int  getBroadcastCount() const;
    void clearActiveAlert();

private:
    void sendToPA(AlertLevel level, const std::string& message);
    void sendToMobileApp(AlertLevel level, const std::string& message);
    void sendToDigitalSignage(AlertLevel level, const std::string& message);

    static std::string levelToString(AlertLevel level);

    bool active;
    int  broadcastCount;
};

#endif