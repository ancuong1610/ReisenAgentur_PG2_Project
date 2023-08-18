#include "travelagencyui.h"
#include <iostream>
#include "kundenprofil.h"
#include "kundensuche.h"
#include "saveoptions.h"
#include "tableitem.h"
#include "travelcheck.h"
#include "ui_travelagencyui.h"
#include "typos.h"
#include "addwindow.h"

#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <fstream>

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonParseError>

TravelAgencyUi::TravelAgencyUi(TravelAgency *travelAgency, QWidget *parent)
    : QMainWindow(parent)
    , travelAgency(travelAgency)
    , ui(new Ui::TravelAgencyUi)
{
    ui->setupUi(this);
    ui->tableWidgetCustomers->hide();
    ui->tableWidgetCustomers->setColumnWidth(1,250);
}

TravelAgencyUi::~TravelAgencyUi()
{
    delete ui;
}

void TravelAgencyUi::printTable()
{
    ui->tableWidgetCustomers->setHorizontalHeaderLabels(QStringList() << "Id" << "Kundenname");
    ui->tableWidgetCustomers->setRowCount(travelAgency->getNumberOfCustomers());
    for(int zeile=0; zeile<travelAgency->getNumberOfCustomers();zeile++){
        std::ostringstream ss1;
        ss1<<travelAgency->getCustomerId(zeile);

        ui->tableWidgetCustomers->setItem(zeile, 0, new TableItem(QString::fromStdString(ss1.str())));
        ui->tableWidgetCustomers->setItem(zeile, 1, new QTableWidgetItem(QString::fromStdString(travelAgency->getCustomerName(zeile))));
    }
}

void TravelAgencyUi::on_pushButtonDateiLesen_clicked()
{
    bool fehlergefunden=false;
    QString Dateiname= QFileDialog::getOpenFileName(this, tr("Datei öffnen"), "/Users/faze/Downloads/PG2 file/Prak/", tr("Textdateien (*.txt)"));
    do{
        try{
            travelAgency->readFile(Dateiname);
        }catch(std::runtime_error &fehlermeldung){
            QMessageBox::warning( this, tr("Warnung"), tr(fehlermeldung.what()) );
            while (!QMessageBox::Close) {}
            //travelAgency->heapLoeschen();
            fehlergefunden=true;
            continue;
        }catch(std::logic_error &fehlermeldung){
            QMessageBox::warning( this, tr("Warnung"), tr(fehlermeldung.what()) );
            while (!QMessageBox::Close) {}
            //travelAgency->heapLoeschen();
            fehlergefunden=true;
            continue;
        }
        fehlergefunden=false;
    }while(fehlergefunden);
    QMessageBox::information(
                this,

                tr("Datei wurde erfolgreich ausgelesen!"),
                tr(travelAgency->getSummary().c_str() ));


    printTable();

    ui->pushButtonSearchCustomer->setEnabled(true);
    ui->pushButtonSaveToJson->setEnabled(true);
    ui->pushButtonDateiLesen->hide();
    ui->pushButtonCheckTravels->setEnabled(true);
    ui->tableWidgetCustomers->show();
}

void TravelAgencyUi::on_pushButtonJson_clicked()
{
    QString Dateiname= QFileDialog::getOpenFileName(this,"Open a File", "/Users/faze/Downloads/PG2 file/Prak/5/");
    travelAgency->readJsonFile(Dateiname);
    QMessageBox::information(
                this,
                tr("Successfull"),
                tr("Json file wird erfolgreich gelesen"));
    ui->pushButtonJson->hide();
}

void TravelAgencyUi::on_pushButtonSearchCustomer_clicked()
{
    KundenSuche *popup=new KundenSuche(travelAgency);
    popup->setWindowModality(Qt::ApplicationModal);
    popup->show();
}

void TravelAgencyUi::on_tableWidgetCustomers_cellDoubleClicked(int row)
{
    QTableWidgetItem* IdItem = ui->tableWidgetCustomers->item(row, 0);
    long CustomerId= IdItem->text().toLong();
    KundenProfil *popup=new KundenProfil(travelAgency->findCustomer(CustomerId), travelAgency);
    popup->show();
}

void TravelAgencyUi::on_pushButtonSaveToJson_clicked()
{
    SortFunktor sorter;
    SaveOptions *popup = new SaveOptions;
    popup->show();
    popup->exec();
    SortFunktor::Modus mode = popup->getMode();
    switch (mode) {
    case SortFunktor::id:
        sorter.setModus(SortFunktor::id);
        break;
    case SortFunktor::preis:
        sorter.setModus(SortFunktor::preis);
        break;
    case SortFunktor::fromDate:
        sorter.setModus(SortFunktor::fromDate);
        break;
    case SortFunktor::toDate:
        sorter.setModus(SortFunktor::toDate);
        break;
    }
    travelAgency->saveToJSON(sorter);
}

void TravelAgencyUi::on_pushButtonCheckTravels_clicked()
{
    TravelCheck *popup=new TravelCheck(travelAgency);
    popup->setWindowModality(Qt::ApplicationModal);
    popup->show();
}

void TravelAgencyUi::on_pushButton_clicked()
{
    Typos *popup = new Typos(travelAgency);
    popup->setWindowModality(Qt::ApplicationModal);
    popup->exec();
}

void TravelAgencyUi::on_actionKunden_triggered()
{
    AddWindow *popup = new AddWindow('K', travelAgency);
    popup->setWindowModality(Qt::ApplicationModal);
    popup->exec();
    if(popup->close() == true){
        ui->tableWidgetCustomers->clear();
        printTable();
    }
}

void TravelAgencyUi::on_actionBooking_triggered()
{
    AddWindow *popup = new AddWindow('B', travelAgency);
    popup->setWindowModality(Qt::ApplicationModal);
    popup->exec();
}

