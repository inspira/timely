/****************************************************************************
** Meta object code from reading C++ file 'mainwidget.h'
**
** Created: Thu Dec 23 00:50:29 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      34,   11,   11,   11, 0x08,
      60,   11,   11,   11, 0x08,
      94,   11,   11,   11, 0x08,
     126,   11,   11,   11, 0x08,
     161,  155,   11,   11, 0x08,
     202,  155,   11,   11, 0x08,
     242,   11,   11,   11, 0x08,
     263,   11,   11,   11, 0x08,
     314,   11,   11,   11, 0x08,
     349,  342,   11,   11, 0x08,
     367,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWidget[] = {
    "MainWidget\0\0on_btnPause_clicked()\0"
    "on_btnPlayPause_clicked()\0"
    "on_btnSaveConfiguration_clicked()\0"
    "on_sbHours_valueChanged(double)\0"
    "on_sbHours_editingFinished()\0index\0"
    "on_cmbCompanies_currentIndexChanged(int)\0"
    "on_cmbProjects_currentIndexChanged(int)\0"
    "on_btnSave_clicked()\0"
    "trayIconClicked(QSystemTrayIcon::ActivationReason)\0"
    "gotProjects(QList<Project>)\0person\0"
    "gotPerson(Person)\0updateTime()\0"
};

const QMetaObject MainWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainWidget,
      qt_meta_data_MainWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWidget))
        return static_cast<void*>(const_cast< MainWidget*>(this));
    if (!strcmp(_clname, "ICallback"))
        return static_cast< ICallback*>(const_cast< MainWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int MainWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_btnPause_clicked(); break;
        case 1: on_btnPlayPause_clicked(); break;
        case 2: on_btnSaveConfiguration_clicked(); break;
        case 3: on_sbHours_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: on_sbHours_editingFinished(); break;
        case 5: on_cmbCompanies_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: on_cmbProjects_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: on_btnSave_clicked(); break;
        case 8: trayIconClicked((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 9: gotProjects((*reinterpret_cast< QList<Project>(*)>(_a[1]))); break;
        case 10: gotPerson((*reinterpret_cast< Person(*)>(_a[1]))); break;
        case 11: updateTime(); break;
        default: ;
        }
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
