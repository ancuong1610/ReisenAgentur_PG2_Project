#include "kundensuche.h"
#include "ui_kundensuche.h"
#include "kundenprofil.h"
#include <QIntValidator>
#include <QMessageBox>
#include <sstream>

KundenSuche::KundenSuche(std::shared_ptr<TravelAgency> travelAgency, QWidget *parent) :
    QDialog(parent)
  ,ui(new Ui::KundenSuche)
  ,travelAgency(travelAgency)
{
    ui->setupUi(this);
    ui->lineEditKundenId->setValidator( new QIntValidator(1, INT_MAX, this) );
}

KundenSuche::~KundenSuche()
{
    delete ui;
}

void KundenSuche::on_pushButtonAbbrechen_clicked()
{
    KundenSuche::close();
}

void KundenSuche::on_pushButtonSuchen_clicked()
{
    if(ui->lineEditKundenId->text().isEmpty()){
        QMessageBox::warning(
                    this,
                    tr("Fehler!"),
                    tr("Geben sie eine ID an!"));
        return;
    }
    long input= ui->lineEditKundenId->text().toLong();
    std::shared_ptr<Customer>foundCustomer= travelAgency->findCustomer(input);

    if(foundCustomer==NULL){
        std::ostringstream ss1;
        ss1<<input;
        std::string fehlermeldung= "Kunden mit der Id "+ss1.str()+" nicht gefunden!";
        QMessageBox::warning(
                    this,
                    tr("Fehler!"),
                    tr(fehlermeldung.c_str()));
        return;
    }
    KundenProfil *popup=new KundenProfil(foundCustomer,travelAgency);
    popup->show();
    KundenSuche::close();

}
