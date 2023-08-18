#include "customer.h"
#include <algorithm>

long Customer::getId() const
{
    return id;
}

int Customer::getNumberOfTravels()
{
    return travelList.size();
}

const std::string &Customer::getName() const
{
    return name;
}

long Customer::getTravelId(int index)
{
    return travelList[index]->getId();
}

std::string Customer::getTravelStart(long travelid)
{
    for(size_t i=0;i<travelList.size();i++){
        if(travelList[i]->getId()==travelid)
            return travelList[i]->getStart();
    }
    return "01011970";
}

std::string Customer::getTravelEnd(long travelid)
{
    for(size_t i=0;i<travelList.size();i++){
        if(travelList[i]->getId()==travelid)
            return travelList[i]->getEnd();
    }
    return "01011970";
}

std::shared_ptr<Travel> Customer::getTravel(long travelId)
{
    for(auto &reise:travelList)
        if(reise->getId()==travelId)
            return reise;
    return NULL;
}

Customer::Customer(long id, const std::string &name)
    :id(id),name(name)
{

}

void Customer::addTravel(std::shared_ptr<Travel>p_travel)
{
    travelList.push_back(p_travel);
}
