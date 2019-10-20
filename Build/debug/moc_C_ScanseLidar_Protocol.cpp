/****************************************************************************
** Meta object code from reading C++ file 'C_ScanseLidar_Protocol.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Drivers/Basic/ScanseLidar/C_ScanseLidar_Protocol.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'C_ScanseLidar_Protocol.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_C_ScanseLidar_Protocol_t {
    QByteArrayData data[14];
    char stringdata0[198];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_C_ScanseLidar_Protocol_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_C_ScanseLidar_Protocol_t qt_meta_stringdata_C_ScanseLidar_Protocol = {
    {
QT_MOC_LITERAL(0, 0, 22), // "C_ScanseLidar_Protocol"
QT_MOC_LITERAL(1, 23, 16), // "SIG_NewLidarData"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 8), // "sensorId"
QT_MOC_LITERAL(4, 50, 9), // "uint32_t*"
QT_MOC_LITERAL(5, 60, 17), // "tabOfMeasures__mm"
QT_MOC_LITERAL(6, 78, 7), // "double*"
QT_MOC_LITERAL(7, 86, 18), // "tabOfMeasures__cos"
QT_MOC_LITERAL(8, 105, 18), // "tabOfMeasures__sin"
QT_MOC_LITERAL(9, 124, 8), // "uint32_t"
QT_MOC_LITERAL(10, 133, 12), // "nbOfMeasures"
QT_MOC_LITERAL(11, 146, 21), // "SLOT_ManageConnection"
QT_MOC_LITERAL(12, 168, 24), // "SLOT_ProcessReceivedData"
QT_MOC_LITERAL(13, 193, 4) // "data"

    },
    "C_ScanseLidar_Protocol\0SIG_NewLidarData\0"
    "\0sensorId\0uint32_t*\0tabOfMeasures__mm\0"
    "double*\0tabOfMeasures__cos\0"
    "tabOfMeasures__sin\0uint32_t\0nbOfMeasures\0"
    "SLOT_ManageConnection\0SLOT_ProcessReceivedData\0"
    "data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_C_ScanseLidar_Protocol[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    5,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   40,    2, 0x08 /* Private */,
      12,    1,   41,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4, 0x80000000 | 6, 0x80000000 | 6, 0x80000000 | 9,    3,    5,    7,    8,   10,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   13,

       0        // eod
};

void C_ScanseLidar_Protocol::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        C_ScanseLidar_Protocol *_t = static_cast<C_ScanseLidar_Protocol *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SIG_NewLidarData((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< uint32_t*(*)>(_a[2])),(*reinterpret_cast< double*(*)>(_a[3])),(*reinterpret_cast< double*(*)>(_a[4])),(*reinterpret_cast< uint32_t(*)>(_a[5]))); break;
        case 1: _t->SLOT_ManageConnection(); break;
        case 2: _t->SLOT_ProcessReceivedData((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (C_ScanseLidar_Protocol::*)(int , uint32_t * , double * , double * , uint32_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&C_ScanseLidar_Protocol::SIG_NewLidarData)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject C_ScanseLidar_Protocol::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_C_ScanseLidar_Protocol.data,
    qt_meta_data_C_ScanseLidar_Protocol,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *C_ScanseLidar_Protocol::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *C_ScanseLidar_Protocol::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_C_ScanseLidar_Protocol.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int C_ScanseLidar_Protocol::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void C_ScanseLidar_Protocol::SIG_NewLidarData(int _t1, uint32_t * _t2, double * _t3, double * _t4, uint32_t _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
