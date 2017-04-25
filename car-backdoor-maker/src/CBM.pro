#-------------------------------------------------
#
# Project created by QtCreator 2017-01-02T16:27:14
# By @UnaPibaGeek - @holesec
# Release date: July 10th 2017.
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CBM
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcgaugewidget.cpp \
    input_filter.cpp

HEADERS  += mainwindow.h \
    qcgaugewidget.h \
    input_filter.h

FORMS    += mainwindow.ui

RESOURCES += \
    connect_icon.qrc \
    write_icon.qrc \
    disconnect_icon.qrc \
    clear_icon.qrc \
    help_icon.qrc \
    about_icon.qrc \
    updates_icon.qrc \
    exit_icon.qrc \
    save_icon.qrc \
    restore_icon.qrc \
    look_icon.qrc \
    gps_icon.qrc \
    frame_icon.qrc

DISTFILES +=
