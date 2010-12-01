#include "REST/http.h"

#include "ICallback.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include <QtXml/QDomDocument>

Http::Http(QObject * parent, ICallback *callbackObject)
    : QObject(parent)
{
    netManager = new QNetworkAccessManager(this);
    this->callbackObject = callbackObject;
}

void Http::get(QString url, QString user, QString password)
{
    _get(url, user, password); // TODO: Asynchronous get!!!
}

void Http::_get(QString url, QString user, QString password, bool requiresAuthorization)
{
    mutex.lock(); // Let's be thread-safe shall we?

    QNetworkRequest request;

    if(requiresAuthorization)
        request.setRawHeader("Authorization", "Basic" +
                             QByteArray(QString("%1:%2").arg(user).arg(password).toAscii().toBase64())
                         );

    request.setUrl(QUrl(url));

    connect(netManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finished(QNetworkReply*)));

    reply = netManager->get(request);

    connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this, SIGNAL(progress(qint64,qint64)));

    mutex.unlock();
}

void Http::finished(QNetworkReply *reply)
{
    QDomDocument dom;
    dom.setContent(reply);

    callbackObject->callback(dom);
}

Http::~Http()
{
    delete netManager;
}
