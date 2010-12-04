#include "ServiceCalls/caller.h"

#include <REST/http.h>
#include <QtXml/QDomDocument>
#include <ICallback.h>

Caller::Caller(QObject *parent, ICallback *callbackObject)
    : QObject(parent),
    serviceUrl("https://inspirasandbox.basecamphq.com/"),
    projects("projects.xml"),
    apiKey("dd8c4e8c9dcec2c1431c869ccc29d6c2c3745d06"),
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

Caller::~Caller()
{
    delete http;
}
