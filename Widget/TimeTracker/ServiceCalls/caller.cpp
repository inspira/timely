#include "ServiceCalls/caller.h"

#include <REST/http.h>
#include <QtXml/QDomDocument>
#include <ICallback.h>

Caller::Caller(QObject *parent, ICallback *callbackObject)
    : QObject(parent),
    serviceUrl("https://inspirasandbox.basecamphq.com/"),
    projects("project/list"),
    apiKey("dd8c4e8c9dcec2c1431c869ccc29d6c2c3745d06")
{
    http = new Http(this, callbackObject);
    this->callbackObject = callbackObject;
}

void Caller::getProjects()
{
    http->get(QString("%1%2").arg(serviceUrl).arg(projects), apiKey, QString("x"));
}

Caller::~Caller()
{
    delete http;
}
