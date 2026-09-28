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

void CampusBlock::print()
{
    std::cout << "Block name: " << getName() << std::endl;
    std::cout << "Buildings in block:\n";
    int size = this->children.size();
    for(int i = 0 ; i < size; i++)
    {
        std::cout << this->children[i]->getName() << std::endl;
    }
}

bool CampusBlock::lock(LockLevel level)
{
    bool overallSecure = true;
    if(level == LockLevel::None)
    {
        this->secure = false;
        return false;
    }
    int size  = this->children.size();
    if(level == LockLevel::Full)
    {
        std::cout << "A full lockdown has been issued.\n";

        for(int i = 0; i < size; i++)
        {
            bool childSecure = this->children[i]->lock(level);
            if(childSecure == false)
            {
                overallSecure = false;
            }
            this->secure = overallSecure;
        }
        this->secure = overallSecure;
        return overallSecure;
    }
    if(level == LockLevel::Restricted)
    {
        std::cout << "Restricting area: " << getName() << "\n";

        for(int i = 0; i < size; i++)
        {
            bool child = this->children[i]->lock(level);
            if(child == false)
            {
                overallSecure = false;
            }
        }
        this->secure = overallSecure;
        return overallSecure;

    }
    this->secure = false;
    return false;
}

bool CampusBlock::unlock()
{
    std::cout << "unlocking area: " << getName() << "\n";

    int size = this->children.size();
    for(int i = 0; i < size; i++)
    {
        this->children[i]->unlock();
    }


    this->secure = false;
    return false;
}

bool CampusBlock::restrict()
{
    bool overallSecure = true;
    int size = this->children.size();
    std::cout << "Restricting area: " << getName() << "\n";
    for(int i = 0; i < size; i++)
    {
        bool child = this->children[i]->restrict();
        if(child == false)
        {
            overallSecure = false;
        }
    }
    this->secure = overallSecure;
    return overallSecure;
}

bool CampusBlock::evacuate()
{
    bool overallSecure = true;
    int size = this->children.size();
    std::cout << "===Emergency evacuation===\n";
    std::cout << "Area: " << getName() << std::endl;
    for(int i = 0; i < size; i++)
    {
        bool child = this->children[i]->evacuate();
        if(child == false)
            {
                overallSecure = false;
            }
    }

    this->secure = overallSecure;
    return overallSecure;
}

bool CampusBlock::isSecure() const
{
    int size = this->children.size();
    if(size == 0){return false;}
    for(int i = 0; i < size; i++)
    {
        if(this->children[i]->isSecure() == false)
        {
            return false;
        }
    }
    return true;
}

CampusBlock::~CampusBlock()
{
    int size = this->children.size();
    for(int i = 0; i < size; i++)
    {
        delete this->children[i];
    }
}