#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QMessageBox>
#include <QCloseEvent>
#include <QMenu>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>

#include <ServiceCalls/caller.h>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    caller = new Caller(this, this);

    createActions();
    createTrayIcon();
    setIcon();

    ui->cmbCompanies->setDisabled(true);
    ui->cmbPeople->setDisabled(true);

    trayIcon->show();

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
    else if (root.tagName() == "people")
    {
        qDebug() << "Got people";

        gotPeople(parsePeople(root.firstChild()));
    }
    else if(root.tagName() == "companies")
    {
        qDebug() << "Got companies";

        gotCompanies(parseCompanies(root.firstChild()));
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

QList<Person> MainWidget::parsePeople(QDomNode peopleRoot)
{
    QList<Person> people;

    while(!peopleRoot.isNull()){
        if(peopleRoot.toElement().tagName() == "person"){
            Person p;
            QDomNodeList nodes = peopleRoot.childNodes();

            for(int i = 0; i < nodes.count(); i++){
                QDomElement element = nodes.at(i).toElement();

                if(element.tagName() == "id")
                    p.id = element.text().toInt();
                else if(element.tagName() == "user-name")
                    p.name = element.text();
             }

            people.append(p);

        }

        peopleRoot = peopleRoot.nextSibling();
    }

    return people;
}

QList<Company> MainWidget::parseCompanies(QDomNode companyRoot)
{
    QList<Company> companies;

    while(!companyRoot.isNull()){
        if(companyRoot.toElement().tagName() == "company"){
            Company c;
            QDomNodeList nodes = companyRoot.childNodes();

            for(int i = 0; i < nodes.count(); i++){
                QDomElement element = nodes.at(i).toElement();

                if(element.tagName() == "id")
                    c.id = element.text().toInt();
                else if(element.tagName() == "name")
                    c.name = element.text();
             }

            companies.append(c);

        }

        companyRoot = companyRoot.nextSibling();
    }

    return companies;
}

void MainWidget::gotProjects(QList<Project> projects)
{
    this->projects = projects;

    for(int i = 0; i < projects.count(); i++){
        if(projects.at(i).status == "active")
            ui->cmbProjects->addItem(projects.at(i).name, projects.at(i).id);
    }
}

void MainWidget::gotPeople(QList<Person> people)
{
    ui->cmbPeople->clear();

    for(int i = 0; i < people.count(); i++){
            ui->cmbPeople->addItem(people.at(i).name, people.at(i).id);
    }

    ui->cmbPeople->setDisabled(false);
}

void MainWidget::gotCompanies(QList<Company> companies)
{
    ui->cmbCompanies->clear();

    for(int i = 0; i < companies.count(); i++){
            ui->cmbCompanies->addItem(companies.at(i).name, companies.at(i).id);
    }

    ui->cmbCompanies->setDisabled(false);
}

void MainWidget::on_btnSave_clicked()
{

}

void MainWidget::on_cmbProjects_currentIndexChanged(int index)
{
    ui->cmbCompanies->clear();
    ui->cmbCompanies->setDisabled(true);

    ui->cmbPeople->clear();
    ui->cmbCompanies->setDisabled(true);

    int id = getCurrentProjectId();

    caller->getCompanies(id);
    caller->getPeople(id);
}

void MainWidget::on_cmbCompanies_currentIndexChanged(int index)
{

}

int MainWidget::getCurrentProjectId()
{
    for(int i = 0; i < projects.count(); i++){
        if(projects.at(i).name == ui->cmbProjects->currentText())
            return projects.at(i).id;
    }
}
