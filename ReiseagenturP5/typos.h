#ifndef TYPOS_H
#define TYPOS_H
#include "travelagency.h"
#include <QDialog>
#include <algorithm>
#include <map>
#include <QMessageBox>

#include <QDialog>

namespace Ui {
class Typos;
}

class Typos : public QDialog
{
    Q_OBJECT

public:
    explicit Typos(std::shared_ptr<TravelAgency> travelAgency,QWidget *parent = nullptr);
    double typos(QString input, std::string data);
    std::map<double, std::string> map;
    ~Typos();

private slots:
    void on_pushButton_clicked();

    void on_listWidget_itemDoubleClicked();

private:
    Ui::Typos *ui;
    std::shared_ptr<TravelAgency> travelAgency;
};

#endif // TYPOS_H
