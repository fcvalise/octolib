/****************************************************************************
** Meta object code from reading C++ file 'PaletteFromImageDialog.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PaletteEditor/PaletteFromImageDialog.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PaletteFromImageDialog.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PaletteFromImageDialog_t {
    QByteArrayData data[6];
    char stringdata[59];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PaletteFromImageDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PaletteFromImageDialog_t qt_meta_stringdata_PaletteFromImageDialog = {
    {
QT_MOC_LITERAL(0, 0, 22), // "PaletteFromImageDialog"
QT_MOC_LITERAL(1, 23, 4), // "exec"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 9), // "loadImage"
QT_MOC_LITERAL(4, 39, 13), // "setColorCount"
QT_MOC_LITERAL(5, 53, 5) // "count"

    },
    "PaletteFromImageDialog\0exec\0\0loadImage\0"
    "setColorCount\0count"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PaletteFromImageDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    0,   30,    2, 0x08 /* Private */,
       4,    1,   31,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,

       0        // eod
};

void PaletteFromImageDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PaletteFromImageDialog *_t = static_cast<PaletteFromImageDialog *>(_o);
        switch (_id) {
        case 0: { int _r = _t->exec();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 1: _t->loadImage(); break;
        case 2: _t->setColorCount((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject PaletteFromImageDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_PaletteFromImageDialog.data,
      qt_meta_data_PaletteFromImageDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PaletteFromImageDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PaletteFromImageDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PaletteFromImageDialog.stringdata))
        return static_cast<void*>(const_cast< PaletteFromImageDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int PaletteFromImageDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
