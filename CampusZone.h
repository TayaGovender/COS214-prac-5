#ifndef CAMPUSZONE_H
#define CAMPUSZONE_H

#include <iostream>
#include <vector>
#include <string>

class CampusZone
{
    public:
        CampusZone(){}; //constructor
        //virtual bool lock(Locklevel level);
        virtual bool unlock() = 0;
        virtual bool restrict() = 0;
        virtual bool evacuate() = 0;
        virtual void addChild(CampusZone* component) = 0;
        virtual void removeChild(CampusZone* component) = 0;
        virtual CampusZone* removeAndGet(CampusZone* component) = 0;
        virtual ~CampusZone(){};
};


#endif //CAMPUSZONE_H