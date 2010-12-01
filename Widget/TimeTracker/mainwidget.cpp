#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QMessageBox>
#include <QCloseEvent>
#include <QMenu>

#include <browserwindow.h>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    createActions();
    createTrayIcon();
    setIcon();

    trayIcon->show();
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
    delete browser;

    delete trayIcon;
    delete trayIconMenu;
    delete open;
    delete close;
}

void MainWidget::on_btnBrowser_clicked()
{
    browser = new BrowserWindow(this);

    browser->showFullScreen();
}
