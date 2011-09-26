QT = core gui network xml

TARGET = timely
TEMPLATE = app
DESTDIR = build
MOC_DIR = src/moc
OBJECTS_DIR = out
UI_HEADERS_DIR = src/ui
UI_SOURCES_DIR = src/ui
RCC_DIR = src/resources
INCLUDEPATH += src src/REST src/ServiceCalls src/DomainModel

SOURCES += \
    src/main.cpp \
    src/mainwidget.cpp \
    src/REST/http.cpp \
    src/ServiceCalls/caller.cpp \
    src/configuration.cpp

HEADERS += \
    src/mainwidget.h \
    src/REST/http.h \
    src/ICallback.h \
    src/ServiceCalls/caller.h \
    src/DomainModel/project.h \
    src/DomainModel/person.h \
    src/DomainModel/company.h \
    src/configuration.h \
    src/DomainModel/timeentry.h

FORMS += \
    src/mainwidget.ui

RESOURCES += \
    src/Resource.qrc
