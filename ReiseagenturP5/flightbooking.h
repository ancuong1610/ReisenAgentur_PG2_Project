#ifndef FLIGHTBOOKING_H
#define FLIGHTBOOKING_H
#include "booking.h"

class FlightBooking:public Booking
{
    std::string fromDest, toDest, airline;
public:
    FlightBooking(long id, double price, long travelId, const std::string &fromDate, const std::string &toDate, std::vector<long>vorgaengerId,
                  const std::string &fromDest,const std::string &toDest,const std::string &airline);

    virtual char getType()override;


    const std::string &getFromDest() const;
    void setFromDest(const std::string &newFromDest);
    const std::string &getToDest() const;
    void setToDest(const std::string &newToDest);
    const std::string &getAirline() const;
    void setAirline(const std::string &newAirline);
};

#endif // FLIGHTBOOKING_H
