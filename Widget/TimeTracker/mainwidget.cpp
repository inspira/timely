#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QMessageBox>
#include <QCloseEvent>
#include <QMenu>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>

#include <ServiceCalls/caller.h>
#include <configuration.h>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    defaultHour = ui->sbHours->text();

    ui->btnSave->setDisabled(true);

    caller = new Caller(this, this);

    createActions();
    createTrayIcon();
    setIcon();

    trayIcon->show();

    caller->getLoggedUser();
    caller->getProjects();
}

void MainWidget::createActions()
{
    open = new QAction(tr("&Abrir"), this);
    connect(open, SIGNAL(triggered()), this, SLOT(show()));

    close = new QAction(tr("&Sair"), this);
    connect(close, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MainWidget::createTrayIcon()
{
    trayIconMenu = new QMenu(this);

    trayIconMenu->addAction(open);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(close);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayIconClicked(QSystemTrayIcon::ActivationReason)));
}

void MainWidget::setIcon()
{
    trayIcon->setIcon(QIcon(":/resource/army-officer-icon.png"));
}

void MainWidget::closeEvent(QCloseEvent *event)
{
    if (trayIcon->isVisible()) {
        trayIcon->showMessage(tr("Still here!!!"),
        tr("This application is still running. To quit please click this icon and select Quit"));
        hide();

        event->ignore(); // Don't let the event propagate to the base class
    }
}

void MainWidget::trayIconClicked(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::Trigger)
        this->show();
}

MainWidget::~MainWidget()
{
    delete ui;

    delete trayIcon;
    delete trayIconMenu;
    delete open;
    delete close;
}


void MainWidget::callback(QDomDocument data)
{
    qDebug() << data.toString();

    QDomElement root = data.documentElement();

    if(root.tagName() == "projects")
    {
        qDebug() << "Got projects";

        gotProjects(parseProjects(root.firstChild()));
    }
    else if (root.tagName() == "person")
    {
        qDebug() << "Got person";

        gotPerson(parsePerson(root));
    }
    else if(root.tagName() == "companies")
    {
        qDebug() << "Got companies";
    }
}

QList<Project> MainWidget::parseProjects(QDomNode projectRoot)
{
    QList<Project> projects;

    while(!projectRoot.isNull()){
        if(projectRoot.toElement().tagName() == "project"){
            Project p;
            QDomNodeList nodes = projectRoot.childNodes();

            for(int i = 0; i < nodes.count(); i++){
                QDomElement element = nodes.at(i).toElement();

                if(element.tagName() == "id")
                    p.id = element.text().toInt();
                else if(element.tagName() == "name")
                    p.name = element.text();
                else if(element.tagName() == "status")
                    p.status = element.text();
             }

            projects.append(p);

        }

        projectRoot = projectRoot.nextSibling();
    }

    return projects;
}

Person MainWidget::parsePerson(QDomNode personRoot)
{
    qDebug() << personRoot.toElement().text();

    QDomNodeList nodes = personRoot.childNodes();

    qDebug() << QString("Got %1").arg(nodes.count());

    Person p;

    for(int i = 0; i < nodes.count(); i++){
        QDomElement element = nodes.at(i).toElement();

        qDebug() << element.tagName();

        if(element.tagName() == "id")
            p.id = element.text().toInt();
        else if(element.tagName() == "user-name")
            p.name = element.text();
    }

    return p;
}

void MainWidget::gotProjects(QList<Project> projects)
{
    this->projects = projects;

    for(int i = 0; i < projects.count(); i++){
        if(projects.at(i).status == "active")
            ui->cmbProjects->addItem(projects.at(i).name, projects.at(i).id);
    }
}

void MainWidget::gotPerson(Person person)
{
    ui->lblWelcome->setText(QString("Bem vindo, %1").arg(person.name));
}

void MainWidget::on_btnSave_clicked()
{

    Configuration config;

    qDebug() << config.getApplicationConfigurationFolder();
}

void MainWidget::on_cmbProjects_currentIndexChanged(int index)
{
    tryToEnableSave();
}

bool MainWidget::canManuallySaveHours(double hours)
{
    double _hours = 0;

    if(hours == 0)
        _hours = ui->sbHours->text().toDouble();
    else
        _hours = hours;

    return _hours > 0 && getCurrentProjectId() != -1;
}

void MainWidget::tryToEnableSave(double hours)
{
    ui->btnSave->setDisabled(!canManuallySaveHours(hours));
}

int MainWidget::getCurrentProjectId()
{
    for(int i = 0; i < projects.count(); i++){
        if(projects.at(i).name == ui->cmbProjects->currentText())
            return projects.at(i).id;
    }

    return -1;
}

void MainWidget::on_sbHours_valueChanged(double hours)
{
    tryToEnableSave(hours);
}
