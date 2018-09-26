/****************************************************************************
** Meta object code from reading C++ file 'TableDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TableDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TableDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TableDialog_t {
    QByteArrayData data[7];
    char stringdata0[67];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TableDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TableDialog_t qt_meta_stringdata_TableDialog = {
    {
QT_MOC_LITERAL(0, 0, 11), // "TableDialog"
QT_MOC_LITERAL(1, 12, 10), // "OnFinished"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 8), // "OnCancel"
QT_MOC_LITERAL(4, 33, 15), // "OnPaddingChange"
QT_MOC_LITERAL(5, 49, 3), // "val"
QT_MOC_LITERAL(6, 53, 13) // "OnColorChange"

    },
    "TableDialog\0OnFinished\0\0OnCancel\0"
    "OnPaddingChange\0val\0OnColorChange"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TableDialog[] = {

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
       1,    0,   34,    2, 0x0a /* Public */,
       3,    0,   35,    2, 0x0a /* Public */,
       4,    1,   36,    2, 0x0a /* Public */,
       6,    0,   39,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,

       0        // eod
};

void TableDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TableDialog *_t = static_cast<TableDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnFinished(); break;
        case 1: _t->OnCancel(); break;
        case 2: _t->OnPaddingChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->OnColorChange(); break;
        default: ;
        }
    }
}

const QMetaObject TableDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_TableDialog.data,
      qt_meta_data_TableDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *TableDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TableDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TableDialog.stringdata0))
        return static_cast<void*>(const_cast< TableDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int TableDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
struct qt_meta_stringdata_TableCellSplitDialog_t {
    QByteArrayData data[4];
    char stringdata0[42];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TableCellSplitDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TableCellSplitDialog_t qt_meta_stringdata_TableCellSplitDialog = {
    {
QT_MOC_LITERAL(0, 0, 20), // "TableCellSplitDialog"
QT_MOC_LITERAL(1, 21, 10), // "OnFinished"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 8) // "OnCancel"

    },
    "TableCellSplitDialog\0OnFinished\0\0"
    "OnCancel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TableCellSplitDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a /* Public */,
       3,    0,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TableCellSplitDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TableCellSplitDialog *_t = static_cast<TableCellSplitDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnFinished(); break;
        case 1: _t->OnCancel(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject TableCellSplitDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_TableCellSplitDialog.data,
      qt_meta_data_TableCellSplitDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *TableCellSplitDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TableCellSplitDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TableCellSplitDialog.stringdata0))
        return static_cast<void*>(const_cast< TableCellSplitDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int TableCellSplitDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
struct qt_meta_stringdata_TableCellDialog_t {
    QByteArrayData data[5];
    char stringdata0[51];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TableCellDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TableCellDialog_t qt_meta_stringdata_TableCellDialog = {
    {
QT_MOC_LITERAL(0, 0, 15), // "TableCellDialog"
QT_MOC_LITERAL(1, 16, 10), // "OnFinished"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 8), // "OnCancel"
QT_MOC_LITERAL(4, 37, 13) // "OnColorChange"

    },
    "TableCellDialog\0OnFinished\0\0OnCancel\0"
    "OnColorChange"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TableCellDialog[] = {

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
       3,    0,   30,    2, 0x0a /* Public */,
       4,    0,   31,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TableCellDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TableCellDialog *_t = static_cast<TableCellDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnFinished(); break;
        case 1: _t->OnCancel(); break;
        case 2: _t->OnColorChange(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject TableCellDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_TableCellDialog.data,
      qt_meta_data_TableCellDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *TableCellDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TableCellDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TableCellDialog.stringdata0))
        return static_cast<void*>(const_cast< TableCellDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int TableCellDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
