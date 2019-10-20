/****************************************************************************
** Meta object code from reading C++ file 'C_CoreSlam_HMI.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Algo/CoreSlam/C_CoreSlam_HMI.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'C_CoreSlam_HMI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_C_CoreSlam_HMI_t {
    QByteArrayData data[35];
    char stringdata0[542];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_C_CoreSlam_HMI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_C_CoreSlam_HMI_t qt_meta_stringdata_C_CoreSlam_HMI = {
    {
QT_MOC_LITERAL(0, 0, 14), // "C_CoreSlam_HMI"
QT_MOC_LITERAL(1, 15, 17), // "SIG_ClosingWindow"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 17), // "SIG_NewEstimation"
QT_MOC_LITERAL(4, 52, 8), // "posX__mm"
QT_MOC_LITERAL(5, 61, 8), // "posY__mm"
QT_MOC_LITERAL(6, 70, 13), // "posTheta__rad"
QT_MOC_LITERAL(7, 84, 8), // "uint8_t*"
QT_MOC_LITERAL(8, 93, 7), // "mapData"
QT_MOC_LITERAL(9, 101, 8), // "uint32_t"
QT_MOC_LITERAL(10, 110, 4), // "xMin"
QT_MOC_LITERAL(11, 115, 4), // "xMax"
QT_MOC_LITERAL(12, 120, 4), // "yMin"
QT_MOC_LITERAL(13, 125, 4), // "yMax"
QT_MOC_LITERAL(14, 130, 21), // "SLOT_StoreNewScanData"
QT_MOC_LITERAL(15, 152, 8), // "sensorId"
QT_MOC_LITERAL(16, 161, 9), // "uint32_t*"
QT_MOC_LITERAL(17, 171, 17), // "tabOfMeasures__mm"
QT_MOC_LITERAL(18, 189, 7), // "double*"
QT_MOC_LITERAL(19, 197, 18), // "tabOfMeasures__cos"
QT_MOC_LITERAL(20, 216, 18), // "tabOfMeasures__sin"
QT_MOC_LITERAL(21, 235, 12), // "nbOfMeasures"
QT_MOC_LITERAL(22, 248, 23), // "SLOT_ProcessNewScanData"
QT_MOC_LITERAL(23, 272, 10), // "closeEvent"
QT_MOC_LITERAL(24, 283, 12), // "QCloseEvent*"
QT_MOC_LITERAL(25, 296, 7), // "ptEvent"
QT_MOC_LITERAL(26, 304, 29), // "on_btn_ZoomDefaultMap_clicked"
QT_MOC_LITERAL(27, 334, 24), // "on_btn_CenterMap_clicked"
QT_MOC_LITERAL(28, 359, 25), // "on_btn_ZoomOutMap_clicked"
QT_MOC_LITERAL(29, 385, 24), // "on_btn_ZoomInMap_clicked"
QT_MOC_LITERAL(30, 410, 27), // "on_btn_MoveRightMap_clicked"
QT_MOC_LITERAL(31, 438, 26), // "on_btn_MoveLeftMap_clicked"
QT_MOC_LITERAL(32, 465, 26), // "on_btn_MoveDownMap_clicked"
QT_MOC_LITERAL(33, 492, 24), // "on_btn_MoveUpMap_clicked"
QT_MOC_LITERAL(34, 517, 24) // "on_btn_ResetSlam_clicked"

    },
    "C_CoreSlam_HMI\0SIG_ClosingWindow\0\0"
    "SIG_NewEstimation\0posX__mm\0posY__mm\0"
    "posTheta__rad\0uint8_t*\0mapData\0uint32_t\0"
    "xMin\0xMax\0yMin\0yMax\0SLOT_StoreNewScanData\0"
    "sensorId\0uint32_t*\0tabOfMeasures__mm\0"
    "double*\0tabOfMeasures__cos\0"
    "tabOfMeasures__sin\0nbOfMeasures\0"
    "SLOT_ProcessNewScanData\0closeEvent\0"
    "QCloseEvent*\0ptEvent\0on_btn_ZoomDefaultMap_clicked\0"
    "on_btn_CenterMap_clicked\0"
    "on_btn_ZoomOutMap_clicked\0"
    "on_btn_ZoomInMap_clicked\0"
    "on_btn_MoveRightMap_clicked\0"
    "on_btn_MoveLeftMap_clicked\0"
    "on_btn_MoveDownMap_clicked\0"
    "on_btn_MoveUpMap_clicked\0"
    "on_btn_ResetSlam_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_C_CoreSlam_HMI[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x06 /* Public */,
       3,    8,   85,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    5,  102,    2, 0x0a /* Public */,
      22,    0,  113,    2, 0x0a /* Public */,
      23,    1,  114,    2, 0x08 /* Private */,
      26,    0,  117,    2, 0x08 /* Private */,
      27,    0,  118,    2, 0x08 /* Private */,
      28,    0,  119,    2, 0x08 /* Private */,
      29,    0,  120,    2, 0x08 /* Private */,
      30,    0,  121,    2, 0x08 /* Private */,
      31,    0,  122,    2, 0x08 /* Private */,
      32,    0,  123,    2, 0x08 /* Private */,
      33,    0,  124,    2, 0x08 /* Private */,
      34,    0,  125,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, 0x80000000 | 7, 0x80000000 | 9, 0x80000000 | 9, 0x80000000 | 9, 0x80000000 | 9,    4,    5,    6,    8,   10,   11,   12,   13,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 16, 0x80000000 | 18, 0x80000000 | 18, 0x80000000 | 9,   15,   17,   19,   20,   21,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 24,   25,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void C_CoreSlam_HMI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        C_CoreSlam_HMI *_t = static_cast<C_CoreSlam_HMI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SIG_ClosingWindow(); break;
        case 1: _t->SIG_NewEstimation((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< uint8_t*(*)>(_a[4])),(*reinterpret_cast< uint32_t(*)>(_a[5])),(*reinterpret_cast< uint32_t(*)>(_a[6])),(*reinterpret_cast< uint32_t(*)>(_a[7])),(*reinterpret_cast< uint32_t(*)>(_a[8]))); break;
        case 2: _t->SLOT_StoreNewScanData((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< uint32_t*(*)>(_a[2])),(*reinterpret_cast< double*(*)>(_a[3])),(*reinterpret_cast< double*(*)>(_a[4])),(*reinterpret_cast< uint32_t(*)>(_a[5]))); break;
        case 3: _t->SLOT_ProcessNewScanData(); break;
        case 4: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 5: _t->on_btn_ZoomDefaultMap_clicked(); break;
        case 6: _t->on_btn_CenterMap_clicked(); break;
        case 7: _t->on_btn_ZoomOutMap_clicked(); break;
        case 8: _t->on_btn_ZoomInMap_clicked(); break;
        case 9: _t->on_btn_MoveRightMap_clicked(); break;
        case 10: _t->on_btn_MoveLeftMap_clicked(); break;
        case 11: _t->on_btn_MoveDownMap_clicked(); break;
        case 12: _t->on_btn_MoveUpMap_clicked(); break;
        case 13: _t->on_btn_ResetSlam_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (C_CoreSlam_HMI::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&C_CoreSlam_HMI::SIG_ClosingWindow)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (C_CoreSlam_HMI::*)(double , double , double , uint8_t * , uint32_t , uint32_t , uint32_t , uint32_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&C_CoreSlam_HMI::SIG_NewEstimation)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject C_CoreSlam_HMI::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_C_CoreSlam_HMI.data,
    qt_meta_data_C_CoreSlam_HMI,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *C_CoreSlam_HMI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *C_CoreSlam_HMI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_C_CoreSlam_HMI.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int C_CoreSlam_HMI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void C_CoreSlam_HMI::SIG_ClosingWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void C_CoreSlam_HMI::SIG_NewEstimation(double _t1, double _t2, double _t3, uint8_t * _t4, uint32_t _t5, uint32_t _t6, uint32_t _t7, uint32_t _t8)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)), const_cast<void*>(reinterpret_cast<const void*>(&_t7)), const_cast<void*>(reinterpret_cast<const void*>(&_t8)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
