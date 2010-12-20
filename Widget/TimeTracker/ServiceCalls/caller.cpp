#include "ServiceCalls/caller.h"

#include <REST/http.h>
#include <QtXml/QDomDocument>
#include <ICallback.h>

Caller::Caller(QObject *parent, ICallback *callbackObject, QString key, QString url)
    : QObject(parent),
    timeEntry("projects/%1/time_entries.xml"),
    serviceUrl(url),
    projects("projects.xml"),
    apiKey(key),
    persons("projects/%1/people.xml"),
    companies("projects/%1/companies.xml"),
    me("me.xml")
{
    http = new Http(this, callbackObject);
    this->callbackObject = callbackObject;
}

void Caller::getProjects()
{
    http->get(QString("%1%2").arg(serviceUrl).arg(projects), apiKey, QString("x"));
}

void Caller::getPeople(int projectId)
{
    http->get(QString("%1%2").arg(serviceUrl).arg(persons.arg(projectId)), apiKey, QString("x"));
}

void Caller::getCompanies(int projectId)
{
    http->get(QString("%1%2").arg(serviceUrl).arg(companies.arg(projectId)), apiKey, QString("x"));
}

void Caller::getLoggedUser()
{
    http->get(QString("%1%2").arg(serviceUrl).arg(me), apiKey, QString("x"));
}

void Caller::postTimeEntry(TimeEntry timeEntry, int projectId)
{
    QString xml("<time-entry><person-id>%1</person-id><date>%2</date><hours>%3</hours><description>%4</description></time-entry>");
    xml = xml.arg(timeEntry.personId).arg(timeEntry.date.toString(QString("yyyyMMdd"))).arg(timeEntry.hours).arg(timeEntry.description);

    qDebug() << xml;

    http->post(QString("%1%2").arg(serviceUrl).arg(this->timeEntry.arg(projectId)), apiKey, QString("x"), xml);
}

Caller::~Caller()
{
    delete http;
}
