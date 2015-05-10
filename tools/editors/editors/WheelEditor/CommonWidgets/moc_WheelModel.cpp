/****************************************************************************
** Meta object code from reading C++ file 'WheelModel.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CommonWidgets/WheelModel.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WheelModel.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_WheelModel_t {
    QByteArrayData data[13];
    char stringdata[102];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WheelModel_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WheelModel_t qt_meta_stringdata_WheelModel = {
    {
QT_MOC_LITERAL(0, 0, 10), // "WheelModel"
QT_MOC_LITERAL(1, 11, 6), // "setHue"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 3), // "hue"
QT_MOC_LITERAL(4, 23, 9), // "addOffset"
QT_MOC_LITERAL(5, 33, 6), // "offset"
QT_MOC_LITERAL(6, 40, 10), // "saturation"
QT_MOC_LITERAL(7, 51, 5), // "value"
QT_MOC_LITERAL(8, 57, 5), // "alpha"
QT_MOC_LITERAL(9, 63, 9), // "HueOffset"
QT_MOC_LITERAL(10, 73, 12), // "removeOffset"
QT_MOC_LITERAL(11, 86, 5), // "index"
QT_MOC_LITERAL(12, 92, 9) // "removeAll"

    },
    "WheelModel\0setHue\0\0hue\0addOffset\0"
    "offset\0saturation\0value\0alpha\0HueOffset\0"
    "removeOffset\0index\0removeAll"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WheelModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x0a /* Public */,
       4,    4,   57,    2, 0x0a /* Public */,
       4,    3,   66,    2, 0x2a /* Public | MethodCloned */,
       4,    2,   73,    2, 0x2a /* Public | MethodCloned */,
       4,    1,   78,    2, 0x2a /* Public | MethodCloned */,
       4,    1,   81,    2, 0x0a /* Public */,
      10,    1,   84,    2, 0x0a /* Public */,
      12,    0,   87,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::QModelIndex, QMetaType::Short, QMetaType::UChar, QMetaType::UChar, QMetaType::UChar,    5,    6,    7,    8,
    QMetaType::QModelIndex, QMetaType::Short, QMetaType::UChar, QMetaType::UChar,    5,    6,    7,
    QMetaType::QModelIndex, QMetaType::Short, QMetaType::UChar,    5,    6,
    QMetaType::QModelIndex, QMetaType::Short,    5,
    QMetaType::QModelIndex, 0x80000000 | 9,    5,
    QMetaType::Void, QMetaType::QModelIndex,   11,
    QMetaType::Void,

       0        // eod
};

void WheelModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WheelModel *_t = static_cast<WheelModel *>(_o);
        switch (_id) {
        case 0: _t->setHue((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 1: { QModelIndex _r = _t->addOffset((*reinterpret_cast< qint16(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2])),(*reinterpret_cast< quint8(*)>(_a[3])),(*reinterpret_cast< quint8(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< QModelIndex*>(_a[0]) = _r; }  break;
        case 2: { QModelIndex _r = _t->addOffset((*reinterpret_cast< qint16(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2])),(*reinterpret_cast< quint8(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QModelIndex*>(_a[0]) = _r; }  break;
        case 3: { QModelIndex _r = _t->addOffset((*reinterpret_cast< qint16(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QModelIndex*>(_a[0]) = _r; }  break;
        case 4: { QModelIndex _r = _t->addOffset((*reinterpret_cast< qint16(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QModelIndex*>(_a[0]) = _r; }  break;
        case 5: { QModelIndex _r = _t->addOffset((*reinterpret_cast< const HueOffset(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QModelIndex*>(_a[0]) = _r; }  break;
        case 6: _t->removeOffset((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 7: _t->removeAll(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< HueOffset >(); break;
            }
            break;
        }
    }
}

const QMetaObject WheelModel::staticMetaObject = {
    { &QAbstractTableModel::staticMetaObject, qt_meta_stringdata_WheelModel.data,
      qt_meta_data_WheelModel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *WheelModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WheelModel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_WheelModel.stringdata))
        return static_cast<void*>(const_cast< WheelModel*>(this));
    return QAbstractTableModel::qt_metacast(_clname);
}

int WheelModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
