/****************************************************************************
** Meta object code from reading C++ file 'PaletteModel.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CommonWidgets/PaletteModel.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PaletteModel.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PaletteModel_t {
    QByteArrayData data[7];
    char stringdata[57];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PaletteModel_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PaletteModel_t qt_meta_stringdata_PaletteModel = {
    {
QT_MOC_LITERAL(0, 0, 12), // "PaletteModel"
QT_MOC_LITERAL(1, 13, 8), // "addColor"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 5), // "color"
QT_MOC_LITERAL(4, 29, 11), // "removeColor"
QT_MOC_LITERAL(5, 41, 5), // "index"
QT_MOC_LITERAL(6, 47, 9) // "removeAll"

    },
    "PaletteModel\0addColor\0\0color\0removeColor\0"
    "index\0removeAll"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PaletteModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a /* Public */,
       1,    0,   37,    2, 0x2a /* Public | MethodCloned */,
       4,    1,   38,    2, 0x0a /* Public */,
       6,    0,   41,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::QModelIndex, QMetaType::QColor,    3,
    QMetaType::QModelIndex,
    QMetaType::Void, QMetaType::QModelIndex,    5,
    QMetaType::Void,

       0        // eod
};

void PaletteModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PaletteModel *_t = static_cast<PaletteModel *>(_o);
        switch (_id) {
        case 0: { QModelIndex _r = _t->addColor((*reinterpret_cast< QColor(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QModelIndex*>(_a[0]) = _r; }  break;
        case 1: { QModelIndex _r = _t->addColor();
            if (_a[0]) *reinterpret_cast< QModelIndex*>(_a[0]) = _r; }  break;
        case 2: _t->removeColor((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 3: _t->removeAll(); break;
        default: ;
        }
    }
}

const QMetaObject PaletteModel::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_PaletteModel.data,
      qt_meta_data_PaletteModel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PaletteModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PaletteModel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PaletteModel.stringdata))
        return static_cast<void*>(const_cast< PaletteModel*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int PaletteModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
