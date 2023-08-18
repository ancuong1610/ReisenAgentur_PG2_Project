#ifndef SAVEOPTIONS_H
#define SAVEOPTIONS_H
#include "sortfunktor.h"
#include <QDialog>

namespace Ui {
class SaveOptions;
}

class SaveOptions : public QDialog
{
    Q_OBJECT

public:
    explicit SaveOptions(QWidget *parent = nullptr);
    ~SaveOptions();

    SortFunktor::Modus getMode() const;

private slots:
    void on_radioButtonId_clicked();

    void on_radioButtonPrice_clicked();

    void on_radioButtonFromDate_clicked();

    void on_radioButtonToDate_clicked();

    void on_pushButtonSave_clicked();

private:
    Ui::SaveOptions *ui;
    SortFunktor::Modus mode;
};

#endif // SAVEOPTIONS_H
