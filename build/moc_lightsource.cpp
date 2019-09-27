/****************************************************************************
** Meta object code from reading C++ file 'lightsource.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../src/lightsource.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lightsource.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LightSource_t {
    QByteArrayData data[24];
    char stringdata0[347];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LightSource_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LightSource_t qt_meta_stringdata_LightSource = {
    {
QT_MOC_LITERAL(0, 0, 11), // "LightSource"
QT_MOC_LITERAL(1, 12, 17), // "set_diffuse_color"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 5), // "color"
QT_MOC_LITERAL(4, 37, 17), // "get_diffuse_color"
QT_MOC_LITERAL(5, 55, 21), // "set_diffuse_intensity"
QT_MOC_LITERAL(6, 77, 9), // "intensity"
QT_MOC_LITERAL(7, 87, 21), // "get_diffuse_intensity"
QT_MOC_LITERAL(8, 109, 10), // "set_height"
QT_MOC_LITERAL(9, 120, 6), // "height"
QT_MOC_LITERAL(10, 127, 10), // "get_height"
QT_MOC_LITERAL(11, 138, 18), // "set_specular_color"
QT_MOC_LITERAL(12, 157, 18), // "get_specular_color"
QT_MOC_LITERAL(13, 176, 22), // "set_specular_intensity"
QT_MOC_LITERAL(14, 199, 21), // "get_specular_intesity"
QT_MOC_LITERAL(15, 221, 20), // "set_specular_scatter"
QT_MOC_LITERAL(16, 242, 7), // "scatter"
QT_MOC_LITERAL(17, 250, 20), // "get_specular_scatter"
QT_MOC_LITERAL(18, 271, 18), // "set_light_position"
QT_MOC_LITERAL(19, 290, 8), // "position"
QT_MOC_LITERAL(20, 299, 18), // "get_light_position"
QT_MOC_LITERAL(21, 318, 13), // "copy_settings"
QT_MOC_LITERAL(22, 332, 12), // "LightSource*"
QT_MOC_LITERAL(23, 345, 1) // "l"

    },
    "LightSource\0set_diffuse_color\0\0color\0"
    "get_diffuse_color\0set_diffuse_intensity\0"
    "intensity\0get_diffuse_intensity\0"
    "set_height\0height\0get_height\0"
    "set_specular_color\0get_specular_color\0"
    "set_specular_intensity\0get_specular_intesity\0"
    "set_specular_scatter\0scatter\0"
    "get_specular_scatter\0set_light_position\0"
    "position\0get_light_position\0copy_settings\0"
    "LightSource*\0l"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LightSource[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x0a /* Public */,
       4,    0,   92,    2, 0x0a /* Public */,
       5,    1,   93,    2, 0x0a /* Public */,
       7,    0,   96,    2, 0x0a /* Public */,
       8,    1,   97,    2, 0x0a /* Public */,
      10,    0,  100,    2, 0x0a /* Public */,
      11,    1,  101,    2, 0x0a /* Public */,
      12,    0,  104,    2, 0x0a /* Public */,
      13,    1,  105,    2, 0x0a /* Public */,
      14,    0,  108,    2, 0x0a /* Public */,
      15,    1,  109,    2, 0x0a /* Public */,
      17,    0,  112,    2, 0x0a /* Public */,
      18,    1,  113,    2, 0x0a /* Public */,
      20,    0,  116,    2, 0x0a /* Public */,
      21,    1,  117,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QColor,    3,
    QMetaType::QColor,
    QMetaType::Void, QMetaType::Float,    6,
    QMetaType::Float,
    QMetaType::Void, QMetaType::Float,    9,
    QMetaType::Float,
    QMetaType::Void, QMetaType::QColor,    3,
    QMetaType::QColor,
    QMetaType::Void, QMetaType::Float,    6,
    QMetaType::Float,
    QMetaType::Void, QMetaType::Float,   16,
    QMetaType::Float,
    QMetaType::Void, QMetaType::QVector3D,   19,
    QMetaType::QVector3D,
    QMetaType::Void, 0x80000000 | 22,   23,

       0        // eod
};

void LightSource::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LightSource *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->set_diffuse_color((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 1: { QColor _r = _t->get_diffuse_color();
            if (_a[0]) *reinterpret_cast< QColor*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->set_diffuse_intensity((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: { float _r = _t->get_diffuse_intensity();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->set_height((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: { float _r = _t->get_height();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 6: _t->set_specular_color((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 7: { QColor _r = _t->get_specular_color();
            if (_a[0]) *reinterpret_cast< QColor*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->set_specular_intensity((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 9: { float _r = _t->get_specular_intesity();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->set_specular_scatter((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 11: { float _r = _t->get_specular_scatter();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 12: _t->set_light_position((*reinterpret_cast< QVector3D(*)>(_a[1]))); break;
        case 13: { QVector3D _r = _t->get_light_position();
            if (_a[0]) *reinterpret_cast< QVector3D*>(_a[0]) = std::move(_r); }  break;
        case 14: _t->copy_settings((*reinterpret_cast< LightSource*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 14:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< LightSource* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject LightSource::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_LightSource.data,
    qt_meta_data_LightSource,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *LightSource::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LightSource::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LightSource.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int LightSource::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
