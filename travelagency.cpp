#include "travelagency.h"
#include "flightbooking.h"
#include "hotelbooking.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include "rentalcarreservation.h"

#include <QFile>
#include <QString>
#include <iostream>

const std::vector<std::shared_ptr<Travel> > &TravelAgency::getAllTravels() const
{
    return allTravels;
}

TravelAgency::TravelAgency()
{

}

void TravelAgency::readFile(QString Dateiname)
{
    std::shared_ptr<Booking>p_booking;
    std::shared_ptr<Customer>p_customer;
    std::shared_ptr<Travel>p_travel;

    QFile datei(Dateiname);
    if (!datei.open(QIODevice::ReadOnly))
        throw std::logic_error("Datei konnte nicht geoeffnet werden");
    QString dateiInhalt = datei.readAll();
    datei.close();
    QStringList zeilen = dateiInhalt.split("\r\n");
    int zeilenzaehler=0;

    for(auto &zeile:zeilen){
        zeilenzaehler++;
        QStringList attribute = zeile.split("|");
        std::string fromDate, toDate, pickuplocation, returnlocation, company, hotel, town,fromDest, toDest, airline, customername;
        std::vector<long>abhaengigkeiten;
        long bookingId, travelId, customerId;
        double preis;
        QChar buchungstyp;

        std::string stringpreis=attribute[2].toStdString();
        for(size_t j=0;j<stringpreis.size();j++)
            if (!isdigit(stringpreis[j])&&stringpreis[j]!='.')
                throw std::runtime_error("Der Preis ist keine Nummer in der "+ std::to_string(zeilenzaehler) +"ten Zeile!");


        buchungstyp= attribute[0].at(0);
        bookingId=   attribute[1].toLong();
        preis=       attribute[2].toDouble();
        fromDate=    attribute[3].toStdString();
        toDate=      attribute[4].toStdString();
        travelId=    attribute[5].toLong();
        customerId=  attribute[6].toLong();
        customername=attribute[7].toStdString();


        p_customer=findCustomer(customerId);
        if(p_customer==NULL){
            p_customer.reset(new Customer(customerId,customername));
            allCustomers.push_back(p_customer);
            KundenName.push_back(customername);
        }

        p_travel=findTravel(travelId);
        if(p_travel==NULL){
            p_travel.reset(new Travel(travelId,customerId));
            allTravels.push_back(p_travel);
            p_customer->addTravel(p_travel);
        }

        p_booking =findBooking(bookingId);
        switch (buchungstyp.toLatin1()) {
        case 'F':

            fromDest=   attribute[8].toStdString();
            toDest=     attribute[9].toStdString();
            airline=    attribute[10].toStdString();

            if((fromDest.size()!=3) || (toDest.size()!=3))
                throw std::runtime_error("Ungueltiges Flughafenkuerzel in Zeile "+ std::to_string(zeilenzaehler) +"!");

            for(int i=0;i<(attribute.size()-11);i++)
                abhaengigkeiten.push_back(attribute[11+i].toLong());

            if(p_booking==NULL){
                p_booking.reset(new FlightBooking(bookingId, preis,travelId, fromDate,toDate,abhaengigkeiten,fromDest,toDest,airline));
                allBookings.push_back(p_booking);
                p_travel->addBooking(p_booking);
            }
            break;
        case 'R':

            pickuplocation= attribute[8].toStdString();
            returnlocation= attribute[9].toStdString();
            company=        attribute[10].toStdString();

            for(int i=0;i<(attribute.size()-11);i++)
                abhaengigkeiten.push_back(attribute[11+i].toLong());

            if(p_booking==NULL){
                p_booking.reset(new RentalCarReservation(bookingId, preis,travelId, fromDate,toDate,abhaengigkeiten,pickuplocation,returnlocation,company));
                allBookings.push_back(p_booking);
                p_travel->addBooking(p_booking);
            }
            break;
        case 'H':

            hotel=  attribute[8].toStdString();
            town=   attribute[9].toStdString();

            for(int i=0;i<(attribute.size()-10);i++)
                abhaengigkeiten.push_back(attribute[10+i].toLong());

            if(p_booking==NULL){
                p_booking.reset(new HotelBooking(bookingId, preis,travelId, fromDate,toDate,abhaengigkeiten,hotel,town));
                allBookings.push_back(p_booking);
                p_travel->addBooking(p_booking);
            }
            break;
        default:
            throw std::runtime_error("Ungueltiger buchungstyp in der "+ std::to_string(zeilenzaehler) +"ten Zeile!");
            break;

        }

    }
    for(const auto &Reise:allTravels){
        Reise->topologischSortieren();
    }

}

