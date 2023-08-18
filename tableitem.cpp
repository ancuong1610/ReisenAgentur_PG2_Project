#include "tableitem.h"
#include <QDate>


TableItem::TableItem(QString value)
    :QTableWidgetItem(value), value(value)
{

}

bool TableItem::operator <(const QTableWidgetItem &b) const
{
    long AId,BId;
    QDate ADatum, BDatum;
    double Aprice, Bprice;
    TableItem const *vergleich= dynamic_cast<TableItem const*>(&b);
    switch (column()) {
    case 0:
        AId = value.toLong();
        BId = vergleich->value.toLong();
        return AId<BId;
    case 1:
    case 2:
        ADatum = QDate::fromString(value, "dd.MM.yyyy");
        BDatum = QDate::fromString(vergleich->value, "dd.MM.yyyy");
        return ADatum<BDatum;
    case 3:
        Aprice = value.toDouble();
        Bprice = vergleich->value.toDouble();
        return Aprice<Bprice;
    }
    return false;
}
