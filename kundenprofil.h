#ifndef KUNDENPROFIL_H
#define KUNDENPROFIL_H

#include "customer.h"
#include "travelagency.h"
#include <QDialog>

namespace Ui {
class KundenProfil;
}

class KundenProfil : public QDialog
{
    Q_OBJECT

public:
    explicit KundenProfil(std::shared_ptr<Customer>customer,std::shared_ptr<TravelAgency>travelAgency, QWidget *parent = nullptr);
    ~KundenProfil();

    void printTravels();
    void printBookings();
    void printDetails();

private slots:
    void on_tableWidgetTravel_cellDoubleClicked(int row);

    void on_tableWidgetBooking_cellDoubleClicked(int row);

    void on_pushButtonSpeichern_clicked();

    void on_pushButtonSort_clicked();

private:
    Ui::KundenProfil *ui;
    std::shared_ptr<Customer>p_customer;
    std::shared_ptr<Travel>p_currentTravel;
    std::shared_ptr<Booking>p_currentBooking;
    std::shared_ptr<TravelAgency>p_travelAgency;
};

#endif // KUNDENPROFIL_H
