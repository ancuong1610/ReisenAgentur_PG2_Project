#include <sstream>
#include "travelcheck.h"
#include "tableitem.h"
#include "ui_travelcheck.h"

TravelCheck::TravelCheck(std::shared_ptr<TravelAgency> travelAgency, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TravelCheck),
    travelAgency(travelAgency)
{
    ui->setupUi(this);
    printTable();
}



TravelCheck::~TravelCheck()
{
    delete ui;
}

void TravelCheck::printTable()
{
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Travel Id" << "Fehlendes Hotel"<<"Überflüssiges Hotel"<<"Überflüssiger Mietwagen"<<"Roundtrip");
    ui->tableWidget->setRowCount(travelAgency->getAllTravels().size());
    for(size_t i=0;i< travelAgency->getAllTravels().size();i++){
        std::stringstream ss1;
        long Travelid=travelAgency->getAllTravels()[i]->getId();
        ss1<<Travelid;
        //ui->tableWidgetTravel->setItem(zeile, 0, new TableItem(QString::fromStdString(ss2.str())));
        ui->tableWidget->setItem(i,0,new TableItem(QString::fromStdString(ss1.str())));
        if(travelAgency->getAllTravels()[i]->checkEnoughHotels())
            ui->tableWidget->setItem(i,1,new TableItem("✅"));
        else
            ui->tableWidget->setItem(i,1,new TableItem("❌"));

        if(travelAgency->getAllTravels()[i]->checkNoUselessHotels())
            ui->tableWidget->setItem(i,2,new TableItem("✅"));
        else
            ui->tableWidget->setItem(i,2,new TableItem("❌"));

        if(travelAgency->getAllTravels()[i]->checkNoUselessRentalCars())
            ui->tableWidget->setItem(i,3,new TableItem("✅"));
        else
            ui->tableWidget->setItem(i,3,new TableItem("❌"));

        if(travelAgency->getAllTravels()[i]->checkRoundtrip())
            ui->tableWidget->setItem(i,4,new TableItem("✅"));
        else
            ui->tableWidget->setItem(i,4,new TableItem("❌"));
    }
}
