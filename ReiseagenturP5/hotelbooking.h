#ifndef HOTELBOOKING_H
#define HOTELBOOKING_H


#include "booking.h"
class HotelBooking: public Booking
{
    std::string hotel, town;
public:
    HotelBooking(int id, double price, long travelId, const std::string &fromDate, const std::string &toDate, std::vector<long>vorgaengerId,
                     const std::string &hotel, const std::string &town);

        virtual char getType()override;

    const std::string &getHotel() const;
    void setHotel(const std::string &newHotel);
    const std::string &getTown() const;
    void setTown(const std::string &newTown);
};

#endif // HOTELBOOKING_H
