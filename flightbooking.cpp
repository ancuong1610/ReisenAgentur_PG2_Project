#include "flightbooking.h"

#include <sstream>

const std::string &FlightBooking::getFromDest() const
{
    return fromDest;
}

void FlightBooking::setFromDest(const std::string &newFromDest)
{
    fromDest = newFromDest;
}

const std::string &FlightBooking::getToDest() const
{
    return toDest;
}

void FlightBooking::setToDest(const std::string &newToDest)
{
    toDest = newToDest;
}

const std::string &FlightBooking::getAirline() const
{
    return airline;
}

void FlightBooking::setAirline(const std::string &newAirline)
{
    airline = newAirline;
}

FlightBooking::FlightBooking(long id, double price, long travelId, const std::string &fromDate, const std::string &toDate, std::vector<long> vorgaengerId,
                             const std::string &fromDest, const std::string &toDest, const std::string &airline)
    :Booking(id,price,travelId,fromDate, toDate, vorgaengerId),
      fromDest(fromDest), toDest(toDest), airline(airline)
{
}

char FlightBooking::getType()
{
    return 'F';
}
