#ifndef TRAVELCHECK_H
#define TRAVELCHECK_H
#include "travelagency.h"
#include <QDialog>

namespace Ui {
class TravelCheck;
}

class TravelCheck : public QDialog
{
    Q_OBJECT

public:
    explicit TravelCheck(std::shared_ptr<TravelAgency>travelAgency,QWidget *parent = nullptr);
    ~TravelCheck();

    void printTable();

private:
    Ui::TravelCheck *ui;
    std::shared_ptr<TravelAgency>travelAgency;
};

#endif // TRAVELCHECK_H
