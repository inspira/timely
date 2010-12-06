#include "configuration.h"

#include <QtCore>

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
    QFile file(getApplicationConfigurationFolder() + "/configuration");

    if(file.open(QFile::ReadOnly))
    {
        return QString(file.readAll());
    }

    return QString("");
}

void Configuration::setApiKey(QString apiKey)
{
    QFile file(getApplicationConfigurationFolder() + "/configuration");

    if(file.open(QFile::WriteOnly))
    {
        QTextStream stream (&file);
        stream << apiKey;

        stream.flush();
    }
}
