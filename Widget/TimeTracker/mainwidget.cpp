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

#ifdef Q_WS_MAC

    extern void qt_mac_set_dock_menu(QMenu*);

#endif

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget),
    time(0, 0, 0),
    timerActive(false)
{
    ui->setupUi(this);

#ifdef Q_WS_MAC

    this->setAttribute(Qt::WA_MacBrushedMetal, true);
    this->ui->btnPause->setAttribute(Qt::WA_MacBrushedMetal, true);
    this->ui->btnPlayPause->setAttribute(Qt::WA_MacBrushedMetal, true);
    this->ui->btnSave->setAttribute(Qt::WA_MacBrushedMetal, true);
    this->ui->btnSaveConfiguration->setAttribute(Qt::WA_MacBrushedMetal, true);

#endif

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
    open = new QAction(tr("&Open"), this);
    connect(open, SIGNAL(triggered()), this, SLOT(show()));

    close = new QAction(tr("&Close"), this);
    connect(close, SIGNAL(triggered()), qApp, SLOT(quit()));

    status = new QAction(tr("Stopped"), this);
    status->setDisabled(true);

    play = new QAction(tr("Play"), this);
    connect(play, SIGNAL(triggered()), this, SLOT(on_btnPlayPause_clicked()));
    play->setDisabled(true);

    pause = new QAction(tr("Pause"), this);
    connect(pause, SIGNAL(triggered()), this, SLOT(on_btnPause_clicked()));
    pause->setDisabled(true);
}

void MainWidget::createTrayIcon()
{
    trayIconMenu = new QMenu(this);

    trayIconMenu->addAction(status);
    trayIconMenu->addAction(play);
    trayIconMenu->addAction(pause);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(open);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(close);

    trayIcon = new QSystemTrayIcon(this);

#ifdef Q_WS_MAC

    qt_mac_set_dock_menu(trayIconMenu);

#endif

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
    QDomNodeList nodes = personRoot.childNodes();

    Person p;

    for(int i = 0; i < nodes.count(); i++){
        QDomElement element = nodes.at(i).toElement();

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

    ui->cmbProjects->clear();

    for(int i = 0; i < projects.count(); i++){
        if(projects.at(i).status == "active")
            ui->cmbProjects->addItem(projects.at(i).name, projects.at(i).id);
    }

    if(ui->cmbProjects->count() > 0){
        play->setDisabled(false);
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
    currentProjectName = this->getCurrentProject().name;
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
    status->setText(QString("%1 - %2").arg(currentProjectName).arg(time.toString("hh:mm:ss")));
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
            status->setText(tr("Stopped"));
            pause->setDisabled(true);
            play->setDisabled(true);
            play->setText("Play");
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
    play->setDisabled(false);
    play->setText(tr("Stop and save"));
    pause->setDisabled(false);
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
    pause->setDisabled(true);
    play->setText("Play");
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
