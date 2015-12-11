/****************************************************************************
** Meta object code from reading C++ file 'view_cube.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../common/inc/view_cube.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'view_cube.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_parview__cube_t {
    QByteArrayData data[4];
    char stringdata[37];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_parview__cube_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_parview__cube_t qt_meta_stringdata_parview__cube = {
    {
QT_MOC_LITERAL(0, 0, 13), // "parview::cube"
QT_MOC_LITERAL(1, 14, 8), // "Click_ok"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 12) // "Click_cancel"

    },
    "parview::cube\0Click_ok\0\0Click_cancel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_parview__cube[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x08 /* Private */,
       3,    0,   25,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void parview::cube::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        cube *_t = static_cast<cube *>(_o);
        switch (_id) {
        case 0: _t->Click_ok(); break;
        case 1: _t->Click_cancel(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject parview::cube::staticMetaObject = {
    { &Object::staticMetaObject, qt_meta_stringdata_parview__cube.data,
      qt_meta_data_parview__cube,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *parview::cube::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *parview::cube::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_parview__cube.stringdata))
        return static_cast<void*>(const_cast< cube*>(this));
    return Object::qt_metacast(_clname);
}

int parview::cube::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Object::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
