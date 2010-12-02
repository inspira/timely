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

    QList<Project> parseProjects(QDomNode projectRoot);
    QList<Person> parsePeople(QDomNode peopleRoot);
    QList<Company> parseCompanies(QDomNode companyRoot);

    QList<Project> projects;

    Ui::MainWidget *ui;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    QAction *open;
    QAction *close;

    int getCurrentProjectId();

    Caller *caller;


private slots:
    void on_cmbCompanies_currentIndexChanged(int index);
    void on_cmbProjects_currentIndexChanged(int index);
    void on_btnSave_clicked();
    void trayIconClicked(QSystemTrayIcon::ActivationReason);
    void gotProjects(QList<Project>);
    void gotPeople(QList<Person>);
    void gotCompanies(QList<Company>);
};

#endif // MAINWIDGET_H
