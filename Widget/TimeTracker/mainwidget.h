#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QTime>

#include <DomainModel/project.h>
#include <DomainModel/person.h>
#include <DomainModel/company.h>

#include "ICallback.h"

class QMenu;
class Caller;
class QDomNode;
class Configuration;
class QTimer;

namespace Ui {
    class MainWidget;
}

class MainWidget : public QWidget, public ICallback
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

    void callback(QDomDocument data);

private:
    void createActions();
    void createTrayIcon();
    void setIcon();
    void closeEvent(QCloseEvent *);

    void _startTimer();
    void _stopTimer();

    void sendHours();

    double timeSpanToDouble(QTime timeSpan);

    bool canManuallySaveHours(double hours = 0);

    void tryToEnableSave(double hours = 0);

    QList<Project> parseProjects(QDomNode projectRoot);

    Person parsePerson(QDomNode personRoot);

    QList<Project> projects;

    Ui::MainWidget *ui;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    QAction *open;
    QAction *close;
    Configuration *configuration;

    QString defaultHour;

    QTimer *timer;
    QTime time;
    bool timerActive;

    Person currentPerson;

    int getCurrentProjectId();

    Caller *caller;


private slots:
    void on_btnPause_clicked();
    void on_btnPlayPause_clicked();
    void on_btnSaveConfiguration_clicked();
    void on_sbHours_valueChanged(double );
    void on_sbHours_editingFinished();
    void on_cmbCompanies_currentIndexChanged(int index);
    void on_cmbProjects_currentIndexChanged(int index);
    void on_btnSave_clicked();
    void trayIconClicked(QSystemTrayIcon::ActivationReason);
    void gotProjects(QList<Project>);
    void gotPerson(Person person);
    void updateTime();
};

#endif // MAINWIDGET_H
