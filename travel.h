#ifndef TRAVEL_H
#define TRAVEL_H
#include "digraph.h"
#include "booking.h"
#include "sortfunktor.h"
#include <memory>
#include <vector>
class Travel
{
    long id, customerid;
    std::vector<std::shared_ptr<Booking>>travelBookings;
    //Digraph<std::shared_ptr<Booking>, 20 > TravelDiagramm;
    Digraph<std::shared_ptr<Booking>,150>* TravelDiagramm;
public:
    Travel(long id, long customerid);

    void addBooking(std::shared_ptr<Booking>p_booking);
    long getId() const;

    int getNumberOfBookings();
    std::string getStart();
    std::string getEnd();

    //print bookings functions
    long getBookingId(int index);
    std::string getBookingStart(int index);
    std::string getBookingEnd(int index);
    double getBookingPrice(int index);

    //save booking in kundenprofil
    std::shared_ptr<Booking> getBooking(long bookingId);

    //sortierungen
    void sortBookings(SortFunktor sortFunktor);//fuer Sort-Fenster bei kundenprofil (freiwillig)
    void topologischSortieren();
    long findbookingindex(long id);
    Digraph<std::shared_ptr<Booking>, 150> *getTravelDiagramm() const;

    //checks
    bool checkRoundtrip();
    std::shared_ptr<Booking> findFirstFlight();
    std::shared_ptr<Booking> findLastFlight();
    bool checkEnoughHotels();
    bool checkNoUselessHotels();
    bool checkNoUselessRentalCars();
};

#endif // TRAVEL_H
