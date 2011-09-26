#ifndef ICALLBACK_H
#define ICALLBACK_H

class QDomDocument;

class ICallback
{
public:
    virtual void callback(QDomDocument data) = 0;
};

#endif // ICALLBACK_H
