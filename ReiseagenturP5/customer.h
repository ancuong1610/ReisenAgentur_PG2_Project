#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "travel.h"
#include <memory>
#include <string>
class Customer
{
    long id;
    std::string name;
    std::vector <std::shared_ptr<Travel>>travelList;
public:
    Customer(long id, const std::string &name);
    void addTravel(std::shared_ptr<Travel> p_travel);
    long getId() const;

    int getNumberOfTravels();
    const std::string &getName() const;

    //Print travel Table functions
    long getTravelId(int index);
    std::string getTravelStart(long travelid);
    std::string getTravelEnd(long travelid);

    //save Travel in Kundenprofil
    std::shared_ptr<Travel> getTravel(long travelId);
};

#endif // CUSTOMER_H
