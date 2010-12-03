#ifndef HTTP_H
#define HTTP_H

#include <QtCore>
#include <QList>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QSslError>

class QNetworkAccessManager;
class ICallback;

class Http : public QObject
{
    Q_OBJECT

public:

    Http(QObject *parent, ICallback *callbackObject);
    ~Http();

    void get(QString url, QString user, QString password);
    void get(QString url);

    void post(QString url, QString user, QString password, QString data);

signals:
    void progress(qint64,qint64);


private:
    ICallback *callbackObject;
    QMutex mutex;
    QNetworkAccessManager *netManager;
    QNetworkReply *reply;

    void _get(QString url, QString user, QString password, bool requiresAuthorization = false);

private slots:
    void finished(QNetworkReply *reply);
    void sslError(QList<QSslError>);
    void networkError(QNetworkReply::NetworkError);

};

#endif // HTTP_H
