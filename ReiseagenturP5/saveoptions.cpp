#include "saveoptions.h"
#include "ui_saveoptions.h"

SaveOptions::SaveOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveOptions)
{
    ui->setupUi(this);
}

SaveOptions::~SaveOptions()
{
    delete ui;
}

void SaveOptions::on_radioButtonId_clicked()
{
    mode = SortFunktor::id;
    ui->pushButtonSave->setEnabled(true);
}


void SaveOptions::on_radioButtonPrice_clicked()
{
    mode = SortFunktor::preis;
    ui->pushButtonSave->setEnabled(true);
}


void SaveOptions::on_radioButtonFromDate_clicked()
{
    mode = SortFunktor::fromDate;
    ui->pushButtonSave->setEnabled(true);
}


void SaveOptions::on_radioButtonToDate_clicked()
{
    mode = SortFunktor::toDate;
    ui->pushButtonSave->setEnabled(true);
}


void SaveOptions::on_pushButtonSave_clicked()
{
    SaveOptions::close();
}

SortFunktor::Modus SaveOptions::getMode() const
{
    return mode;
}

