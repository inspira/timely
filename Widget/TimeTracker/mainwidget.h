#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QSystemTrayIcon>

#include "ICallback.h"

class QMenu;
class Caller;

class BrowserWindow;

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

    Ui::MainWidget *ui;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    QAction *open;
    QAction *close;

    Caller *caller;


private slots:
    void on_btnSave_clicked();
    void trayIconClicked(QSystemTrayIcon::ActivationReason);
};

#endif // MAINWIDGET_H
