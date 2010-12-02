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

//Test

void MainWidget::callback(QDomDocument data)
{
    QDomElement root = data.documentElement();

    if(root.tagName() == "projects")
    {
        qDebug() << "Got projects";

        QDomNode project = root.firstChild();

        while(!project.isNull()){
            if(project.toElement().tagName() == "project"){
                int id = -1;
                QString name("");

                QDomNodeList nodes = project.childNodes();

                for(int i = 0; i < nodes.count(); i++){
                    QDomElement element = nodes.at(i).toElement();

                    if(element.tagName() == "id")
                        id = element.text().toInt();
                    else if(element.tagName() == "name")
                        name = element.text();
                }

                ui->cmbProjects->addItem(name, id);

            }

            project = project.nextSibling();
        }
    }
}

//!Test

void MainWidget::on_btnSave_clicked()
{
}
