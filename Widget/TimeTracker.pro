#-------------------------------------------------
#
# Project created by QtCreator 2010-11-29T16:14:41
#
#-------------------------------------------------

QT       += core gui

QT       += network xml

DESTDIR = ../../../Timely-build

TARGET = timely
TEMPLATE = app
DESTDIR = build

SOURCES += \
    src/main.cpp \
    src/mainwidget.cpp \
    src/REST/http.cpp \
    src/ServiceCalls/caller.cpp \
    src/configuration.cpp

HEADERS  += \
    src/mainwidget.h \
    src/REST/http.h \
    src/ICallback.h \
    src/ServiceCalls/caller.h \
    src/DomainModel/project.h \
    src/DomainModel/person.h \
    src/DomainModel/company.h \
    src/configuration.h \
    src/DomainModel/timeentry.h

FORMS    += \
    src/mainwidget.ui

RESOURCES += \
    src/Resource.qrc
