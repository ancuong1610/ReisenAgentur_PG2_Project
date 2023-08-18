#include "kundenprofil.h"
#include "flightbooking.h"
#include "rentalcarreservation.h"
#include "hotelbooking.h"
#include "tableitem.h"
#include "ui_kundenprofil.h"
#include "sortfunktor.h"

#include "travelagency.h"

#include <QDate>
#include <QMessageBox>
#include <QString>
#include <sstream>
KundenProfil::KundenProfil(std::shared_ptr<Customer>customer,std::shared_ptr<TravelAgency>travelAgency,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KundenProfil),
    p_customer(customer),
    p_travelAgency(travelAgency)
{
    ui->setupUi(this);
    ui->tableWidgetBooking->hide();
    ui->TabWidget->hide();
    ui->labelTravelId->hide();
    ui->lineEditTravelId->hide();
    ui->pushButtonSpeichern->hide();

    ui->radioButtonId->hide();
    ui->radioButtonPrice->hide();
    ui->radioButtonFromDate->hide();
    ui->radioButtontoDate->hide();
    ui->pushButtonSort->hide();


    std::ostringstream ss1;
    ss1<<p_customer->getId();
    ui->lineEditId->setText(QString::fromStdString(ss1.str()));
    ui->lineEditName->setText(QString::fromStdString( p_customer->getName()));
    printTravels();
}

KundenProfil::~KundenProfil()
{
    delete ui;
}

void KundenProfil::printTravels()
{
    ui->tableWidgetTravel->setHorizontalHeaderLabels(QStringList() << "Id" << "Startdatum"<<"Enddatum"<<"Reisedauer[Tage]");
    ui->tableWidgetTravel->setRowCount(p_customer->getNumberOfTravels());

    QDate VonDatum, BisDatum;
    QString sVonDatum, sBisDatum;


    for(int zeile=0;zeile<p_customer->getNumberOfTravels();zeile++){
        std::ostringstream ss2;
        long Travelid=p_customer->getTravelId(zeile);
        ss2<<Travelid;

        sVonDatum=QString::fromStdString( p_customer->getTravelStart(Travelid));
        sBisDatum=QString::fromStdString( p_customer->getTravelEnd(Travelid));
        VonDatum=QDate::fromString(sVonDatum,"yyyyMMdd");
        BisDatum=QDate::fromString(sBisDatum,"yyyyMMdd");

        ui->tableWidgetTravel->setItem(zeile, 0, new TableItem(QString::fromStdString(ss2.str())));
        ui->tableWidgetTravel->setItem(zeile, 1, new TableItem(VonDatum.toString("dd.MM.yyyy")));
        ui->tableWidgetTravel->setItem(zeile, 2, new TableItem(BisDatum.toString("dd.MM.yyyy")));
        ui->tableWidgetTravel->setItem(zeile, 3, new TableItem(QString::number(VonDatum.daysTo(BisDatum))));
    }
}

void KundenProfil::printBookings()
{
    ui->tableWidgetBooking->setHorizontalHeaderLabels(QStringList() << "Id" << "Startdatum"<<"Enddatum"<<"Preis [EUR]");
    ui->tableWidgetBooking->setRowCount(p_currentTravel->getNumberOfBookings());
    QDate VonDatum, BisDatum;
    QString sVonDatum, sBisDatum;

    //p_currentTravel->topologischSortieren<class TV,20>();
    //p_currentTravel->topologischSortieren<class TV,20>();
    p_currentTravel->topologischSortieren();

    for(int zeile=0;zeile< p_currentTravel->getNumberOfBookings();zeile++){

        sVonDatum=QString::fromStdString( p_currentTravel->getBookingStart(zeile));
        sBisDatum=QString::fromStdString( p_currentTravel->getBookingEnd(zeile));
        VonDatum=QDate::fromString(sVonDatum,"yyyyMMdd");
        BisDatum=QDate::fromString(sBisDatum,"yyyyMMdd");

        std::ostringstream ss1,ss2;
        ss1<<p_currentTravel->getBookingId(zeile);
        ss2<<p_currentTravel->getBookingPrice(zeile);

        ui->tableWidgetBooking->setItem(zeile,0,new TableItem(QString::fromStdString(ss1.str())));
        ui->tableWidgetBooking->setItem(zeile,1,new TableItem(VonDatum.toString("dd.MM.yyyy")));
        ui->tableWidgetBooking->setItem(zeile,2,new TableItem(BisDatum.toString("dd.MM.yyyy")));
        ui->tableWidgetBooking->setItem(zeile,3,new TableItem(QString::fromStdString(ss2.str())/*+"EUR"*/));
    }
}

