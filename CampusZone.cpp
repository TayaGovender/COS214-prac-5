// TestZone.h — replace with the real Room/Building when you integrate.
#include "CampusZone.h"
#include <iostream>

class TestZone : public CampusZone {
public:
    explicit TestZone(const std::string& name) : CampusZone(name) {}

    bool lock(LockLevel level) override {
        std::cout << "  [TestZone] " << name
                  << " locked to level " << static_cast<int>(level) << "\n";
        return true;
    }
    bool unlock() override {
        std::cout << "  [TestZone] " << name << " unlocked\n";
        return true;
    }
    bool restrict() override {
        std::cout << "  [TestZone] " << name << " restricted\n";
        return true;
    }
    bool isSecure() const override { return true; }
};