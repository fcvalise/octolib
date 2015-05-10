/****************************************************************************
** Meta object code from reading C++ file 'WheelEditor.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../WheelEditor.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WheelEditor.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_WheelEditor_t {
    QByteArrayData data[24];
    char stringdata[257];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WheelEditor_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WheelEditor_t qt_meta_stringdata_WheelEditor = {
    {
QT_MOC_LITERAL(0, 0, 11), // "WheelEditor"
QT_MOC_LITERAL(1, 12, 8), // "modified"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 16), // "selectionChanged"
QT_MOC_LITERAL(4, 39, 8), // "newWheel"
QT_MOC_LITERAL(5, 48, 9), // "saveWheel"
QT_MOC_LITERAL(6, 58, 8), // "filePath"
QT_MOC_LITERAL(7, 67, 9), // "openWheel"
QT_MOC_LITERAL(8, 77, 9), // "addOffset"
QT_MOC_LITERAL(9, 87, 6), // "offset"
QT_MOC_LITERAL(10, 94, 13), // "addAnaloguous"
QT_MOC_LITERAL(11, 108, 8), // "QWidget*"
QT_MOC_LITERAL(12, 117, 6), // "parent"
QT_MOC_LITERAL(13, 124, 18), // "addComplementaries"
QT_MOC_LITERAL(14, 143, 8), // "addTriad"
QT_MOC_LITERAL(15, 152, 9), // "addSquare"
QT_MOC_LITERAL(16, 162, 13), // "removeCurrent"
QT_MOC_LITERAL(17, 176, 9), // "removeAll"
QT_MOC_LITERAL(18, 186, 12), // "hasSelection"
QT_MOC_LITERAL(19, 199, 7), // "isEmpty"
QT_MOC_LITERAL(20, 207, 16), // "onCurrentChanged"
QT_MOC_LITERAL(21, 224, 7), // "current"
QT_MOC_LITERAL(22, 232, 14), // "onOffsetEdited"
QT_MOC_LITERAL(23, 247, 9) // "HueOffset"

    },
    "WheelEditor\0modified\0\0selectionChanged\0"
    "newWheel\0saveWheel\0filePath\0openWheel\0"
    "addOffset\0offset\0addAnaloguous\0QWidget*\0"
    "parent\0addComplementaries\0addTriad\0"
    "addSquare\0removeCurrent\0removeAll\0"
    "hasSelection\0isEmpty\0onCurrentChanged\0"
    "current\0onOffsetEdited\0HueOffset"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WheelEditor[] = {

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
       8,    1,  108,    2, 0x0a /* Public */,
       8,    0,  111,    2, 0x2a /* Public | MethodCloned */,
      10,    1,  112,    2, 0x0a /* Public */,
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
    QMetaType::Void, QMetaType::UShort,    9,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::QModelIndex, QMetaType::QModelIndex,   21,    2,
    QMetaType::Void, 0x80000000 | 23,    9,

       0        // eod
};

void WheelEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WheelEditor *_t = static_cast<WheelEditor *>(_o);
        switch (_id) {
        case 0: _t->modified(); break;
        case 1: _t->selectionChanged(); break;
        case 2: _t->newWheel(); break;
        case 3: _t->saveWheel((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->openWheel((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->addOffset((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 6: _t->addOffset(); break;
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
        case 16: _t->onOffsetEdited((*reinterpret_cast< const HueOffset(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
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
            typedef void (WheelEditor::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WheelEditor::modified)) {
                *result = 0;
            }
        }
        {
            typedef void (WheelEditor::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WheelEditor::selectionChanged)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject WheelEditor::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_WheelEditor.data,
      qt_meta_data_WheelEditor,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *WheelEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WheelEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_WheelEditor.stringdata))
        return static_cast<void*>(const_cast< WheelEditor*>(this));
    return QWidget::qt_metacast(_clname);
}

int WheelEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void WheelEditor::modified()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void WheelEditor::selectionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
