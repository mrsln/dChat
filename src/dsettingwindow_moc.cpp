/****************************************************************************
** Meta object code from reading C++ file 'dsettingwindow.h'
**
** Created: ?? 7. ??? 22:01:33 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dsettingwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dsettingwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_dSettingWindow[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      18,   16,   15,   15, 0x0a,
      51,   43,   15,   15, 0x0a,
      81,   75,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_dSettingWindow[] = {
    "dSettingWindow\0\0i\0opacityValueChanged(int)\0checked\0"
    "clickedSkinButton(bool)\0state\0stateChanged(int)\0"
};

const QMetaObject dSettingWindow::staticMetaObject = {
    { &dSetting::staticMetaObject, qt_meta_stringdata_dSettingWindow,
      qt_meta_data_dSettingWindow, 0 }
};

const QMetaObject *dSettingWindow::metaObject() const
{
    return &staticMetaObject;
}

void *dSettingWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dSettingWindow))
	return static_cast<void*>(const_cast<dSettingWindow*>(this));
    return dSetting::qt_metacast(_clname);
}

int dSettingWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = dSetting::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: opacityValueChanged(*reinterpret_cast< int*>(_a[1])); break;
        case 1: clickedSkinButton(*reinterpret_cast< bool*>(_a[1])); break;
        case 2: stateChanged(*reinterpret_cast< int*>(_a[1])); break;
        }
        _id -= 3;
    }
    return _id;
}