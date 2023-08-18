#include "booking.h"

int Booking::getId() const
{
    return id;
}

void Booking::setId(int newId)
{
    id = newId;
}

double Booking::getPrice() const
{
    return price;
}

void Booking::setPrice(double newPrice)
{
    price = newPrice;
}

long Booking::getTravelId() const
{
    return travelId;
}

const std::string &Booking::getFromDate() const
{
    return fromDate;
}

void Booking::setFromDate(const std::string &newFromDate)
{
    fromDate = newFromDate;
}

const std::string &Booking::getToDate() const
{
    return toDate;
}

void Booking::setToDate(const std::string &newToDate)
{
    toDate = newToDate;
}

const std::vector<long> &Booking::getVorgaengerbuchungen() const
{
    return vorgaengerbuchungen;
}

Booking::Booking(int id, double price, long travelId, const std::string &fromDate, const std::string &toDate, std::vector<long> vorgaengerId) : id(id),
    price(price),
    travelId(travelId),
    fromDate(fromDate),
    toDate(toDate),
    vorgaengerbuchungen(vorgaengerId)
{}

Booking::~Booking()
{

}
