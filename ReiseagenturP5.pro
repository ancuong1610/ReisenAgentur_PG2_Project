QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addwindow.cpp \
    algorithmen.cpp \
    booking.cpp \
    customer.cpp \
    flightbooking.cpp \
    hotelbooking.cpp \
    kundenprofil.cpp \
    kundensuche.cpp \
    main.cpp \
    rentalcarreservation.cpp \
    saveoptions.cpp \
    sortfunktor.cpp \
    tableitem.cpp \
    travel.cpp \
    travelagency.cpp \
    travelagencyui.cpp \
    travelcheck.cpp \
    typos.cpp

HEADERS += \
    addwindow.h \
    booking.h \
    customer.h \
    digraph.h \
    flightbooking.h \
    hotelbooking.h \
    kundenprofil.h \
    kundensuche.h \
    rentalcarreservation.h \
    saveoptions.h \
    sortfunktor.h \
    tableitem.h \
    travel.h \
    travelagency.h \
    travelagencyui.h \
    travelcheck.h \
    typos.h

FORMS += \
    addwindow.ui \
    kundenprofil.ui \
    kundensuche.ui \
    saveoptions.ui \
    travelagencyui.ui \
    travelcheck.ui \
    typos.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
