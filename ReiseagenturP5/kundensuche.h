#ifndef KUNDENSUCHE_H
#define KUNDENSUCHE_H
#include "travelagency.h"
#include <QDialog>

namespace Ui {
class KundenSuche;
}

class KundenSuche : public QDialog
{
    Q_OBJECT

public:
    explicit KundenSuche(std::shared_ptr<TravelAgency>travelAgency,QWidget *parent = nullptr);
    ~KundenSuche();

private slots:

    void on_pushButtonAbbrechen_clicked();

    void on_pushButtonSuchen_clicked();

private:
    Ui::KundenSuche *ui;
    std::shared_ptr<TravelAgency>travelAgency;
};

#endif // KUNDENSUCHE_H
