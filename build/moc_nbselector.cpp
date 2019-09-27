/****************************************************************************
** Meta object code from reading C++ file 'nbselector.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../gui/nbselector.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nbselector.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NBSelector_t {
    QByteArrayData data[14];
    char stringdata0[221];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NBSelector_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NBSelector_t qt_meta_stringdata_NBSelector = {
    {
QT_MOC_LITERAL(0, 0, 10), // "NBSelector"
QT_MOC_LITERAL(1, 11, 36), // "on_pushButtonResetNeighbours_..."
QT_MOC_LITERAL(2, 48, 0), // ""
QT_MOC_LITERAL(3, 49, 14), // "get_neighbours"
QT_MOC_LITERAL(4, 64, 14), // "on_NUL_clicked"
QT_MOC_LITERAL(5, 79, 14), // "on_NUM_clicked"
QT_MOC_LITERAL(6, 94, 14), // "on_NUR_clicked"
QT_MOC_LITERAL(7, 109, 14), // "on_NML_clicked"
QT_MOC_LITERAL(8, 124, 14), // "on_NMM_clicked"
QT_MOC_LITERAL(9, 139, 14), // "on_NMR_clicked"
QT_MOC_LITERAL(10, 154, 14), // "on_NBL_clicked"
QT_MOC_LITERAL(11, 169, 14), // "on_NBM_clicked"
QT_MOC_LITERAL(12, 184, 14), // "on_NBR_clicked"
QT_MOC_LITERAL(13, 199, 21) // "on_pushButton_clicked"

    },
    "NBSelector\0on_pushButtonResetNeighbours_clicked\0"
    "\0get_neighbours\0on_NUL_clicked\0"
    "on_NUM_clicked\0on_NUR_clicked\0"
    "on_NML_clicked\0on_NMM_clicked\0"
    "on_NMR_clicked\0on_NBL_clicked\0"
    "on_NBM_clicked\0on_NBR_clicked\0"
    "on_pushButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NBSelector[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x08 /* Private */,
      11,    0,   83,    2, 0x08 /* Private */,
      12,    0,   84,    2, 0x08 /* Private */,
      13,    0,   85,    2, 0x08 /* Private */,

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

       0        // eod
};

void NBSelector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NBSelector *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButtonResetNeighbours_clicked(); break;
        case 1: _t->get_neighbours(); break;
        case 2: _t->on_NUL_clicked(); break;
        case 3: _t->on_NUM_clicked(); break;
        case 4: _t->on_NUR_clicked(); break;
        case 5: _t->on_NML_clicked(); break;
        case 6: _t->on_NMM_clicked(); break;
        case 7: _t->on_NMR_clicked(); break;
        case 8: _t->on_NBL_clicked(); break;
        case 9: _t->on_NBM_clicked(); break;
        case 10: _t->on_NBR_clicked(); break;
        case 11: _t->on_pushButton_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject NBSelector::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_NBSelector.data,
    qt_meta_data_NBSelector,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *NBSelector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NBSelector::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NBSelector.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int NBSelector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