void TravelAgency::readJsonFile(QString Dateiname)
{
    QFile file(Dateiname);
    if(!file.open(QIODevice::ReadWrite))    qDebug() <<"File open error";
    else                                    qDebug() <<"JSON File open!";
    QString val = file.readAll();
    file.close();
    auto json_doc = QJsonDocument::fromJson(val.toUtf8());
    QJsonArray jArr = json_doc.array();

    QJsonValue airport;
    QString nameValue,isoValue,muniValue,iataValue;
    for (auto tmpAirport : jArr){
        airport = tmpAirport.toObject().value("name");
        nameValue = airport.toString();

        airport = tmpAirport.toObject().value("iso_country");
        isoValue = airport.toString();

        airport = tmpAirport.toObject().value("municipality");
        muniValue = airport.toString();

        airport = tmpAirport.toObject().value("iata_code");
        iataValue = airport.toString();

        Airport tmp = {nameValue.toStdString(),isoValue.toStdString(),muniValue.toStdString(),iataValue.toStdString()};
        Flughafen[iataValue.toStdString()] = tmp;
    }
}

std::shared_ptr<Booking> TravelAgency::findBooking(long id)
{
    for(auto &booking:allBookings)
        if(booking->getId()==id)
            return booking;
    return NULL;
}

std::shared_ptr<Customer> TravelAgency::findCustomer(long id)
{
    for(auto &customer:allCustomers)
        if(customer->getId()==id)
            return customer;
    return NULL;
}

std::shared_ptr<Travel> TravelAgency::findTravel(long id)
{
    for(auto &travel:allTravels)
        if(travel->getId()==id)
            return travel;
    return NULL;
}

std::string TravelAgency::getSummary()
{
    std::string ausgabe;
    std::stringstream ss1,ss2,ss3,ss4,ss5,ss6,ss7,ss8,ss9,ss10,ss11,ss12;
    ss1<<allBookings.size();
    std::string anzahlBuchungen = ss1.str();
    int anzahlFluege=0, anzahlAutos=0,anzahlHotels=0;
    double gesamtBuchungsPreis=0, FluegePreis=0,AutoPreis=0, HotelPreis=0;
    for(auto &buchung:allBookings){
        gesamtBuchungsPreis+=buchung->getPrice();
        if(buchung->getType()=='F'){
            anzahlFluege++;
            FluegePreis+=buchung->getPrice();
        }
        else if(buchung->getType()=='R'){
            anzahlAutos++;
            AutoPreis+=buchung->getPrice();
        }
        else if(buchung->getType()=='H'){
            anzahlHotels++;
            HotelPreis+=buchung->getPrice();
        }
    }
    ss7<<gesamtBuchungsPreis;
    ausgabe= "Es wurden insgesamt [" +anzahlBuchungen + "] Buchungen eingelesen (Gesamtwert: "+ss7.str() +"EUR). Davon sind:\n";
    ss8<<FluegePreis;
    ss2<<anzahlFluege;
    anzahlBuchungen=ss2.str();
    ausgabe+="\t"+anzahlBuchungen+" Flugbuchungen ("+ss8.str() +"EUR)\n";
    ss9<<AutoPreis;
    ss3<<anzahlAutos;
    anzahlBuchungen=ss3.str();
    ausgabe+="\t"+anzahlBuchungen+" AutoBuchungen ("+ss9.str() +"EUR)\n";
    ss10<<HotelPreis;
    ss4<<anzahlHotels;
    anzahlBuchungen=ss4.str();
    ausgabe+="\t"+anzahlBuchungen+" Hotelbuchungen ("+ss10.str() +"EUR)\n\n";

    ss5<<allCustomers.size();
    std::string AnzahlKunden=ss5.str();
    ausgabe+= "Es wurden insgesamt [" +AnzahlKunden + "] Kunden eingelesen.\n\n";

    ss6<<allTravels.size();
    std::string AnzahlReisen=ss6.str();
    ausgabe+= "Es wurden insgesamt [" +AnzahlReisen+ "] Reisen eingelesen.\n\n";

    int AnzahlBuchungenBeiKunde1=0;
    ausgabe+="Der Kunde mit der Id: 1 hat ";
    for(size_t i=0;i<allCustomers.size();i++)
        if(allCustomers[i]->getId()==1)
            AnzahlBuchungenBeiKunde1=allCustomers[i]->getNumberOfTravels();
    ss11<<AnzahlBuchungenBeiKunde1;
    ausgabe+= ss11.str()+" Reisen gebucht\n\n";

    int AnzahlBuchungenReise17=0;
    for(size_t i=0;i<allTravels.size();i++)
        if(allTravels[i]->getId()==17)
            AnzahlBuchungenReise17=allTravels[i]->getNumberOfBookings();
    ss12<<AnzahlBuchungenReise17;
    ausgabe+= "Die Reise mit der Id: 17 wurde "+ss12.str()+" mal gebucht\n\n";
    return ausgabe;
}

int TravelAgency::getNumberOfCustomers()
{
    return allCustomers.size();
}

long TravelAgency::getCustomerId(int index)
{
    return allCustomers[index]->getId();
}

