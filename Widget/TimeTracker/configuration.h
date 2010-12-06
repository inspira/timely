#ifndef CONFIGURATION_H
#define CONFIGURATION_H

class QString;

class Configuration
{
public:
    QString getApplicationConfigurationFolder();
    QString getApiKey();
    void setApiKey(QString apiKey);
};

#endif // CONFIGURATION_H
