#include "travelagencyui.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    TravelAgency TUIreisen;
    //std::shared_ptr<TravelAgency>TUI(new TravelAgency);
    QApplication a(argc, argv);
    TravelAgencyUi w(&TUIreisen);
    w.show();
    return a.exec();
}



