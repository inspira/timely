#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

#include <QSystemTrayIcon>

class QMenu;

class BrowserWindow;

namespace Ui {
    class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

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

    BrowserWindow *browser;

private slots:
    void on_btnBrowser_clicked();
    void trayIconClicked(QSystemTrayIcon::ActivationReason);
};

#endif // MAINWIDGET_H
