/****************************************************************************
** Meta object code from reading C++ file 'C_Main.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../C_Main.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'C_Main.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_C_Main_t {
    QByteArrayData data[18];
    char stringdata0[440];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_C_Main_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_C_Main_t qt_meta_stringdata_C_Main = {
    {
QT_MOC_LITERAL(0, 0, 6), // "C_Main"
QT_MOC_LITERAL(1, 7, 29), // "SLOT_ClosingScanseLidarWindow"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 31), // "SLOT_ClosingSlamwareLidarWindow"
QT_MOC_LITERAL(4, 70, 29), // "SLOT_ClosingCoreSlamHMIWindow"
QT_MOC_LITERAL(5, 100, 31), // "SLOT_ClosingCoreSlamPFHMIWindow"
QT_MOC_LITERAL(6, 132, 26), // "SLOT_ClosingCommandsWindow"
QT_MOC_LITERAL(7, 159, 28), // "SLOT_ClosingPathFinderWindow"
QT_MOC_LITERAL(8, 188, 40), // "SLOT_PeriodicCheckExitConditi..."
QT_MOC_LITERAL(9, 229, 30), // "on_btn_ShowScanseLidar_clicked"
QT_MOC_LITERAL(10, 260, 32), // "on_btn_ShowSlamwareLidar_clicked"
QT_MOC_LITERAL(11, 293, 27), // "on_btn_ShowCoreSlam_clicked"
QT_MOC_LITERAL(12, 321, 26), // "on_btn_ShowCommand_clicked"
QT_MOC_LITERAL(13, 348, 29), // "on_btn_ShowPathFinder_clicked"
QT_MOC_LITERAL(14, 378, 10), // "closeEvent"
QT_MOC_LITERAL(15, 389, 12), // "QCloseEvent*"
QT_MOC_LITERAL(16, 402, 7), // "ptEvent"
QT_MOC_LITERAL(17, 410, 29) // "on_btn_ShowCoreSlamPF_clicked"

    },
    "C_Main\0SLOT_ClosingScanseLidarWindow\0"
    "\0SLOT_ClosingSlamwareLidarWindow\0"
    "SLOT_ClosingCoreSlamHMIWindow\0"
    "SLOT_ClosingCoreSlamPFHMIWindow\0"
    "SLOT_ClosingCommandsWindow\0"
    "SLOT_ClosingPathFinderWindow\0"
    "SLOT_PeriodicCheckExitConditionsThenExit\0"
    "on_btn_ShowScanseLidar_clicked\0"
    "on_btn_ShowSlamwareLidar_clicked\0"
    "on_btn_ShowCoreSlam_clicked\0"
    "on_btn_ShowCommand_clicked\0"
    "on_btn_ShowPathFinder_clicked\0closeEvent\0"
    "QCloseEvent*\0ptEvent\0on_btn_ShowCoreSlamPF_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_C_Main[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    0,   86,    2, 0x08 /* Private */,
       5,    0,   87,    2, 0x08 /* Private */,
       6,    0,   88,    2, 0x08 /* Private */,
       7,    0,   89,    2, 0x08 /* Private */,
       8,    0,   90,    2, 0x08 /* Private */,
       9,    0,   91,    2, 0x08 /* Private */,
      10,    0,   92,    2, 0x08 /* Private */,
      11,    0,   93,    2, 0x08 /* Private */,
      12,    0,   94,    2, 0x08 /* Private */,
      13,    0,   95,    2, 0x08 /* Private */,
      14,    1,   96,    2, 0x08 /* Private */,
      17,    0,   99,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void,

       0        // eod
};

void C_Main::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        C_Main *_t = static_cast<C_Main *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SLOT_ClosingScanseLidarWindow(); break;
        case 1: _t->SLOT_ClosingSlamwareLidarWindow(); break;
        case 2: _t->SLOT_ClosingCoreSlamHMIWindow(); break;
        case 3: _t->SLOT_ClosingCoreSlamPFHMIWindow(); break;
        case 4: _t->SLOT_ClosingCommandsWindow(); break;
        case 5: _t->SLOT_ClosingPathFinderWindow(); break;
        case 6: _t->SLOT_PeriodicCheckExitConditionsThenExit(); break;
        case 7: _t->on_btn_ShowScanseLidar_clicked(); break;
        case 8: _t->on_btn_ShowSlamwareLidar_clicked(); break;
        case 9: _t->on_btn_ShowCoreSlam_clicked(); break;
        case 10: _t->on_btn_ShowCommand_clicked(); break;
        case 11: _t->on_btn_ShowPathFinder_clicked(); break;
        case 12: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 13: _t->on_btn_ShowCoreSlamPF_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject C_Main::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_C_Main.data,
    qt_meta_data_C_Main,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *C_Main::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *C_Main::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_C_Main.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int C_Main::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
