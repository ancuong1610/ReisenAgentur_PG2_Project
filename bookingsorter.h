#ifndef BOOKINGSORTER_H
#define BOOKINGSORTER_H
#include "booking.h"
#include <memory>

class BookingSorter
{
public:
    BookingSorter();
    bool operator()(std::shared_ptr<Booking> a,std::shared_ptr<Booking> b);
};

#endif // BOOKINGSORTER_H
