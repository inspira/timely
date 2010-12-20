#include "configuration.h"

#include <QtCore>
#include <QSettings>

QString Configuration::getApplicationConfigurationFolder()
{
    QString path("");

#ifdef Q_WS_WIN
    path = QDir::homePath() + "/Application Data/Timely";
#else
    path = QDir::homePath() + "/.config/Timely";
#endif

    if(!QDir(path).exists())
        QDir().mkdir(path);

    return path;
}

QString Configuration::getApiKey()
{
    QSettings settings(QString("Inspira"), QString("Timely Widget"));

    return settings.value("apikey").toString();
}

void Configuration::setApiKey(QString apiKey)
{
    QSettings settings(QString("Inspira"), QString("Timely Widget"));

    settings.setValue("apikey", apiKey);
}

QString Configuration::getBasecampUrl()
{
    QSettings settings(QString("Inspira"), QString("Timely Widget"));

    return settings.value("basecamp").toString();
}

void Configuration::setBasecampUrl(QString url)
{
    QSettings settings(QString("Inspira"), QString("Timely Widget"));

    settings.setValue("basecamp", url);
}
