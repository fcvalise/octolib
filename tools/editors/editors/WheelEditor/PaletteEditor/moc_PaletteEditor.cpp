/****************************************************************************
** Meta object code from reading C++ file 'PaletteEditor.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PaletteEditor/PaletteEditor.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PaletteEditor.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PaletteEditor_t {
    QByteArrayData data[24];
    char stringdata[270];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PaletteEditor_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PaletteEditor_t qt_meta_stringdata_PaletteEditor = {
    {
QT_MOC_LITERAL(0, 0, 13), // "PaletteEditor"
QT_MOC_LITERAL(1, 14, 8), // "modified"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 16), // "selectionChanged"
QT_MOC_LITERAL(4, 41, 10), // "newPalette"
QT_MOC_LITERAL(5, 52, 11), // "savePalette"
QT_MOC_LITERAL(6, 64, 8), // "filePath"
QT_MOC_LITERAL(7, 73, 11), // "openPalette"
QT_MOC_LITERAL(8, 85, 8), // "addColor"
QT_MOC_LITERAL(9, 94, 17), // "addColorFromImage"
QT_MOC_LITERAL(10, 112, 8), // "QWidget*"
QT_MOC_LITERAL(11, 121, 6), // "parent"
QT_MOC_LITERAL(12, 128, 13), // "addAnaloguous"
QT_MOC_LITERAL(13, 142, 18), // "addComplementaries"
QT_MOC_LITERAL(14, 161, 8), // "addTriad"
QT_MOC_LITERAL(15, 170, 9), // "addSquare"
QT_MOC_LITERAL(16, 180, 13), // "removeCurrent"
QT_MOC_LITERAL(17, 194, 9), // "removeAll"
QT_MOC_LITERAL(18, 204, 12), // "hasSelection"
QT_MOC_LITERAL(19, 217, 7), // "isEmpty"
QT_MOC_LITERAL(20, 225, 16), // "onCurrentChanged"
QT_MOC_LITERAL(21, 242, 7), // "current"
QT_MOC_LITERAL(22, 250, 13), // "onColorEdited"
QT_MOC_LITERAL(23, 264, 5) // "color"

    },
    "PaletteEditor\0modified\0\0selectionChanged\0"
    "newPalette\0savePalette\0filePath\0"
    "openPalette\0addColor\0addColorFromImage\0"
    "QWidget*\0parent\0addAnaloguous\0"
    "addComplementaries\0addTriad\0addSquare\0"
    "removeCurrent\0removeAll\0hasSelection\0"
    "isEmpty\0onCurrentChanged\0current\0"
    "onColorEdited\0color"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PaletteEditor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x06 /* Public */,
       3,    0,  100,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,  101,    2, 0x0a /* Public */,
       5,    1,  102,    2, 0x0a /* Public */,
       7,    1,  105,    2, 0x0a /* Public */,
       8,    0,  108,    2, 0x0a /* Public */,
       9,    1,  109,    2, 0x0a /* Public */,
      12,    1,  112,    2, 0x0a /* Public */,
      13,    1,  115,    2, 0x0a /* Public */,
      14,    1,  118,    2, 0x0a /* Public */,
      15,    1,  121,    2, 0x0a /* Public */,
      16,    0,  124,    2, 0x0a /* Public */,
      17,    0,  125,    2, 0x0a /* Public */,
      18,    0,  126,    2, 0x0a /* Public */,
      19,    0,  127,    2, 0x0a /* Public */,
      20,    2,  128,    2, 0x08 /* Private */,
      22,    1,  133,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::QModelIndex, QMetaType::QModelIndex,   21,    2,
    QMetaType::Void, QMetaType::QColor,   23,

       0        // eod
};

void PaletteEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PaletteEditor *_t = static_cast<PaletteEditor *>(_o);
        switch (_id) {
        case 0: _t->modified(); break;
        case 1: _t->selectionChanged(); break;
        case 2: _t->newPalette(); break;
        case 3: _t->savePalette((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->openPalette((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->addColor(); break;
        case 6: _t->addColorFromImage((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 7: _t->addAnaloguous((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 8: _t->addComplementaries((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 9: _t->addTriad((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 10: _t->addSquare((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 11: _t->removeCurrent(); break;
        case 12: _t->removeAll(); break;
        case 13: { bool _r = _t->hasSelection();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 14: { bool _r = _t->isEmpty();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 15: _t->onCurrentChanged((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2]))); break;
        case 16: _t->onColorEdited((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PaletteEditor::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PaletteEditor::modified)) {
                *result = 0;
            }
        }
        {
            typedef void (PaletteEditor::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PaletteEditor::selectionChanged)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject PaletteEditor::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PaletteEditor.data,
      qt_meta_data_PaletteEditor,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PaletteEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PaletteEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PaletteEditor.stringdata))
        return static_cast<void*>(const_cast< PaletteEditor*>(this));
    return QWidget::qt_metacast(_clname);
}

int PaletteEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void PaletteEditor::modified()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void PaletteEditor::selectionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
