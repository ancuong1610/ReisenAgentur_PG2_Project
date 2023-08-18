#ifndef SORTFUNKTOR_H
#define SORTFUNKTOR_H



#include "booking.h"
#include <memory>
class SortFunktor
{
public:
    enum Modus { id, preis, fromDate, toDate};
    SortFunktor(Modus modus);
    SortFunktor();
    bool operator()(std::shared_ptr<Booking> a,std::shared_ptr<Booking> b);
    void setModus(Modus newModus);
private:
    Modus modus;
};

#endif // SORTFUNKTOR_H
