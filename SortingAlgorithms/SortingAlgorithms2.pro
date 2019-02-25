#-------------------------------------------------
#
# Project created by QtCreator 2015-09-26T12:05:07
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SortingAlgorithms2
TEMPLATE = app


SOURCES += main.cpp \
    GUI/mainwindow.cpp \
    GUI/PaintGraphic.cpp \
    GUI/MntDataBase.cpp \
    GUI/Ordenation.cpp \
    GUI/PopUp.cpp \
    DataBase/Connection/ConnectionDb.cpp \
    DataBase/Model/MOrdenation.cpp \
    DataBase/Dao/DAOOrdenation.cpp \
    GUI/WidPaintGraphic.cpp \
    Util/GenerateVector.cpp \
    Util/TimeMeter.cpp \
    Sort/Sort.cpp \
    Util/ShowError.cpp \
    Util/Web.cpp \
    Exceptions/Exception.cpp \
    Exceptions/ConnectionException.cpp \
    Exceptions/QueryException.cpp

HEADERS  += \
    GUI/mainwindow.h \
    GUI/PaintGraphic.h \
    GUI/MntDataBase.h \
    GUI/Ordenation.h \
    GUI/PopUp.h \
    DataBase/Connection/ConnectionDb.h \
    DataBase/Model/MOrdenation.h \
    DataBase/Dao/DAOOrdenation.h \
    GUI/WidPaintGraphic.h \
    Enums.h \
    Util/GenerateVector.h \
    Util/TimeMeter.h \
    Sort/Sort.h \
    Util/ShowError.h \
    Util/Web.h \
    Exceptions/Exception.h \
    Exceptions/ConnectionException.h \
    Exceptions/QueryException.h

FORMS    += GUI/mainwindow.ui \
    GUI/PaintGraphic.ui \
    GUI/MntDataBase.ui \
    GUI/Ordenation.ui \
    GUI/PopUp.ui

RESOURCES += \
    rsc.qrc

CONFIG += c++11
