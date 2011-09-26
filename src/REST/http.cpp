#include "REST/http.h"

#include "ICallback.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QSslConfiguration>

#include <QMessageBox>

#include <QtXml/QDomDocument>

Http::Http(QObject * parent, ICallback *callbackObject)
    : QObject(parent)
{
    netManager = new QNetworkAccessManager(this);
    this->callbackObject = callbackObject;
}

void Http::get(QString url)
{
    _get(url, QString(""), QString(""));
}

void Http::get(QString url, QString user, QString password)
{
    _get(url, user, password, true);
}

void Http::_get(QString url, QString user, QString password, bool requiresAuthorization)
{
    QSslConfiguration config(QSslConfiguration::defaultConfiguration());

    QNetworkRequest request;


    request.setSslConfiguration(config);

    if(requiresAuthorization)
        request.setRawHeader("Authorization", "Basic " +
                             QByteArray(QString("%1:%2").arg(user).arg(password).toAscii().toBase64())
                         );
    request.setRawHeader("Accept", "application/xml");
    request.setRawHeader("Content-Type", "application/xml");

    request.setUrl(QUrl(url));

    connect(netManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finished(QNetworkReply*)));

    reply = netManager->get(request);

    connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this, SIGNAL(progress(qint64,qint64)));
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(sslError(QList<QSslError>)));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void Http::post(QString url, QString user, QString password, QString data)
{
    QSslConfiguration config(QSslConfiguration::defaultConfiguration());

    QNetworkRequest request;


    request.setSslConfiguration(config);

    request.setRawHeader("Authorization", "Basic " +
                         QByteArray(QString("%1:%2").arg(user).arg(password).toAscii().toBase64())
                     );
    request.setRawHeader("Accept", "application/xml");
    request.setRawHeader("Content-Type", "application/xml");

    request.setUrl(QUrl(url));

    connect(netManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finished(QNetworkReply*)));

    reply = netManager->post(request, data.toUtf8());

    connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this, SIGNAL(progress(qint64,qint64)));
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(sslError(QList<QSslError>)));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void Http::finished(QNetworkReply *reply)
{
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    QString code = statusCode.toString();

    QDomDocument dom;
    dom.setContent(reply);

    callbackObject->callback(dom);
}

void Http::sslError(QList<QSslError>)
{
    QMessageBox::critical(0, tr("Error!"), tr("An SSL error has ocurred.\n"));
}

void Http::networkError(QNetworkReply::NetworkError error)
{
    qDebug() << "Network error: " + error;
    QMessageBox::critical(0, tr("Error!"), tr("An network error has ocurred.\n"));
}

Http::~Http()
{
    delete reply;
    delete netManager;
}
