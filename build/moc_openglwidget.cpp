/****************************************************************************
** Meta object code from reading C++ file 'openglwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../src/openglwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'openglwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_OpenGlWidget_t {
    QByteArrayData data[83];
    char stringdata0[1096];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OpenGlWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OpenGlWidget_t qt_meta_stringdata_OpenGlWidget = {
    {
QT_MOC_LITERAL(0, 0, 12), // "OpenGlWidget"
QT_MOC_LITERAL(1, 13, 11), // "initialized"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 20), // "selectedLightChanged"
QT_MOC_LITERAL(4, 47, 12), // "LightSource*"
QT_MOC_LITERAL(5, 60, 5), // "light"
QT_MOC_LITERAL(6, 66, 15), // "stopAddingLight"
QT_MOC_LITERAL(7, 82, 25), // "selectedProcessorsChanged"
QT_MOC_LITERAL(8, 108, 22), // "QList<ImageProcessor*>"
QT_MOC_LITERAL(9, 131, 4), // "list"
QT_MOC_LITERAL(10, 136, 18), // "processor_selected"
QT_MOC_LITERAL(11, 155, 15), // "ImageProcessor*"
QT_MOC_LITERAL(12, 171, 9), // "processor"
QT_MOC_LITERAL(13, 181, 8), // "selected"
QT_MOC_LITERAL(14, 190, 24), // "set_enabled_map_controls"
QT_MOC_LITERAL(15, 215, 1), // "e"
QT_MOC_LITERAL(16, 217, 6), // "update"
QT_MOC_LITERAL(17, 224, 12), // "force_update"
QT_MOC_LITERAL(18, 237, 8), // "setImage"
QT_MOC_LITERAL(19, 246, 7), // "QImage*"
QT_MOC_LITERAL(20, 254, 5), // "image"
QT_MOC_LITERAL(21, 260, 12), // "setNormalMap"
QT_MOC_LITERAL(22, 273, 9), // "normalMap"
QT_MOC_LITERAL(23, 283, 14), // "setParallaxMap"
QT_MOC_LITERAL(24, 298, 11), // "parallaxMap"
QT_MOC_LITERAL(25, 310, 14), // "setSpecularMap"
QT_MOC_LITERAL(26, 325, 15), // "setOcclusionMap"
QT_MOC_LITERAL(27, 341, 12), // "occlusionMap"
QT_MOC_LITERAL(28, 354, 7), // "setZoom"
QT_MOC_LITERAL(29, 362, 4), // "zoom"
QT_MOC_LITERAL(30, 367, 9), // "resetZoom"
QT_MOC_LITERAL(31, 377, 7), // "fitZoom"
QT_MOC_LITERAL(32, 385, 7), // "getZoom"
QT_MOC_LITERAL(33, 393, 8), // "setLight"
QT_MOC_LITERAL(34, 402, 13), // "setLightColor"
QT_MOC_LITERAL(35, 416, 5), // "color"
QT_MOC_LITERAL(36, 422, 12), // "setSpecColor"
QT_MOC_LITERAL(37, 435, 14), // "setLightHeight"
QT_MOC_LITERAL(38, 450, 6), // "height"
QT_MOC_LITERAL(39, 457, 17), // "setLightIntensity"
QT_MOC_LITERAL(40, 475, 9), // "intensity"
QT_MOC_LITERAL(41, 485, 19), // "setAmbientIntensity"
QT_MOC_LITERAL(42, 505, 16), // "setSpecIntensity"
QT_MOC_LITERAL(43, 522, 14), // "setSpecScatter"
QT_MOC_LITERAL(44, 537, 7), // "scatter"
QT_MOC_LITERAL(45, 545, 15), // "setAmbientColor"
QT_MOC_LITERAL(46, 561, 18), // "setBackgroundColor"
QT_MOC_LITERAL(47, 580, 8), // "setTileX"
QT_MOC_LITERAL(48, 589, 1), // "x"
QT_MOC_LITERAL(49, 591, 8), // "setTileY"
QT_MOC_LITERAL(50, 600, 1), // "y"
QT_MOC_LITERAL(51, 602, 12), // "setPixelated"
QT_MOC_LITERAL(52, 615, 9), // "pixelated"
QT_MOC_LITERAL(53, 625, 12), // "setPixelSize"
QT_MOC_LITERAL(54, 638, 4), // "size"
QT_MOC_LITERAL(55, 643, 17), // "setParallaxHeight"
QT_MOC_LITERAL(56, 661, 11), // "setParallax"
QT_MOC_LITERAL(57, 673, 1), // "p"
QT_MOC_LITERAL(58, 675, 17), // "calculate_preview"
QT_MOC_LITERAL(59, 693, 11), // "get_preview"
QT_MOC_LITERAL(60, 705, 12), // "update_scene"
QT_MOC_LITERAL(61, 718, 12), // "renderBuffer"
QT_MOC_LITERAL(62, 731, 12), // "loadTextures"
QT_MOC_LITERAL(63, 744, 13), // "set_add_light"
QT_MOC_LITERAL(64, 758, 3), // "add"
QT_MOC_LITERAL(65, 762, 21), // "update_light_position"
QT_MOC_LITERAL(66, 784, 7), // "new_pos"
QT_MOC_LITERAL(67, 792, 12), // "remove_light"
QT_MOC_LITERAL(68, 805, 26), // "get_current_light_list_ptr"
QT_MOC_LITERAL(69, 832, 20), // "QList<LightSource*>*"
QT_MOC_LITERAL(70, 853, 22), // "set_current_light_list"
QT_MOC_LITERAL(71, 876, 13), // "add_processor"
QT_MOC_LITERAL(72, 890, 21), // "set_current_processor"
QT_MOC_LITERAL(73, 912, 18), // "set_processor_list"
QT_MOC_LITERAL(74, 931, 20), // "clear_processor_list"
QT_MOC_LITERAL(75, 952, 21), // "get_current_processor"
QT_MOC_LITERAL(76, 974, 22), // "set_processor_selected"
QT_MOC_LITERAL(77, 997, 27), // "set_all_processors_selected"
QT_MOC_LITERAL(78, 1025, 27), // "get_all_selected_processors"
QT_MOC_LITERAL(79, 1053, 13), // "set_view_mode"
QT_MOC_LITERAL(80, 1067, 4), // "mode"
QT_MOC_LITERAL(81, 1072, 21), // "use_sample_light_list"
QT_MOC_LITERAL(82, 1094, 1) // "l"

    },
    "OpenGlWidget\0initialized\0\0"
    "selectedLightChanged\0LightSource*\0"
    "light\0stopAddingLight\0selectedProcessorsChanged\0"
    "QList<ImageProcessor*>\0list\0"
    "processor_selected\0ImageProcessor*\0"
    "processor\0selected\0set_enabled_map_controls\0"
    "e\0update\0force_update\0setImage\0QImage*\0"
    "image\0setNormalMap\0normalMap\0"
    "setParallaxMap\0parallaxMap\0setSpecularMap\0"
    "setOcclusionMap\0occlusionMap\0setZoom\0"
    "zoom\0resetZoom\0fitZoom\0getZoom\0setLight\0"
    "setLightColor\0color\0setSpecColor\0"
    "setLightHeight\0height\0setLightIntensity\0"
    "intensity\0setAmbientIntensity\0"
    "setSpecIntensity\0setSpecScatter\0scatter\0"
    "setAmbientColor\0setBackgroundColor\0"
    "setTileX\0x\0setTileY\0y\0setPixelated\0"
    "pixelated\0setPixelSize\0size\0"
    "setParallaxHeight\0setParallax\0p\0"
    "calculate_preview\0get_preview\0"
    "update_scene\0renderBuffer\0loadTextures\0"
    "set_add_light\0add\0update_light_position\0"
    "new_pos\0remove_light\0get_current_light_list_ptr\0"
    "QList<LightSource*>*\0set_current_light_list\0"
    "add_processor\0set_current_processor\0"
    "set_processor_list\0clear_processor_list\0"
    "get_current_processor\0set_processor_selected\0"
    "set_all_processors_selected\0"
    "get_all_selected_processors\0set_view_mode\0"
    "mode\0use_sample_light_list\0l"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OpenGlWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      53,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  279,    2, 0x06 /* Public */,
       3,    1,  280,    2, 0x06 /* Public */,
       6,    0,  283,    2, 0x06 /* Public */,
       7,    1,  284,    2, 0x06 /* Public */,
      10,    2,  287,    2, 0x06 /* Public */,
      14,    1,  292,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    0,  295,    2, 0x0a /* Public */,
      17,    0,  296,    2, 0x0a /* Public */,
      18,    1,  297,    2, 0x0a /* Public */,
      21,    1,  300,    2, 0x0a /* Public */,
      23,    1,  303,    2, 0x0a /* Public */,
      25,    1,  306,    2, 0x0a /* Public */,
      26,    1,  309,    2, 0x0a /* Public */,
      28,    1,  312,    2, 0x0a /* Public */,
      30,    0,  315,    2, 0x0a /* Public */,
      31,    0,  316,    2, 0x0a /* Public */,
      32,    0,  317,    2, 0x0a /* Public */,
      33,    1,  318,    2, 0x0a /* Public */,
      34,    1,  321,    2, 0x0a /* Public */,
      36,    1,  324,    2, 0x0a /* Public */,
      37,    1,  327,    2, 0x0a /* Public */,
      39,    1,  330,    2, 0x0a /* Public */,
      41,    1,  333,    2, 0x0a /* Public */,
      42,    1,  336,    2, 0x0a /* Public */,
      43,    1,  339,    2, 0x0a /* Public */,
      45,    1,  342,    2, 0x0a /* Public */,
      46,    1,  345,    2, 0x0a /* Public */,
      47,    1,  348,    2, 0x0a /* Public */,
      49,    1,  351,    2, 0x0a /* Public */,
      51,    1,  354,    2, 0x0a /* Public */,
      53,    1,  357,    2, 0x0a /* Public */,
      55,    1,  360,    2, 0x0a /* Public */,
      56,    1,  363,    2, 0x0a /* Public */,
      58,    0,  366,    2, 0x0a /* Public */,
      59,    0,  367,    2, 0x0a /* Public */,
      60,    0,  368,    2, 0x0a /* Public */,
      61,    0,  369,    2, 0x0a /* Public */,
      62,    0,  370,    2, 0x0a /* Public */,
      63,    1,  371,    2, 0x0a /* Public */,
      65,    1,  374,    2, 0x0a /* Public */,
      67,    1,  377,    2, 0x0a /* Public */,
      68,    0,  380,    2, 0x0a /* Public */,
      70,    1,  381,    2, 0x0a /* Public */,
      71,    1,  384,    2, 0x0a /* Public */,
      72,    1,  387,    2, 0x0a /* Public */,
      73,    1,  390,    2, 0x0a /* Public */,
      74,    0,  393,    2, 0x0a /* Public */,
      75,    0,  394,    2, 0x0a /* Public */,
      76,    2,  395,    2, 0x0a /* Public */,
      77,    1,  400,    2, 0x0a /* Public */,
      78,    0,  403,    2, 0x0a /* Public */,
      79,    1,  404,    2, 0x0a /* Public */,
      81,    1,  407,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 11, QMetaType::Bool,   12,   13,
    QMetaType::Void, QMetaType::Bool,   15,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 19,   20,
    QMetaType::Void, 0x80000000 | 19,   22,
    QMetaType::Void, 0x80000000 | 19,   24,
    QMetaType::Void, 0x80000000 | 19,   20,
    QMetaType::Void, 0x80000000 | 19,   27,
    QMetaType::Void, QMetaType::Float,   29,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Float,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::QColor,   35,
    QMetaType::Void, QMetaType::QColor,   35,
    QMetaType::Void, QMetaType::Float,   38,
    QMetaType::Void, QMetaType::Float,   40,
    QMetaType::Void, QMetaType::Float,   40,
    QMetaType::Void, QMetaType::Float,   40,
    QMetaType::Void, QMetaType::Int,   44,
    QMetaType::Void, QMetaType::QColor,   35,
    QMetaType::Void, QMetaType::QColor,   35,
    QMetaType::Void, QMetaType::Bool,   48,
    QMetaType::Void, QMetaType::Bool,   50,
    QMetaType::Void, QMetaType::Bool,   52,
    QMetaType::Void, QMetaType::Int,   54,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::Bool,   57,
    QMetaType::QImage,
    QMetaType::QImage,
    QMetaType::Void,
    QMetaType::QImage,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   64,
    QMetaType::Void, QMetaType::QVector3D,   66,
    QMetaType::Void, 0x80000000 | 4,    5,
    0x80000000 | 69,
    QMetaType::Void, 0x80000000 | 69,    9,
    QMetaType::Void, 0x80000000 | 11,   57,
    QMetaType::Void, 0x80000000 | 11,   57,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    0x80000000 | 11,
    QMetaType::Void, 0x80000000 | 11, QMetaType::Bool,   12,   13,
    QMetaType::Void, QMetaType::Bool,   13,
    0x80000000 | 8,
    QMetaType::Void, QMetaType::Int,   80,
    QMetaType::Void, QMetaType::Bool,   82,

       0        // eod
};

void OpenGlWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<OpenGlWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->initialized(); break;
        case 1: _t->selectedLightChanged((*reinterpret_cast< LightSource*(*)>(_a[1]))); break;
        case 2: _t->stopAddingLight(); break;
        case 3: _t->selectedProcessorsChanged((*reinterpret_cast< QList<ImageProcessor*>(*)>(_a[1]))); break;
        case 4: _t->processor_selected((*reinterpret_cast< ImageProcessor*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 5: _t->set_enabled_map_controls((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->update(); break;
        case 7: _t->force_update(); break;
        case 8: _t->setImage((*reinterpret_cast< QImage*(*)>(_a[1]))); break;
        case 9: _t->setNormalMap((*reinterpret_cast< QImage*(*)>(_a[1]))); break;
        case 10: _t->setParallaxMap((*reinterpret_cast< QImage*(*)>(_a[1]))); break;
        case 11: _t->setSpecularMap((*reinterpret_cast< QImage*(*)>(_a[1]))); break;
        case 12: _t->setOcclusionMap((*reinterpret_cast< QImage*(*)>(_a[1]))); break;
        case 13: _t->setZoom((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 14: _t->resetZoom(); break;
        case 15: _t->fitZoom(); break;
        case 16: { float _r = _t->getZoom();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 17: _t->setLight((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: _t->setLightColor((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 19: _t->setSpecColor((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 20: _t->setLightHeight((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 21: _t->setLightIntensity((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 22: _t->setAmbientIntensity((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 23: _t->setSpecIntensity((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 24: _t->setSpecScatter((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->setAmbientColor((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 26: _t->setBackgroundColor((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 27: _t->setTileX((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 28: _t->setTileY((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 29: _t->setPixelated((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 30: _t->setPixelSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 31: _t->setParallaxHeight((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 32: _t->setParallax((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 33: { QImage _r = _t->calculate_preview();
            if (_a[0]) *reinterpret_cast< QImage*>(_a[0]) = std::move(_r); }  break;
        case 34: { QImage _r = _t->get_preview();
            if (_a[0]) *reinterpret_cast< QImage*>(_a[0]) = std::move(_r); }  break;
        case 35: _t->update_scene(); break;
        case 36: { QImage _r = _t->renderBuffer();
            if (_a[0]) *reinterpret_cast< QImage*>(_a[0]) = std::move(_r); }  break;
        case 37: _t->loadTextures(); break;
        case 38: _t->set_add_light((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 39: _t->update_light_position((*reinterpret_cast< QVector3D(*)>(_a[1]))); break;
        case 40: _t->remove_light((*reinterpret_cast< LightSource*(*)>(_a[1]))); break;
        case 41: { QList<LightSource*>* _r = _t->get_current_light_list_ptr();
            if (_a[0]) *reinterpret_cast< QList<LightSource*>**>(_a[0]) = std::move(_r); }  break;
        case 42: _t->set_current_light_list((*reinterpret_cast< QList<LightSource*>*(*)>(_a[1]))); break;
        case 43: _t->add_processor((*reinterpret_cast< ImageProcessor*(*)>(_a[1]))); break;
        case 44: _t->set_current_processor((*reinterpret_cast< ImageProcessor*(*)>(_a[1]))); break;
        case 45: _t->set_processor_list((*reinterpret_cast< QList<ImageProcessor*>(*)>(_a[1]))); break;
        case 46: _t->clear_processor_list(); break;
        case 47: { ImageProcessor* _r = _t->get_current_processor();
            if (_a[0]) *reinterpret_cast< ImageProcessor**>(_a[0]) = std::move(_r); }  break;
        case 48: _t->set_processor_selected((*reinterpret_cast< ImageProcessor*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 49: _t->set_all_processors_selected((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 50: { QList<ImageProcessor*> _r = _t->get_all_selected_processors();
            if (_a[0]) *reinterpret_cast< QList<ImageProcessor*>*>(_a[0]) = std::move(_r); }  break;
        case 51: _t->set_view_mode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 52: _t->use_sample_light_list((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< LightSource* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<ImageProcessor*> >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ImageProcessor* >(); break;
            }
            break;
        case 40:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< LightSource* >(); break;
            }
            break;
        case 43:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ImageProcessor* >(); break;
            }
            break;
        case 44:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ImageProcessor* >(); break;
            }
            break;
        case 45:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<ImageProcessor*> >(); break;
            }
            break;
        case 48:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ImageProcessor* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (OpenGlWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OpenGlWidget::initialized)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (OpenGlWidget::*)(LightSource * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OpenGlWidget::selectedLightChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (OpenGlWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OpenGlWidget::stopAddingLight)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (OpenGlWidget::*)(QList<ImageProcessor*> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OpenGlWidget::selectedProcessorsChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (OpenGlWidget::*)(ImageProcessor * , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OpenGlWidget::processor_selected)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (OpenGlWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OpenGlWidget::set_enabled_map_controls)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject OpenGlWidget::staticMetaObject = { {
    &QOpenGLWidget::staticMetaObject,
    qt_meta_stringdata_OpenGlWidget.data,
    qt_meta_data_OpenGlWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *OpenGlWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OpenGlWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_OpenGlWidget.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QOpenGLFunctions"))
        return static_cast< QOpenGLFunctions*>(this);
    return QOpenGLWidget::qt_metacast(_clname);
}

int OpenGlWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 53)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 53;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 53)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 53;
    }
    return _id;
}

// SIGNAL 0
void OpenGlWidget::initialized()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void OpenGlWidget::selectedLightChanged(LightSource * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void OpenGlWidget::stopAddingLight()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void OpenGlWidget::selectedProcessorsChanged(QList<ImageProcessor*> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void OpenGlWidget::processor_selected(ImageProcessor * _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void OpenGlWidget::set_enabled_map_controls(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
