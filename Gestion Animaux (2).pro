#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T21:45:23
#
#-------------------------------------------------

QT += core gui sql
QT += core gui sql printsupport charts script
QT += charts
QT += serialport
QT += core gui serialport
QT += widgets
QT += printsupport
QT +=sql
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Atelier_Connexion
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    GA_main.cpp \
    GA_mainwindow.cpp \
    GM_mainwindow.cpp \
    animaux.cpp \
    arduino.cpp \
    connection.cpp \
    login.cpp \
    mainwindow_gp.cpp \
    mainwindow_gs.cpp \
    matriel.cpp \
    menu.cpp \
    produit.cpp \
    reminder.cpp \
    section.cpp

HEADERS += \
    GA_mainwindow.h \
    GM_mainwindow.h \
    animaux.h \
    arduino.h \
    connection.h \
    login.h \
    mainwindow_gp.h \
    mainwindow_gs.h \
    matriel.h \
    menu.h \
    produit.h \
    reminder.h \
    section.h

FORMS += \
    GA_mainwindow.ui \
    GM_mainwindow.ui \
    login.ui \
    mainwindow_gp.ui \
    mainwindow_gs.ui \
    menu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    backgrounds.qrc
