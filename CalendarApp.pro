#-------------------------------------------------
#
# Project created by QtCreator 2018-09-09T02:50:25
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = CalendarApp
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
        main.cpp \
        mainwindow.cpp \
    registerdialog.cpp \
    mongodbconnection.cpp \
    logindialog.cpp \
    credential.cpp \
    calendarscreen.cpp \
    neweventdialog.cpp \
    newemaildialog.cpp \
    aboutevent.cpp \
    selectedeventdialog.cpp \
    sendemail.cpp

HEADERS += \
        mainwindow.h \
    registerdialog.h \
    mongodbconnection.h \
    logindialog.h \
    credential.h \
    calendarscreen.h \
    neweventdialog.h \
    newemaildialog.h \
    aboutevent.h \
    selectedeventdialog.h \
    sendemail.h

FORMS += \
        mainwindow.ui \
    registerdialog.ui \
    logindialog.ui \
    calendarscreen.ui \
    neweventdialog.ui \
    newemaildialog.ui \
    selectedeventdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += libmongocxx

# Following lines are added to use poco libraies
# May not work properly on windows

unix|win32: LIBS += -lPocoNet

unix|win32: LIBS += -lPocoFoundation

unix|win32: LIBS += -lPocoNetSSL

unix|win32: LIBS += -lPocoUtil
