#-------------------------------------------------
#
# Project created by QtCreator 2010-11-29T16:14:41
#
#-------------------------------------------------

QT       += core gui

QT       += network xml

    TARGET = 32bit_binary
    QMAKE_CFLAGS_RELEASE += -m32


TARGET = TimeTracker
TEMPLATE = app


SOURCES += main.cpp \
    mainwidget.cpp \
    REST/http.cpp \
    ServiceCalls/caller.cpp \
    configuration.cpp

HEADERS  += \
    mainwidget.h \
    REST/http.h \
    ICallback.h \
    ServiceCalls/caller.h \
    DomainModel/project.h \
    DomainModel/person.h \
    DomainModel/company.h \
    configuration.h \
    DomainModel/timeentry.h

FORMS    += \
    mainwidget.ui

RESOURCES += \
    Resource.qrc