void KundenProfil::printDetails()
{
    QDate VonDatum, BisDatum;
    QString sVonDatum, sBisDatum;
    sVonDatum=QString::fromStdString(p_currentBooking->getFromDate());
    sBisDatum=QString::fromStdString(p_currentBooking->getToDate());
    VonDatum=QDate::fromString(sVonDatum,"yyyyMMdd");
    BisDatum=QDate::fromString(sBisDatum,"yyyyMMdd");

    std::shared_ptr<FlightBooking>flight;
    std::shared_ptr<RentalCarReservation>car;
    std::shared_ptr<HotelBooking>hotel;


    switch (p_currentBooking->getType()){
    case 'F':
        flight = std::dynamic_pointer_cast<FlightBooking>(p_currentBooking);

        ui->TabWidget->setTabVisible(0,true);
        ui->TabWidget->setTabVisible(1,false);
        ui->TabWidget->setTabVisible(2,false);

        ui->spinBoxFlugId->setValue(flight->getId());
        ui->doubleSpinBoxFlugPreis->setValue(flight->getPrice());
        ui->dateEditFlugFrom->setDate(VonDatum);
        ui->dateEditFlugTo->setDate(BisDatum);
        ui->lineEditFlugFrom->setText(QString::fromStdString(flight->getFromDest()));
        ui->lineEditFlugTo->setText(QString::fromStdString(flight->getToDest()));
        ui->lineEditFlugAirline->setText(QString::fromStdString(flight->getAirline()));


        if(p_travelAgency->findIataCode(flight->getFromDest())=="ERROR"){
            ui->lineEditFlugFromStadtError->show();
            ui->lineEditFlugFromStadt->hide();
            ui->lineEditFlugFromStadtError->setText("Ungültiger Iata-Code");
        }else{
            ui->lineEditFlugFromStadtError->hide();
            ui->lineEditFlugFromStadt->show();
            ui->lineEditFlugFromStadt->setText(QString::fromStdString(p_travelAgency->findIataCode(flight->getFromDest())));
        }
        if(p_travelAgency->findIataCode(flight->getToDest())=="ERROR"){
            ui->lineEditFlugToStadtError->show();
            ui->lineEditFlugToStadt->hide();
            ui->lineEditFlugToStadtError->setText("Ungültiger Iata-Code");
        }else{
            ui->lineEditFlugToStadtError->hide();
            ui->lineEditFlugToStadt->show();
            ui->lineEditFlugToStadt->setText(QString::fromStdString(p_travelAgency->findIataCode(flight->getToDest())));
        }
        break;
    case 'R':
        car = std::dynamic_pointer_cast<RentalCarReservation>(p_currentBooking);

        ui->TabWidget->setTabVisible(0,false);
        ui->TabWidget->setTabVisible(1,true);
        ui->TabWidget->setTabVisible(2,false);

        ui->spinBoxAutoId->setValue(car->getId());
        ui->doubleSpinBoxAutoPreis->setValue(car->getPrice());
        ui->dateEditAutoFrom->setDate(VonDatum);
        ui->dateEditAutoTo->setDate(BisDatum);
        ui->lineEditAutoPickup->setText(QString::fromStdString(car->getPickupLocation()));
        ui->lineEditAutoReturn->setText(QString::fromStdString(car->getReturnLocation()));
        ui->lineEditAutoCompany->setText(QString::fromStdString(car->getCompany()));
        break;
    case 'H':
        hotel = std::dynamic_pointer_cast<HotelBooking>(p_currentBooking);

        ui->TabWidget->setTabVisible(0,false);
        ui->TabWidget->setTabVisible(1,false);
        ui->TabWidget->setTabVisible(2,true);

        ui->spinBoxHotelId->setValue(hotel->getId());
        ui->doubleSpinBoxHotelPreis->setValue(hotel->getPrice());
        ui->dateEditHotelFrom->setDate(VonDatum);
        ui->dateEditHotelTo->setDate(BisDatum);
        ui->lineEditHotelName->setText(QString::fromStdString(hotel->getHotel()));
        ui->lineEditHotelTown->setText(QString::fromStdString(hotel->getTown()));
        break;
    default:
        break;
    }
}


