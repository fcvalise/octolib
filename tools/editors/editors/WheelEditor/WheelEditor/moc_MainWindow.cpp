/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MainWindow.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[17];
    char stringdata[200];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 8), // "newWheel"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 9), // "openWheel"
QT_MOC_LITERAL(4, 31, 8), // "filePath"
QT_MOC_LITERAL(5, 40, 9), // "saveWheel"
QT_MOC_LITERAL(6, 50, 11), // "saveWheelAs"
QT_MOC_LITERAL(7, 62, 9), // "addOffset"
QT_MOC_LITERAL(8, 72, 13), // "addAnaloguous"
QT_MOC_LITERAL(9, 86, 18), // "addComplementaries"
QT_MOC_LITERAL(10, 105, 8), // "addTriad"
QT_MOC_LITERAL(11, 114, 9), // "addSquare"
QT_MOC_LITERAL(12, 124, 12), // "deleteOffset"
QT_MOC_LITERAL(13, 137, 16), // "deleteAllOffsets"
QT_MOC_LITERAL(14, 154, 9), // "showAbout"
QT_MOC_LITERAL(15, 164, 12), // "updateAction"
QT_MOC_LITERAL(16, 177, 22) // "onDocumentFileModified"

    },
    "MainWindow\0newWheel\0\0openWheel\0filePath\0"
    "saveWheel\0saveWheelAs\0addOffset\0"
    "addAnaloguous\0addComplementaries\0"
    "addTriad\0addSquare\0deleteOffset\0"
    "deleteAllOffsets\0showAbout\0updateAction\0"
    "onDocumentFileModified"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x08 /* Private */,
       3,    0,   90,    2, 0x08 /* Private */,
       3,    1,   91,    2, 0x08 /* Private */,
       5,    0,   94,    2, 0x08 /* Private */,
       6,    0,   95,    2, 0x08 /* Private */,
       7,    0,   96,    2, 0x08 /* Private */,
       8,    0,   97,    2, 0x08 /* Private */,
       9,    0,   98,    2, 0x08 /* Private */,
      10,    0,   99,    2, 0x08 /* Private */,
      11,    0,  100,    2, 0x08 /* Private */,
      12,    0,  101,    2, 0x08 /* Private */,
      13,    0,  102,    2, 0x08 /* Private */,
      14,    0,  103,    2, 0x08 /* Private */,
      15,    0,  104,    2, 0x08 /* Private */,
      16,    0,  105,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Bool,
    QMetaType::Bool,
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

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->newWheel(); break;
        case 1: _t->openWheel(); break;
        case 2: _t->openWheel((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: { bool _r = _t->saveWheel();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: { bool _r = _t->saveWheelAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: _t->addOffset(); break;
        case 6: _t->addAnaloguous(); break;
        case 7: _t->addComplementaries(); break;
        case 8: _t->addTriad(); break;
        case 9: _t->addSquare(); break;
        case 10: _t->deleteOffset(); break;
        case 11: _t->deleteAllOffsets(); break;
        case 12: _t->showAbout(); break;
        case 13: _t->updateAction(); break;
        case 14: _t->onDocumentFileModified(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
