#include <QtCore>
#include <QtGui/QApplication>
#include "mainwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setWindowIcon(QIcon(":/resource/army-officer-icon.png"));

    MainWidget mainWidget;
    mainWidget.show();

    return a.exec();
}
