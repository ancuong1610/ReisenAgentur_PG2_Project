#ifndef ADDWINDOW_H
#define ADDWINDOW_H
#include "travelagency.h"
#include <QDialog>

namespace Ui {
class AddWindow;
}

class AddWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddWindow(char type,std::shared_ptr<TravelAgency>travelAgency,QWidget *parent = nullptr);
    ~AddWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AddWindow *ui;
    std::shared_ptr<TravelAgency>travelAgency;
};

#endif // ADDWINDOW_H
