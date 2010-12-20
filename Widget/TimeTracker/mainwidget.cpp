#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QMessageBox>
#include <QCloseEvent>
#include <QMenu>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QTimer>

#include <ServiceCalls/caller.h>
#include <configuration.h>

#include <DomainModel/timeentry.h>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget),
    time(0, 0, 0),
    timerActive(false)
{
    ui->setupUi(this);

    ui->btnPause->setDisabled(true);

    configuration = new Configuration();

    ui->txtApiKey->setText(configuration->getApiKey());
    ui->txtBasecamp->setText(configuration->getBasecampUrl());

    defaultHour = ui->sbHours->text();

    ui->btnSave->setDisabled(true);

    caller = new Caller(this, this, ui->txtApiKey->text(), ui->txtBasecamp->text());

    createActions();
    createTrayIcon();
    setIcon();

    trayIcon->show();

    if(!ui->txtApiKey->text().isEmpty() && !ui->txtBasecamp->text().isEmpty()){
        caller->getLoggedUser();
        caller->getProjects();
    }
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
        tr("The Timely Widget is still running. To quit please click this icon and select Quit"));
        hide();

        event->ignore(); // Don't let the event propagate to the base class
    }
}

void MainWidget::trayIconClicked(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::Trigger)
    {
        this->hide();
        this->show();
    }
}

MainWidget::~MainWidget()
{
    //TODO: Save hours to local file if timer is active

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

    if(ui->cmbProjects->count() > 0){
        ui->btnPlayPause->setDisabled(false);
        ui->cmbProjects->setDisabled(false);
    }
}

void MainWidget::gotPerson(Person person)
{
    this->currentPerson = person;
    ui->lblWelcome->setText(QString("Welcome, %1").arg(person.name));
}

void MainWidget::on_btnSave_clicked()
{
    Configuration config;

    TimeEntry timeEntry;
    timeEntry.date = QDate::currentDate();
    timeEntry.hours = ui->sbHours->text().toDouble();
    timeEntry.personId = currentPerson.id;
    timeEntry.description = ui->txtDescription->toPlainText();

    caller->postTimeEntry(timeEntry, this->getCurrentProjectId());

    ui->sbHours->clear();
    ui->txtDescription->clear();
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

void MainWidget::on_btnSaveConfiguration_clicked()
{
    configuration->setApiKey(ui->txtApiKey->text());
    configuration->setBasecampUrl(ui->txtBasecamp->text());

    caller = new Caller(this, this, ui->txtApiKey->text(), ui->txtBasecamp->text());

    caller->getLoggedUser();
    caller->getProjects();
}

void MainWidget::updateTime()
{
    time = time.addSecs(1);
    qDebug() << time.toString("hh:mm:ss");
    ui->txtRunningTime->setText(time.toString("hh:mm:ss"));

    if(time.second() == 0 && time.minute() % 5 == 0){
        if(trayIcon->isVisible()){
            trayIcon->showMessage(tr("Reminder"), tr("You're currently working on: %1").arg(getCurrentProject().name));
        }
    }
}

Project MainWidget::getCurrentProject()
{
    int id = this->getCurrentProjectId();

    for(int i = 0; i < projects.count(); i++){
        if(projects.at(i).id == id)
            return projects.at(i);
    }

    return Project();
}

void MainWidget::on_cmbCompanies_currentIndexChanged(int){}
void MainWidget::on_sbHours_editingFinished(){}

void MainWidget::on_btnPlayPause_clicked()
{
    if(!timerActive){
        ui->cmbProjects->setDisabled(true);
        _startTimer();
    }
    else{
        if(QMessageBox::question(this, tr("Question"), tr("Do you really wish to send your hours to Basecamp?"), QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes){
            sendHours();
            ui->txtRunningTime->clear();
            ui->cmbProjects->setDisabled(false);
        }
    }
}

void MainWidget::_startTimer()
{
    qDebug() << "Started timer";
    ui->btnPlayPause->setIcon(QIcon(":/resource/Player End.png"));
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()), this, SLOT(updateTime()));
    timer->start(1000);
    timerActive = true;
    ui->btnPause->setDisabled(false);
}

void MainWidget::_stopTimer()
{
    qDebug() << "Stopped timer";
    ui->btnPlayPause->setIcon(QIcon(":/resource/Player Play.png"));
    timer->stop();
    delete timer;
    timerActive = false;
}

void MainWidget::on_btnPause_clicked()
{
    _stopTimer();
    ui->btnPause->setDisabled(true);
}

void MainWidget::sendHours()
{
    _stopTimer();

    QTime timeWorked = this->time;
    time = QTime(0, 0, 0);

    double hours = timeSpanToDouble(timeWorked);

    if(hours == 0){
        QMessageBox::warning(this, tr("Not enough hours"), tr("You have not worked the minimum amount of time that Basecamp can compute."));
        return;
    }

    TimeEntry timeEntry;
    timeEntry.date = QDate::currentDate();
    timeEntry.hours = hours;
    timeEntry.personId = currentPerson.id;
    timeEntry.description = ui->txtDescription->toPlainText();

    caller->postTimeEntry(timeEntry, this->getCurrentProjectId());
}

double MainWidget::timeSpanToDouble(QTime time)
{
    double result = time.hour();

    if(time.minute() != 0)
        result += (double)time.minute() / 60;

    return result;
}
