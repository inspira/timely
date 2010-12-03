#include "configuration.h"

#include <QtCore>

QString Configuration::getApplicationConfigurationFolder()
{
#ifdef Q_WS_WIN
    return QDir::homePath() + "/Application Data/Timely";
#else
    return QDir::homePath() + "/.config/Timely";
#endif
}
