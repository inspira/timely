#ifndef HTTP_H
#define HTTP_H

#include <QtCore>

class QNetworkAccessManager;
class QNetworkReply;
class ICallback;

class Http : public QObject
{
    Q_OBJECT

public:

    Http(QObject *parent, ICallback *callbackObject);
    ~Http();

    void get(QString url, QString user, QString password);

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

};

#endif // HTTP_H
