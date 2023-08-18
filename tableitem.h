#ifndef TABLEITEM_H
#define TABLEITEM_H


#include <QTableWidgetItem>

class TableItem:public QTableWidgetItem
{
    QString value;
public:
    TableItem(QString value);

    virtual bool operator<(QTableWidgetItem const &b)const;
};

#endif // TABLEITEM_H
