#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QSystemTrayIcon>

#include <DomainModel/project.h>
#include <DomainModel/person.h>
#include <DomainModel/company.h>

#include "ICallback.h"

class QMenu;
class Caller;
class QDomNode;

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

    QString defaultHour;

    Person currentPerson;

    int getCurrentProjectId();

    Caller *caller;


private slots:
    void on_sbHours_valueChanged(double );
    void on_sbHours_editingFinished();
    void on_cmbCompanies_currentIndexChanged(int index);
    void on_cmbProjects_currentIndexChanged(int index);
    void on_btnSave_clicked();
    void trayIconClicked(QSystemTrayIcon::ActivationReason);
    void gotProjects(QList<Project>);
    void gotPerson(Person person);
};

#endif // MAINWIDGET_H
