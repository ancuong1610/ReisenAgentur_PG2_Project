#include "bookingsorter.h"


BookingSorter::BookingSorter()
{

}

bool BookingSorter::operator()(std::shared_ptr<Booking> a, std::shared_ptr<Booking> b)
{
    return true;
}
