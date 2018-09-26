/****************************************************************************
** Meta object code from reading C++ file 'ReportTextEdit.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ReportTextEdit.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ReportTextEdit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ReportTextEdit_t {
    QByteArrayData data[6];
    char stringdata0[66];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ReportTextEdit_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ReportTextEdit_t qt_meta_stringdata_ReportTextEdit = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ReportTextEdit"
QT_MOC_LITERAL(1, 15, 14), // "OnPrintPreview"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 9), // "QPrinter*"
QT_MOC_LITERAL(4, 41, 7), // "printer"
QT_MOC_LITERAL(5, 49, 16) // "OnPageWidthLimit"

    },
    "ReportTextEdit\0OnPrintPreview\0\0QPrinter*\0"
    "printer\0OnPageWidthLimit"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ReportTextEdit[] = {

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
       1,    1,   24,    2, 0x0a /* Public */,
       5,    0,   27,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

       0        // eod
};

void ReportTextEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ReportTextEdit *_t = static_cast<ReportTextEdit *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnPrintPreview((*reinterpret_cast< QPrinter*(*)>(_a[1]))); break;
        case 1: _t->OnPageWidthLimit(); break;
        default: ;
        }
    }
}

const QMetaObject ReportTextEdit::staticMetaObject = {
    { &QTextEdit::staticMetaObject, qt_meta_stringdata_ReportTextEdit.data,
      qt_meta_data_ReportTextEdit,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ReportTextEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ReportTextEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ReportTextEdit.stringdata0))
        return static_cast<void*>(const_cast< ReportTextEdit*>(this));
    return QTextEdit::qt_metacast(_clname);
}

int ReportTextEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTextEdit::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
