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
    src/GA_main.cpp \
    src/GA_mainwindow.cpp \
    src/GM_mainwindow.cpp \
    src/animaux.cpp \
    src/arduino.cpp \
    src/connection.cpp \
    src/login.cpp \
    src/mainwindow_gp.cpp \
    src/mainwindow_gs.cpp \
    src/matriel.cpp \
    src/menu.cpp \
    src/produit.cpp \
    src/reminder.cpp \
    src/section.cpp

HEADERS += \
    src/GA_mainwindow.h \
    src/GM_mainwindow.h \
    src/animaux.h \
    src/arduino.h \
    src/connection.h \
    src/login.h \
    src/mainwindow_gp.h \
    src/mainwindow_gs.h \
    src/matriel.h \
    src/menu.h \
    src/produit.h \
    src/reminder.h \
    src/section.h

FORMS += \
    ui/GA_mainwindow.ui \
    ui/GM_mainwindow.ui \
    ui/login.ui \
    ui/mainwindow_gp.ui \
    ui/mainwindow_gs.ui \
    ui/menu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/backgrounds.qrc
