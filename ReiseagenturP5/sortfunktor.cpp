#include "sortfunktor.h"

SortFunktor::SortFunktor(Modus modus)
    :modus(modus)
{

}

SortFunktor::SortFunktor()
{

}

bool SortFunktor::operator()(std::shared_ptr<Booking>a, std::shared_ptr<Booking> b)
{
    switch (modus) {
    case id:
        return a->getId()<b->getId();
        break;
    case preis:
        return a->getPrice()<b->getPrice();
        break;
    case fromDate:
        return a->getFromDate()<b->getFromDate();
        break;
    case toDate:
        return a->getToDate()<b->getToDate();
        break;
    default:
        return false;
        break;
    }
}

void SortFunktor::setModus(Modus newModus)
{
    modus = newModus;
}