void KundenProfil::on_tableWidgetTravel_cellDoubleClicked(int row)
{
    ui->lineEditTravelId->show();
    ui->labelTravelId->show();
    ui->tableWidgetBooking->show();

    ui->radioButtonId->show();
    ui->radioButtonPrice->show();
    ui->radioButtonFromDate->show();
    ui->radioButtontoDate->show();
    ui->pushButtonSort->show();

    QTableWidgetItem* IdItem = ui->tableWidgetTravel->item(row, 0);
    long travelId= IdItem->text().toLong();
    p_currentTravel= p_customer->getTravel(travelId);
    std::ostringstream ss1;
    ss1<<p_currentTravel->getId();
    ui->lineEditTravelId->setText(QString::fromStdString(ss1.str()));

    printBookings();
}

void KundenProfil::on_tableWidgetBooking_cellDoubleClicked(int row)
{
    ui->TabWidget->show();
    ui->pushButtonSpeichern->show();

    QTableWidgetItem* IdItem= ui->tableWidgetBooking->item(row,0);
    long bookingId = IdItem->text().toLong();
    p_currentBooking= p_currentTravel->getBooking(bookingId);

    printDetails();
}


void KundenProfil::on_pushButtonSpeichern_clicked()
{
    std::shared_ptr<FlightBooking>flight;
    std::shared_ptr<RentalCarReservation>car;
    std::shared_ptr<HotelBooking>hotel;

    switch (p_currentBooking->getType()) {
    case 'F':
        flight = std::dynamic_pointer_cast<FlightBooking>(p_currentBooking);

        flight->setId(ui->spinBoxFlugId->value());
        flight->setPrice(ui->doubleSpinBoxFlugPreis->value());
        flight->setFromDate(ui->dateEditFlugFrom->date().toString("yyyyMMdd").toStdString());
        flight->setToDate(ui->dateEditFlugTo->date().toString("yyyyMMdd").toStdString());

        flight->setFromDest(ui->lineEditFlugFrom->text().toStdString());
        flight->setToDest(ui->lineEditFlugTo->text().toStdString());
        flight->setAirline(ui->lineEditFlugAirline->text().toStdString());
        break;
    case 'R':
        car = std::dynamic_pointer_cast<RentalCarReservation>(p_currentBooking);

        car->setId(ui->spinBoxAutoId->value());
        car->setPrice(ui->doubleSpinBoxAutoPreis->value());
        car->setFromDate(ui->dateEditAutoFrom->date().toString("yyyyMMdd").toStdString());
        car->setToDate(ui->dateEditAutoTo->date().toString("yyyyMMdd").toStdString());

        car->setPickupLocation(ui->lineEditAutoPickup->text().toStdString());
        car->setReturnLocation(ui->lineEditAutoReturn->text().toStdString());
        car->setCompany(ui->lineEditAutoCompany->text().toStdString());
        break;
    case 'H':
        hotel = std::dynamic_pointer_cast<HotelBooking>(p_currentBooking);

        hotel->setId(ui->spinBoxHotelId->value());
        hotel->setPrice(ui->doubleSpinBoxHotelPreis->value());
        hotel->setFromDate(ui->dateEditHotelFrom->date().toString("yyyyMMdd").toStdString());
        hotel->setToDate(ui->dateEditHotelTo->date().toString("yyyyMMdd").toStdString());

        hotel->setHotel(ui->lineEditHotelName->text().toStdString());
        hotel->setTown(ui->lineEditHotelTown->text().toStdString());
        break;
    }

    printTravels();
    printBookings();
    printDetails();

    QMessageBox::information(
                this,
                tr("Gespeichert"),
                tr("Änderungen wurden gespeichert!"));
}


void KundenProfil::on_pushButtonSort_clicked()
{
    if(ui->radioButtonId->isChecked()){
        SortFunktor sortFunktor(SortFunktor::id);
        //p_customer->sortTravels(sortFunktor);
        p_currentTravel->sortBookings(sortFunktor);
    }else if(ui->radioButtonPrice->isChecked()){
        SortFunktor sortFunktor(SortFunktor::preis);
        //p_customer->sortTravels(sortFunktor);
        p_currentTravel->sortBookings(sortFunktor);
    }else if(ui->radioButtonFromDate->isChecked()){
        SortFunktor sortFunktor(SortFunktor::fromDate);
        //p_customer->sortTravels(sortFunktor);
        p_currentTravel->sortBookings(sortFunktor);
    }else if (ui->radioButtontoDate->isChecked()) {
        SortFunktor sortFunktor(SortFunktor::toDate);
        //p_customer->sortTravels(sortFunktor);
        p_currentTravel->sortBookings(sortFunktor);
    }else{
        QMessageBox::warning(
                    this,
                    tr("Warnung"),
                    tr("Wählen sie aus, nach was sortiert werden soll!"));
    }
    printTravels();
    printBookings();
}
