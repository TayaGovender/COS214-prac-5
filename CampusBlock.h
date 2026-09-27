#ifndef CAMPUSBLOCK_H
#define CAMPUSBLOCK_H

#include <iostream>
#include <string>
#include <vector>

#include "CampusZone.h"

class CampusBlock : public CampusZone
{
    public:
        CampusBlock(std::string name);
        void addChild(CampusZone* component) override;
        void removeChild(CampusZone* component) override;
        CampusZone* removeAndGet(CampusZone* component) override;
        //bool lock(Locklevel level) override;
        bool unlock() override;
        bool restrict() override;
        bool evacuate() override;
        std::string getName();
        virtual ~CampusBlock();
    private:
        std::string name;
        std::vector<CampusZone*> children;
};

#endif //CAMPUSBLOCK_H