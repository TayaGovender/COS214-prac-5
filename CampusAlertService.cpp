#include "CampusAlertService.h"
#include <iostream>

CampusAlertService::CampusAlertService()
    : active(false), broadcastCount(0) {}

CampusAlertService::~CampusAlertService() {}

std::string CampusAlertService::levelToString(AlertLevel level) {
    switch (level) {
        case AlertLevel::Info:     return "INFO";
        case AlertLevel::Warning:  return "WARNING";
        case AlertLevel::Critical: return "CRITICAL";
    }
    return "UNKNOWN";
}

void CampusAlertService::sendToPA(AlertLevel level,
                                  const std::string& message) {
    std::cout << "  [PA System] " << levelToString(level)
              << ": " << message << std::endl;
}

void CampusAlertService::sendToMobileApp(AlertLevel level,
                                         const std::string& message) {
    std::cout << "  [Mobile App] push -> " << levelToString(level)
              << ": " << message << std::endl;
}

void CampusAlertService::sendToDigitalSignage(AlertLevel level,
                                              const std::string& message) {
    std::cout << "  [Digital Signage] " << levelToString(level)
              << ": " << message << std::endl;
}

bool CampusAlertService::broadcastAlert(AlertLevel level,
                                        const std::string& message) {
    // Failure case: refuse to broadcast an empty alert.
    if (message.empty()) {
        std::cout << "[AlertService] Refused empty alert message." << std::endl;
        return false;
    }

    std::cout << "[AlertService] Broadcasting "
              << levelToString(level)
              << " alert: \"" << message << "\"" << std::endl;

    // Every alert goes to the mobile app.
    sendToMobileApp(level, message);

    // Warning and Critical alerts also hit PA and digital signage.
    if (level == AlertLevel::Warning || level == AlertLevel::Critical) {
        sendToPA(level, message);
        sendToDigitalSignage(level, message);
    }

    broadcastCount++;
    active = (level != AlertLevel::Info);
    return true;
}

bool CampusAlertService::isAlertActive() const {
    return active;
}

int CampusAlertService::getBroadcastCount() const {
    return broadcastCount;
}

void CampusAlertService::clearActiveAlert() {
    active = false;
    std::cout << "[AlertService] Active alert cleared." << std::endl;
}