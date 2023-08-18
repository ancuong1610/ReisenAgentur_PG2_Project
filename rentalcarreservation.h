#ifndef RENTALCARRESERVATION_H
#define RENTALCARRESERVATION_H

#include "booking.h"
class RentalCarReservation: public Booking
{
    std::string pickupLocation, returnLocation, company;
public:
    RentalCarReservation(int id, double price, long travelId, const std::string &fromDate, const std::string &toDate, std::vector<long>vorgaengerId,
                            const std::string &pickupLocation,const std::string returnLocation, const std::string &company);

       virtual char getType()override;

    const std::string &getPickupLocation() const;
    void setPickupLocation(const std::string &newPickupLocation);
    const std::string &getReturnLocation() const;
    void setReturnLocation(const std::string &newReturnLocation);
    const std::string &getCompany() const;
    void setCompany(const std::string &newCompany);
};

#endif // RENTALCARRESERVATION_H
