/****************************************************************************
** Meta object code from reading C++ file 'ditemdelegate.h'
**
** Created: ?? 21. ??? 13:02:02 2005
**      by: The Qt Meta Object Compiler version 58 (Qt 4.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ditemdelegate.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ditemdelegate.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 58
#error "This file was generated using the moc from 4.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_UserItemDelegate[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_UserItemDelegate[] = {
    "UserItemDelegate\0"
};

const QMetaObject UserItemDelegate::staticMetaObject = {
    { &QItemDelegate::staticMetaObject, qt_meta_stringdata_UserItemDelegate,
      qt_meta_data_UserItemDelegate, 0 }
};

const QMetaObject *UserItemDelegate::metaObject() const
{
    return &staticMetaObject;
}

void *UserItemDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UserItemDelegate))
	return static_cast<void*>(const_cast<UserItemDelegate*>(this));
    return QItemDelegate::qt_metacast(_clname);
}

int UserItemDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QItemDelegate::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
