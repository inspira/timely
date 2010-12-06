#ifndef CALLER_H
#define CALLER_H

#include <QtCore>
#include <DomainModel/timeentry.h>

class Http;
class QDomDocument;
class ICallback;

class Caller : public QObject
{
    Q_OBJECT
public:
    Caller(QObject *parent, ICallback *callbackObject);
    void getProjects();
    void getPeople(int projectId);
    void getCompanies(int projectId);
    void getLoggedUser();
    void postTimeEntry(TimeEntry, int);
    ~Caller();

private:

    Http *http;

    ICallback *callbackObject;

    QString timeEntry;
    QString serviceUrl;
    QString projects;
    QString apiKey;
    QString persons;
    QString companies;
    QString me;
};

#endif // CALLER_H
