#include "ServiceCalls/caller.h"

#include <REST/http.h>
#include <QtXml/QDomDocument>
#include <ICallback.h>

Caller::Caller(QObject *parent, ICallback *callbackObject)
    : QObject(parent),
    serviceUrl("https://inspiradev.basecamphq.com/"),
    projects("projects.xml"),
    apiKey("fef639fd1055d3df72ac7fe0a8d9c5cd25376208"),
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
