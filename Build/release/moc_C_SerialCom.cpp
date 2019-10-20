/****************************************************************************
** Meta object code from reading C++ file 'C_SerialCom.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Drivers/Basic/SerialCom/C_SerialCom.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'C_SerialCom.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_C_SerialCom_t {
    QByteArrayData data[15];
    char stringdata0[216];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_C_SerialCom_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_C_SerialCom_t qt_meta_stringdata_C_SerialCom = {
    {
QT_MOC_LITERAL(0, 0, 11), // "C_SerialCom"
QT_MOC_LITERAL(1, 12, 17), // "SIG_ClosingWindow"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 19), // "SIG_NewDataReceived"
QT_MOC_LITERAL(4, 51, 4), // "data"
QT_MOC_LITERAL(5, 56, 12), // "SLOT_Connect"
QT_MOC_LITERAL(6, 69, 15), // "SLOT_Disconnect"
QT_MOC_LITERAL(7, 85, 21), // "SLOT_ReadDataFromPort"
QT_MOC_LITERAL(8, 107, 20), // "SLOT_HandlePortError"
QT_MOC_LITERAL(9, 128, 28), // "QSerialPort::SerialPortError"
QT_MOC_LITERAL(10, 157, 5), // "error"
QT_MOC_LITERAL(11, 163, 20), // "SLOT_WriteDataToPort"
QT_MOC_LITERAL(12, 184, 10), // "closeEvent"
QT_MOC_LITERAL(13, 195, 12), // "QCloseEvent*"
QT_MOC_LITERAL(14, 208, 7) // "ptEvent"

    },
    "C_SerialCom\0SIG_ClosingWindow\0\0"
    "SIG_NewDataReceived\0data\0SLOT_Connect\0"
    "SLOT_Disconnect\0SLOT_ReadDataFromPort\0"
    "SLOT_HandlePortError\0QSerialPort::SerialPortError\0"
    "error\0SLOT_WriteDataToPort\0closeEvent\0"
    "QCloseEvent*\0ptEvent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_C_SerialCom[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    1,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   58,    2, 0x08 /* Private */,
       6,    0,   59,    2, 0x08 /* Private */,
       7,    0,   60,    2, 0x08 /* Private */,
       8,    1,   61,    2, 0x08 /* Private */,
      11,    1,   64,    2, 0x08 /* Private */,
      12,    1,   67,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, QMetaType::QByteArray,    4,
    QMetaType::Void, 0x80000000 | 13,   14,

       0        // eod
};

void C_SerialCom::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        C_SerialCom *_t = static_cast<C_SerialCom *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SIG_ClosingWindow(); break;
        case 1: _t->SIG_NewDataReceived((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 2: _t->SLOT_Connect(); break;
        case 3: _t->SLOT_Disconnect(); break;
        case 4: _t->SLOT_ReadDataFromPort(); break;
        case 5: _t->SLOT_HandlePortError((*reinterpret_cast< QSerialPort::SerialPortError(*)>(_a[1]))); break;
        case 6: _t->SLOT_WriteDataToPort((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 7: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (C_SerialCom::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&C_SerialCom::SIG_ClosingWindow)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (C_SerialCom::*)(const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&C_SerialCom::SIG_NewDataReceived)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject C_SerialCom::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_C_SerialCom.data,
    qt_meta_data_C_SerialCom,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *C_SerialCom::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *C_SerialCom::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_C_SerialCom.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int C_SerialCom::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void C_SerialCom::SIG_ClosingWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void C_SerialCom::SIG_NewDataReceived(const QByteArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
