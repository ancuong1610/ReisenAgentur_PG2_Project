#ifndef BOOKING_H
#define BOOKING_H

#include <sstream>
#include <string>
#include <vector>
class Booking
{
protected:
    int id;
    double price;
    long travelId;
    std::string fromDate,toDate;
    std::vector <long>vorgaengerbuchungen;

public:
    Booking(int id, double price, long travelId, const std::string &fromDate, const std::string &toDate, std::vector<long>vorgaengerId);
    virtual ~Booking();

    virtual char getType()=0;

    int getId() const;
    void setId(int newId);
    double getPrice() const;
    void setPrice(double newPrice);
    long getTravelId() const;
    const std::string &getFromDate() const;
    void setFromDate(const std::string &newFromDate);
    const std::string &getToDate() const;
    void setToDate(const std::string &newToDate);
    const std::vector<long> &getVorgaengerbuchungen() const;
};

#endif // BOOKING_H
