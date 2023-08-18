#include "hotelbooking.h"

#include <sstream>
const std::string &HotelBooking::getHotel() const
{
    return hotel;
}

void HotelBooking::setHotel(const std::string &newHotel)
{
    hotel = newHotel;
}

const std::string &HotelBooking::getTown() const
{
    return town;
}

void HotelBooking::setTown(const std::string &newTown)
{
    town = newTown;
}

HotelBooking::HotelBooking(int id, double price, long travelId, const std::string &fromDate, const std::string &toDate, std::vector<long> vorgaengerId,
                           const std::string &hotel, const std::string &town)
    :Booking(id, price, travelId, fromDate, toDate, vorgaengerId),hotel(hotel), town(town)
{
}

char HotelBooking::getType()
{
    return 'H';
}
