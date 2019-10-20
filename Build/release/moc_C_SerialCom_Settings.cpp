/****************************************************************************
** Meta object code from reading C++ file 'C_SerialCom_Settings.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Drivers/Basic/SerialCom/C_SerialCom_Settings.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'C_SerialCom_Settings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_C_SerialCom_Settings_t {
    QByteArrayData data[7];
    char stringdata0[127];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_C_SerialCom_Settings_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_C_SerialCom_Settings_t qt_meta_stringdata_C_SerialCom_Settings = {
    {
QT_MOC_LITERAL(0, 0, 20), // "C_SerialCom_Settings"
QT_MOC_LITERAL(1, 21, 17), // "SLOT_ShowPortInfo"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 3), // "idx"
QT_MOC_LITERAL(4, 44, 18), // "SLOT_ApplySettings"
QT_MOC_LITERAL(5, 63, 30), // "SLOT_CheckCustomBaudRatePolicy"
QT_MOC_LITERAL(6, 94, 32) // "SLOT_CheckCustomDevicePathPolicy"

    },
    "C_SerialCom_Settings\0SLOT_ShowPortInfo\0"
    "\0idx\0SLOT_ApplySettings\0"
    "SLOT_CheckCustomBaudRatePolicy\0"
    "SLOT_CheckCustomDevicePathPolicy"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_C_SerialCom_Settings[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x08 /* Private */,
       4,    0,   37,    2, 0x08 /* Private */,
       5,    1,   38,    2, 0x08 /* Private */,
       6,    1,   41,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void C_SerialCom_Settings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        C_SerialCom_Settings *_t = static_cast<C_SerialCom_Settings *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SLOT_ShowPortInfo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->SLOT_ApplySettings(); break;
        case 2: _t->SLOT_CheckCustomBaudRatePolicy((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->SLOT_CheckCustomDevicePathPolicy((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject C_SerialCom_Settings::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_C_SerialCom_Settings.data,
    qt_meta_data_C_SerialCom_Settings,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *C_SerialCom_Settings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *C_SerialCom_Settings::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_C_SerialCom_Settings.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int C_SerialCom_Settings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
