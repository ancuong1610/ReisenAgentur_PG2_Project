#include "rentalcarreservation.h"

#include <sstream>
const std::string &RentalCarReservation::getPickupLocation() const
{
    return pickupLocation;
}

void RentalCarReservation::setPickupLocation(const std::string &newPickupLocation)
{
    pickupLocation = newPickupLocation;
}

const std::string &RentalCarReservation::getReturnLocation() const
{
    return returnLocation;
}

void RentalCarReservation::setReturnLocation(const std::string &newReturnLocation)
{
    returnLocation = newReturnLocation;
}

const std::string &RentalCarReservation::getCompany() const
{
    return company;
}

void RentalCarReservation::setCompany(const std::string &newCompany)
{
    company = newCompany;
}

RentalCarReservation::RentalCarReservation(int id, double price, long travelId, const std::string &fromDate, const std::string &toDate, std::vector<long> vorgaengerId,
                                           const std::string &pickupLocation, const std::string returnLocation, const std::string &company)
    :Booking(id, price, travelId, fromDate, toDate, vorgaengerId),
      pickupLocation(pickupLocation), returnLocation(returnLocation), company(company)
{

}

char RentalCarReservation::getType()
{
    return 'R';
}
