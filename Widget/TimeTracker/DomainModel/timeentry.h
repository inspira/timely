#ifndef TIMEENTRY_H
#define TIMEENTRY_H

class QString;
class QDate;

class TimeEntry
{
public:
    int personId;
    QDate date;
    int hours;
    QString description;
};

#endif // TIMEENTRY_H
