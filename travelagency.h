#ifndef TRAVELAGENCY_H
#define TRAVELAGENCY_H
#include "booking.h"
#include "customer.h"
#include "travel.h"
#include <QString>
#include <map>

class TravelAgency
{
    std::vector <std::shared_ptr<Booking>>allBookings;
    std::vector <std::shared_ptr<Customer>>allCustomers;
    std::vector <std::shared_ptr<Travel>>allTravels;
    std::vector <long>KundenIDList;
    std::vector <long>TravelIDList;
    std::vector <long>BookingIDList;
public:
    struct Airport{
        std::string name;
        std::string iso_country;
        std::string municipality;
        std::string iata_code;
    };
    std::map<std::string, Airport> Flughafen;

    std::vector<std::string> KundenName;
    TravelAgency();
    void readFile(QString Dateiname);
    void readJsonFile(QString Dateiname);
    std::shared_ptr<Booking> findBooking(long id);
    std::shared_ptr<Customer> findCustomer(long id);
    std::shared_ptr<Travel> findTravel(long id);
    std::string getSummary();

    int getNumberOfCustomers();
    long getCustomerId(int index);
    std::string getCustomerName(int index);

    std::string findIataCode(std::string code);

    void saveToJSON(SortFunktor sortierer);
    const std::vector<std::shared_ptr<Travel> > &getAllTravels() const;

    std::shared_ptr<Customer> returnKunde(std::string name);

    void addKunden(std::string name);
    void addBuchung(long id, char type);
    long returnKundenID();
    long returnReiseID();
    long returnBuchungID();
};

#endif // TRAVELAGENCY_H
