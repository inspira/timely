/********************************************************************************
** Form generated from reading UI file 'mainwidget.ui'
**
** Created: Thu Dec 23 00:50:21 2010
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIDGET_H
#define UI_MAINWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWidget
{
public:
    QTabWidget *tabWidget;
    QWidget *tabMain;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *lblWelcome;
    QComboBox *cmbProjects;
    QTextEdit *txtDescription;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *txtRunningTime;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnPlayPause;
    QPushButton *btnPause;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QDoubleSpinBox *sbHours;
    QPushButton *btnSave;
    QWidget *tabOptions;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *txtApiKey;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QLineEdit *txtBasecamp;
    QPushButton *btnSaveConfiguration;

    void setupUi(QWidget *MainWidget)
    {
        if (MainWidget->objectName().isEmpty())
            MainWidget->setObjectName(QString::fromUtf8("MainWidget"));
        MainWidget->resize(384, 286);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWidget->sizePolicy().hasHeightForWidth());
        MainWidget->setSizePolicy(sizePolicy);
        MainWidget->setMinimumSize(QSize(384, 286));
        MainWidget->setMaximumSize(QSize(384, 286));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resource/army-officer-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWidget->setWindowIcon(icon);
        tabWidget = new QTabWidget(MainWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 364, 271));
        tabMain = new QWidget();
        tabMain->setObjectName(QString::fromUtf8("tabMain"));
        layoutWidget = new QWidget(tabMain);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 341, 225));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lblWelcome = new QLabel(layoutWidget);
        lblWelcome->setObjectName(QString::fromUtf8("lblWelcome"));

        verticalLayout->addWidget(lblWelcome);

        cmbProjects = new QComboBox(layoutWidget);
        cmbProjects->setObjectName(QString::fromUtf8("cmbProjects"));
        cmbProjects->setEnabled(false);

        verticalLayout->addWidget(cmbProjects);

        txtDescription = new QTextEdit(layoutWidget);
        txtDescription->setObjectName(QString::fromUtf8("txtDescription"));

        verticalLayout->addWidget(txtDescription);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        txtRunningTime = new QLineEdit(layoutWidget);
        txtRunningTime->setObjectName(QString::fromUtf8("txtRunningTime"));
        txtRunningTime->setReadOnly(true);

        horizontalLayout_4->addWidget(txtRunningTime);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        btnPlayPause = new QPushButton(layoutWidget);
        btnPlayPause->setObjectName(QString::fromUtf8("btnPlayPause"));
        btnPlayPause->setEnabled(false);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/resource/Player Play.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPlayPause->setIcon(icon1);

        horizontalLayout_3->addWidget(btnPlayPause);

        btnPause = new QPushButton(layoutWidget);
        btnPause->setObjectName(QString::fromUtf8("btnPause"));
        btnPause->setEnabled(false);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/resource/Player Pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPause->setIcon(icon2);

        horizontalLayout_3->addWidget(btnPause);


        horizontalLayout_4->addLayout(horizontalLayout_3);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        sbHours = new QDoubleSpinBox(layoutWidget);
        sbHours->setObjectName(QString::fromUtf8("sbHours"));

        horizontalLayout_2->addWidget(sbHours);

        btnSave = new QPushButton(layoutWidget);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));

        horizontalLayout_2->addWidget(btnSave);


        verticalLayout->addLayout(horizontalLayout_2);

        tabWidget->addTab(tabMain, QString());
        tabOptions = new QWidget();
        tabOptions->setObjectName(QString::fromUtf8("tabOptions"));
        verticalLayoutWidget_2 = new QWidget(tabOptions);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(10, 10, 341, 101));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(verticalLayoutWidget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        txtApiKey = new QLineEdit(verticalLayoutWidget_2);
        txtApiKey->setObjectName(QString::fromUtf8("txtApiKey"));

        horizontalLayout->addWidget(txtApiKey);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_3 = new QLabel(verticalLayoutWidget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_5->addWidget(label_3);

        txtBasecamp = new QLineEdit(verticalLayoutWidget_2);
        txtBasecamp->setObjectName(QString::fromUtf8("txtBasecamp"));

        horizontalLayout_5->addWidget(txtBasecamp);


        verticalLayout_2->addLayout(horizontalLayout_5);

        btnSaveConfiguration = new QPushButton(verticalLayoutWidget_2);
        btnSaveConfiguration->setObjectName(QString::fromUtf8("btnSaveConfiguration"));

        verticalLayout_2->addWidget(btnSaveConfiguration);

        tabWidget->addTab(tabOptions, QString());

        retranslateUi(MainWidget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWidget);
    } // setupUi

    void retranslateUi(QWidget *MainWidget)
    {
        MainWidget->setWindowTitle(QApplication::translate("MainWidget", "Timely", 0, QApplication::UnicodeUTF8));
        lblWelcome->setText(QApplication::translate("MainWidget", "Welcome,", 0, QApplication::UnicodeUTF8));
        btnPlayPause->setText(QString());
        btnPause->setText(QString());
        label->setText(QApplication::translate("MainWidget", "Hours", 0, QApplication::UnicodeUTF8));
        btnSave->setText(QApplication::translate("MainWidget", "Save", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabMain), QApplication::translate("MainWidget", "Main", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWidget", "Api key:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWidget", "Basecamp url:", 0, QApplication::UnicodeUTF8));
        btnSaveConfiguration->setText(QApplication::translate("MainWidget", "Save", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabOptions), QApplication::translate("MainWidget", "Settings", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWidget: public Ui_MainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