std::string TravelAgency::getCustomerName(int index)
{
    return allCustomers[index]->getName();
}

std::string TravelAgency::findIataCode(std::string code)
{
    for (const auto& i : Flughafen)
        if(i.first==code)
            return i.second.name;
    return "ERROR";
}

void TravelAgency::saveToJSON(SortFunktor sortierer)
{
    std::shared_ptr<FlightBooking>flight;
    std::shared_ptr<RentalCarReservation>car;
    std::shared_ptr<HotelBooking>hotel;

    std::sort(allBookings.begin(),allBookings.end(),sortierer);

    QJsonDocument doc;
    QJsonArray jsonBookings;
    for(auto &booking:allBookings){
        QJsonObject jsonObjectBooking;
        jsonObjectBooking["Id"] =       booking->getId();
        jsonObjectBooking["Price"] =    booking->getPrice();
        jsonObjectBooking["FromDate"] = QString::fromStdString(booking->getFromDate());
        jsonObjectBooking["ToDate"] =   QString::fromStdString(booking->getToDate());

        switch (booking->getType()) {
        case 'F':
            flight = std::dynamic_pointer_cast<FlightBooking>(booking);
            jsonObjectBooking["FromDest"] =  QString::fromStdString(flight->getFromDest());
            jsonObjectBooking["ToDest"] =    QString::fromStdString(flight->getToDest());
            jsonObjectBooking["Airline"] =   QString::fromStdString(flight->getAirline());
            break;
        case 'R':
            car = std::dynamic_pointer_cast<RentalCarReservation>(booking);
            jsonObjectBooking["PickupLocation"] =   QString::fromStdString(car->getPickupLocation());
            jsonObjectBooking["ReturnLocation"]=    QString::fromStdString(car->getReturnLocation());
            jsonObjectBooking["Company"]=           QString::fromStdString(car->getCompany());
            break;
        case 'H':
            hotel = std::dynamic_pointer_cast<HotelBooking>(booking);
            jsonObjectBooking["Hotel"] =    QString::fromStdString(hotel->getHotel());
            jsonObjectBooking["Town"] =     QString::fromStdString(hotel->getTown());
            break;
        }
        jsonBookings.push_back(jsonObjectBooking);
    }
    doc.setArray(jsonBookings);
    QString filename = "/Users/faze/Downloads/PG2 file/Prak/5/AllBookings.json";
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly))
        std::cerr << "Datei konnte nicht geoeffnet werden";
    file.write(doc.toJson());
    file.close();

}

std::shared_ptr<Customer> TravelAgency::returnKunde(std::string name){
    for(auto &kunde:allCustomers){
        int res = kunde->getName().compare(name);
        if(res == 0)
            return kunde;
    }
    return NULL;
}

void TravelAgency::addKunden(string name)
{
    std::shared_ptr<Customer> Kunde= std::shared_ptr<Customer>(new Customer(returnKundenID(),name));
    allCustomers.push_back(Kunde);
}

void TravelAgency::addBuchung(long id, char type)
{
    long tmp = returnReiseID();
    std::shared_ptr<Travel> Reise = std::shared_ptr<Travel>(new Travel(tmp,id));
    allTravels.push_back(Reise);
    findCustomer(id)->addTravel(Reise);
    std::vector<long> empty;
    std::shared_ptr<Booking> Buchung;
    switch(type){
    case 'F':{
        Buchung = std::shared_ptr<FlightBooking>(new FlightBooking(returnBuchungID(),0, tmp, "00000000", "00000000",empty, "NON", "NON", "none"));
        break;
    }
    case 'H':{
        Buchung = std::shared_ptr<HotelBooking>(new HotelBooking(returnBuchungID(),0, tmp, "00000000", "00000000",empty, "none", "none"));
        break;
    }
    case 'C':{
        Buchung = std::shared_ptr<RentalCarReservation>(new RentalCarReservation(returnBuchungID(),0, tmp, "00000000", "00000000",empty, "none", "none", "none" ));
        break;
    }
    }
    allBookings.push_back(Buchung);
    findTravel(tmp)->addBooking(Buchung);
}

long TravelAgency::returnKundenID(){
    for(auto &customer : allCustomers){
        KundenIDList.push_back(customer->getId());
    }
    sort(KundenIDList.begin(), KundenIDList.end());
    return KundenIDList.back() += 1;
}

long TravelAgency::returnReiseID(){
    for(auto &travel :allTravels){
        TravelIDList.push_back(travel->getId());
    }
    sort(TravelIDList.begin(), TravelIDList.end());
    return TravelIDList.back() += 1;
}

long TravelAgency::returnBuchungID(){
    for(auto &booking :allBookings){
        BookingIDList.push_back(booking->getId());
    }
    sort(BookingIDList.begin(), BookingIDList.end());
    return BookingIDList.back() += 1;
}
