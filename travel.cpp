#include "travel.h"
#include "digraph.h"
#include "algorithmen.cpp"
#include "flightbooking.h"
#include <algorithm>
#include <iomanip>
#include <map>
#include <QDate>
#include <QString>

long Travel::getId() const
{
    return id;
}

int Travel::getNumberOfBookings()
{
    return travelBookings.size();
}

std::string Travel::getStart()
{
    std::string ausgabe="No Bookings";
    for(size_t i=0; i<travelBookings.size();i++){
        if(i==0)
            ausgabe=travelBookings[i]->getFromDate();
        else{
            if(stoi(ausgabe)>stoi(travelBookings[i]->getFromDate()))
                ausgabe=travelBookings[i]->getFromDate();
        }
    }
    return ausgabe;
}

std::string Travel::getEnd()
{
    std::string ausgabe="No Bookings";
    for(size_t i=0; i<travelBookings.size();i++){
        if(i==0)
            ausgabe=travelBookings[i]->getToDate();
        else{
            if(stoi(ausgabe) < stoi(travelBookings[i]->getToDate()))
                ausgabe=travelBookings[i]->getToDate();
        }
    }

    return ausgabe;
}

long Travel::getBookingId(int index)
{
    return travelBookings[index]->getId();
}

std::string Travel::getBookingStart(int index)
{
    return travelBookings[index]->getFromDate();
}

std::string Travel::getBookingEnd(int index)
{
    return travelBookings[index]->getToDate();
}

double Travel::getBookingPrice(int index)
{
    return travelBookings[index]->getPrice();
}

std::shared_ptr<Booking> Travel::getBooking(long bookingId)
{
    for(auto &booking:travelBookings)
        if(booking->getId()==bookingId)
            return booking;
    return NULL;
}

void Travel::sortBookings(SortFunktor sortFunktor)
{
    std::sort(travelBookings.begin(),travelBookings.end(),sortFunktor);
}

void Travel::topologischSortieren()
{
    //Graph erstellen
    //int n = travelBookings.size();
    std::vector<std::shared_ptr<Booking>>sortedBookings;
    std::map<int, std::shared_ptr<Booking>>sortingmap;
    //int zaehler=1;
    const int n= 150;
    Digraph<std::shared_ptr<Booking>, n>* graph = new Digraph<std::shared_ptr<Booking>, n>;

    for(auto &Buchung:travelBookings){                       //alle Vertexe einfuegen
        graph->insertVertex(findbookingindex(Buchung->getId()), Buchung);
        //        zaehler++;
    }
    for(auto &Buchung:travelBookings)                       //alle Beziehungen einsetzen
        for(size_t i=0;i<Buchung->getVorgaengerbuchungen().size();i++)
            graph->insertArc(findbookingindex(Buchung->getId()),findbookingindex(Buchung->getVorgaengerbuchungen().at(i)));
    TravelDiagramm=graph;

    //TODO Tiefensuche
    DepthFirstSearch(*graph);
    for(size_t i=0;i<travelBookings.size();i++){            //map mit Bearbeitungszeit als key + booking als inhalt -> Bookings in richtige reihenfolge
        int ende=graph->getEnd(findbookingindex(travelBookings[i]->getId()));
        sortingmap.insert(std::pair<int, std::shared_ptr<Booking>>(ende,travelBookings[i]));
    }
    auto iterator= sortingmap.begin();
    for(size_t i = 0;i<sortingmap.size();i++){
        sortedBookings.push_back((*iterator).second);
        iterator++;
    }
    travelBookings=sortedBookings;
}

long Travel::findbookingindex(long id)
{
    for(size_t i=0;i<travelBookings.size();i++)
        if(travelBookings[i]->getId()==id)
            return i;
    return 0;
}

Digraph<std::shared_ptr<Booking>, 150> *Travel::getTravelDiagramm() const
{
    return TravelDiagramm;
}

bool Travel::checkRoundtrip()
{
    std::shared_ptr<FlightBooking>firstFlight, lastFlight;
    firstFlight = std::dynamic_pointer_cast<FlightBooking>(findFirstFlight());
    lastFlight = std::dynamic_pointer_cast<FlightBooking>(findLastFlight());
    if(firstFlight->getFromDest()==lastFlight->getToDest())
        return true;
    return false;
}

std::shared_ptr<Booking> Travel::findFirstFlight()
{
    for(const auto &Buchung:travelBookings)
        if(Buchung->getType()=='F')
            return Buchung;
    return nullptr;
}

std::shared_ptr<Booking> Travel::findLastFlight()
{
    for(size_t i=(travelBookings.size()-1);i>=0;i--)
        if(travelBookings[i]->getType()=='F')
            return travelBookings[i];
    return nullptr;
}

QDate stringToDate(std::string str){
    QString sdatum= QString::fromStdString(str);
    QDate datum = QDate::fromString(sdatum,"yyyyMMdd");
    return datum;
}

bool Travel::checkEnoughHotels()
{
    std::shared_ptr<Booking>a,b;
    std::vector<std::shared_ptr<Booking>>hotelvec=travelBookings;
    for(size_t i=0;i<hotelvec.size();i++){
        if(hotelvec[i]->getType()=='R')
            hotelvec.erase(hotelvec.begin()+i);
    }
    for(size_t i=0;i<hotelvec.size();i++){
        a=hotelvec[i];
        if(i+1 >=hotelvec.size())
            return true;
        b=hotelvec[i+1];
        if(stringToDate(a->getToDate()).daysTo(stringToDate(b->getFromDate()))>0)
            return false;
    }
    return true;
}

bool Travel::checkNoUselessHotels()
{
    if(travelBookings[travelBookings.size()-1]->getType()=='H')
        return false;
    std::shared_ptr<Booking>a,b;
    std::vector<std::shared_ptr<Booking>>hotelvec;
    for(size_t i=0;i<travelBookings.size();i++){
        if(travelBookings[i]->getType()=='H'||travelBookings[i]->getType()=='F'){
            hotelvec.push_back(travelBookings[i]);
        }
    }
    for(size_t i=0;i<hotelvec.size();i++){
        a=hotelvec[i];
        if(i+1 >=hotelvec.size())
            return true;
        b=hotelvec[i+1];
        if(stringToDate(a->getToDate()).daysTo(stringToDate(b->getFromDate()))<0)
            return false;
    }
    return true;
}

bool Travel::checkNoUselessRentalCars()
{
    if(travelBookings[travelBookings.size()-1]->getType()=='R')
        return false;
    std::shared_ptr<Booking>a,b;
    std::vector<std::shared_ptr<Booking>>carvec;
    for(size_t i=0;i<travelBookings.size();i++){
        if(travelBookings[i]->getType()=='R'||travelBookings[i]->getType()=='F'){
            carvec.push_back(travelBookings[i]);
        }
    }
    for(size_t i=0;i<carvec.size();i++){
        a=carvec[i];
        if(i+1 >=carvec.size())
            return true;
        b=carvec[i+1];
        if(stringToDate(a->getToDate()).daysTo(stringToDate(b->getFromDate()))<0)
            return false;
    }
    return true;
}

Travel::Travel(long id, long customerid)
    :id(id),customerid(customerid)
{

}

void Travel::addBooking(std::shared_ptr<Booking> p_booking)
{
    travelBookings.push_back(p_booking);
}
