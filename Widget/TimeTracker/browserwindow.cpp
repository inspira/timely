#include "browserwindow.h"
#include "ui_browserwindow.h"

BrowserWindow::BrowserWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BrowserWindow)
{
    ui->setupUi(this);

    createActions();

    ui->webView->load(QString("http://raphaelcruzeiro.com/"));
}

void BrowserWindow::createActions()
{
    connect(ui->webView, SIGNAL(loadProgress(int)), ui->progressBar, SLOT(setValue(int)));
}

BrowserWindow::~BrowserWindow()
{
    delete ui;
}
