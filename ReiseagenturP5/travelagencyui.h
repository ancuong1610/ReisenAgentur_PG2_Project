#ifndef TRAVELAGENCYUI_H
#define TRAVELAGENCYUI_H
#include "travelagency.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class TravelAgencyUi; }
QT_END_NAMESPACE

class TravelAgencyUi : public QMainWindow
{
    Q_OBJECT

public:
    //TravelAgencyUi(std::shared_ptr<TravelAgency>,QWidget *parent = nullptr);
    TravelAgencyUi(TravelAgency *travelAgency, QWidget *parent = nullptr);
    ~TravelAgencyUi();

    void printTable();

private slots:
    void on_pushButtonDateiLesen_clicked();

    void on_pushButtonJson_clicked();

    void on_pushButtonSearchCustomer_clicked();

    void on_tableWidgetCustomers_cellDoubleClicked(int row);

    void on_pushButtonSaveToJson_clicked();

    void on_pushButtonCheckTravels_clicked();

    void on_pushButton_clicked();

    void on_actionKunden_triggered();

    void on_actionBooking_triggered();

private:
    std::shared_ptr<TravelAgency>travelAgency;
    Ui::TravelAgencyUi *ui;
};
#endif // TRAVELAGENCYUI_H
