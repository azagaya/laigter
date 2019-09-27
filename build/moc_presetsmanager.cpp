/****************************************************************************
** Meta object code from reading C++ file 'presetsmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../gui/presetsmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'presetsmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PresetsManager_t {
    QByteArrayData data[10];
    char stringdata0[224];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PresetsManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PresetsManager_t qt_meta_stringdata_PresetsManager = {
    {
QT_MOC_LITERAL(0, 0, 14), // "PresetsManager"
QT_MOC_LITERAL(1, 15, 13), // "settingAplied"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 31), // "on_pushButtonSavePreset_clicked"
QT_MOC_LITERAL(4, 62, 14), // "update_presets"
QT_MOC_LITERAL(5, 77, 12), // "scan_presets"
QT_MOC_LITERAL(6, 90, 33), // "on_pushButtonDeletePreset_cli..."
QT_MOC_LITERAL(7, 124, 31), // "on_pushButtonAplyPreset_clicked"
QT_MOC_LITERAL(8, 156, 33), // "on_pushButtonExportPreset_cli..."
QT_MOC_LITERAL(9, 190, 33) // "on_pushButtonImportPreset_cli..."

    },
    "PresetsManager\0settingAplied\0\0"
    "on_pushButtonSavePreset_clicked\0"
    "update_presets\0scan_presets\0"
    "on_pushButtonDeletePreset_clicked\0"
    "on_pushButtonAplyPreset_clicked\0"
    "on_pushButtonExportPreset_clicked\0"
    "on_pushButtonImportPreset_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PresetsManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QStringList,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PresetsManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PresetsManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->settingAplied(); break;
        case 1: _t->on_pushButtonSavePreset_clicked(); break;
        case 2: _t->update_presets(); break;
        case 3: { QStringList _r = _t->scan_presets();
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->on_pushButtonDeletePreset_clicked(); break;
        case 5: _t->on_pushButtonAplyPreset_clicked(); break;
        case 6: _t->on_pushButtonExportPreset_clicked(); break;
        case 7: _t->on_pushButtonImportPreset_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PresetsManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PresetsManager::settingAplied)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PresetsManager::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_PresetsManager.data,
    qt_meta_data_PresetsManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PresetsManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PresetsManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PresetsManager.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int PresetsManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void PresetsManager::settingAplied()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
