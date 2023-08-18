#include "addwindow.h"
#include "ui_addwindow.h"
#include <QMessageBox>

AddWindow::AddWindow(char type,std::shared_ptr<TravelAgency>travelAgency,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddWindow),
    travelAgency(travelAgency)
{
    ui->setupUi(this);
    if(type == 'K'){
        ui->nameEdit->setText("Geben Sie Name von dem neuen Kunde!");
        ui->comboBox->hide();
    }
    else{
        ui->nameEdit->setText("Geben Sie ID des Kundes von dem neuen Buchung!");
    }
}

AddWindow::~AddWindow()
{
    delete ui;
}

void AddWindow::on_pushButton_clicked()
{
    if (ui->nameEdit->text() == "Geben Sie Name von dem neuen Kunde!"){
        std::string eingabe= ui->lineEdit->text().toStdString();
        travelAgency->addKunden(eingabe);
        QMessageBox::information(
                    this,
                    tr("Gespeichert"),
                    tr("Neue Kunde wird hinzufugt!"));
    }
    else{
        if(ui->comboBox->currentText() == QString::fromStdString("Flight Booking")){
            long eingabe= ui->lineEdit->text().toLong();
            travelAgency->addBuchung(eingabe,'F');
            QMessageBox::information(
                        this,
                        tr("Gespeichert"),
                        tr("Neue Flug Buchung wird hinzufugt!"));
        }
        else if(ui->comboBox->currentText() == QString::fromStdString("Hotel Booking")){
            long eingabe= ui->lineEdit->text().toLong();
            travelAgency->addBuchung(eingabe,'H');
            QMessageBox::information(
                        this,
                        tr("Gespeichert"),
                        tr("Neue Hotel Buchung wird hinzufugt!"));
        }
        else if(ui->comboBox->currentText() == QString::fromStdString("Rental Car Reservation")){
            long eingabe= ui->lineEdit->text().toLong();
            travelAgency->addBuchung(eingabe,'C');
            QMessageBox::information(
                        this,
                        tr("Gespeichert"),
                        tr("Neue Rental Buchung wird hinzufugt!"));
        }
    }
}

