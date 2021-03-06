#include <QtCore>
#include <QtGui/QApplication>
#include "mainwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#ifdef Q_WS_MAC

    a.setWindowIcon(QIcon(":/resource/army-officer-icon.png"));

#endif

#ifdef QT_MAC_USE_COCOA

    qDebug() << "Using the Cocoa MAC OS API";

#endif

    MainWidget mainWidget;
    mainWidget.show();

    return a.exec();
}
