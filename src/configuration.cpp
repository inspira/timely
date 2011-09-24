#include "configuration.h"

#include <QtCore>
#include <QSettings>

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
