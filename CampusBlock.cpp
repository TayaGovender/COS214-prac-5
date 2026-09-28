#include "CampusBlock.h"


void CampusBlock::addChild(CampusZone* component)
{
    if(component == nullptr){return;}

    int size = this->children.size();
    bool exists = false;
    for(int i = 0; i < size; i++)
    {
        if(this->children[i] == component)
        {
            exists = true;
        }
    }

    if(!exists)
    {
        this->children.push_back(component);
    }
}

void CampusBlock::removeChild(CampusZone* component)
{
    if(component == nullptr){return;}

    
    int size = this->children.size();
    for(int i = 0; i < size; i++)
    {
        if(this->children[i] == component)
        {
            this->children[i] = this->children.back();
            this->children.pop_back();
            return;
        }
    }

}

CampusZone* CampusBlock::removeAndGet(CampusZone* component)
{
    if(component == nullptr){return;}

        
    int size = this->children.size();
    for(int i = 0; i < size; i++)
    {
        if(this->children[i] == component)
        {
            CampusZone* removed = this->children[i];
            this->children[i] = this->children.back();
            this->children.pop_back();
            return removed;      
        }
    }
}

std::string CampusBlock::getName()
{
    return this->name;
}

void CampusBlock::print()
{
    std::cout << "Block name: " << this->name << std::endl;
    std::cout << "Buildings in block:\n";
    int size = this->children.size();
    for(int i = 0 ; i < size; i++)
    {
        std::cout << this->children[i]->getName() << std::endl;
    }
}

