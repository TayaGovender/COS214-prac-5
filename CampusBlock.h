#ifndef CAMPUSBLOCK_H
#define CAMPUSBLOCK_H

#include <iostream>
#include <string>
#include <vector>

#include "CampusZone.h"
#include "CampusTypes.h"

class CampusBlock : public CampusZone
{
    public:
        CampusBlock(std::string name) : CampusZone(name){};
        void addChild(CampusZone* component) override;
        void removeChild(CampusZone* component) override;
        bool lock(LockLevel level) override;
        bool unlock() override;
        bool restrict() override;
        bool evacuate() override;
        bool isSecure() const override;
        void print();
        virtual ~CampusBlock();
    private:
        std::vector<CampusZone*> children;
};

#endif //CAMPUSBLOCK_H