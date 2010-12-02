#ifndef CALLER_H
#define CALLER_H

#include <QtCore>

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
    ~Caller();

private:

    Http *http;

    ICallback *callbackObject;

    QString serviceUrl;
    QString projects;
    QString apiKey;
    QString persons;
    QString companies;
};

#endif // CALLER_H
