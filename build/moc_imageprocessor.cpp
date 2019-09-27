/****************************************************************************
** Meta object code from reading C++ file 'imageprocessor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../src/imageprocessor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imageprocessor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ImageProcessor_t {
    QByteArrayData data[142];
    char stringdata0[2120];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ImageProcessor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ImageProcessor_t qt_meta_stringdata_ImageProcessor = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ImageProcessor"
QT_MOC_LITERAL(1, 15, 9), // "processed"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 7), // "on_idle"
QT_MOC_LITERAL(4, 34, 13), // "copy_settings"
QT_MOC_LITERAL(5, 48, 17), // "ProcessorSettings"
QT_MOC_LITERAL(6, 66, 1), // "s"
QT_MOC_LITERAL(7, 68, 16), // "set_normal_depth"
QT_MOC_LITERAL(8, 85, 5), // "depth"
QT_MOC_LITERAL(9, 91, 16), // "get_normal_depth"
QT_MOC_LITERAL(10, 108, 22), // "set_normal_blur_radius"
QT_MOC_LITERAL(11, 131, 6), // "radius"
QT_MOC_LITERAL(12, 138, 22), // "get_normal_blur_radius"
QT_MOC_LITERAL(13, 161, 22), // "set_normal_bisel_depth"
QT_MOC_LITERAL(14, 184, 22), // "get_normal_bisel_depth"
QT_MOC_LITERAL(15, 207, 25), // "set_normal_bisel_distance"
QT_MOC_LITERAL(16, 233, 8), // "distance"
QT_MOC_LITERAL(17, 242, 25), // "get_normal_bisel_distance"
QT_MOC_LITERAL(18, 268, 28), // "set_normal_bisel_blur_radius"
QT_MOC_LITERAL(19, 297, 28), // "get_normal_bisel_blur_radius"
QT_MOC_LITERAL(20, 326, 21), // "set_normal_bisel_soft"
QT_MOC_LITERAL(21, 348, 4), // "soft"
QT_MOC_LITERAL(22, 353, 21), // "get_normal_bisel_soft"
QT_MOC_LITERAL(23, 375, 19), // "set_normal_invert_x"
QT_MOC_LITERAL(24, 395, 6), // "invert"
QT_MOC_LITERAL(25, 402, 19), // "get_normal_invert_x"
QT_MOC_LITERAL(26, 422, 19), // "set_normal_invert_y"
QT_MOC_LITERAL(27, 442, 19), // "get_normal_invert_y"
QT_MOC_LITERAL(28, 462, 19), // "set_normal_invert_z"
QT_MOC_LITERAL(29, 482, 12), // "get_tileable"
QT_MOC_LITERAL(30, 495, 12), // "set_tileable"
QT_MOC_LITERAL(31, 508, 1), // "t"
QT_MOC_LITERAL(32, 510, 19), // "set_parallax_invert"
QT_MOC_LITERAL(33, 530, 19), // "get_parallax_invert"
QT_MOC_LITERAL(34, 550, 18), // "set_parallax_focus"
QT_MOC_LITERAL(35, 569, 5), // "focus"
QT_MOC_LITERAL(36, 575, 18), // "get_parallax_focus"
QT_MOC_LITERAL(37, 594, 17), // "set_parallax_soft"
QT_MOC_LITERAL(38, 612, 17), // "get_parallax_soft"
QT_MOC_LITERAL(39, 630, 19), // "set_parallax_thresh"
QT_MOC_LITERAL(40, 650, 6), // "thresh"
QT_MOC_LITERAL(41, 657, 19), // "get_parallax_thresh"
QT_MOC_LITERAL(42, 677, 16), // "set_parallax_min"
QT_MOC_LITERAL(43, 694, 3), // "min"
QT_MOC_LITERAL(44, 698, 16), // "get_parallax_min"
QT_MOC_LITERAL(45, 715, 17), // "set_parallax_type"
QT_MOC_LITERAL(46, 733, 12), // "ParallaxType"
QT_MOC_LITERAL(47, 746, 5), // "ptype"
QT_MOC_LITERAL(48, 752, 25), // "get_parallax_quantization"
QT_MOC_LITERAL(49, 778, 25), // "set_parallax_quantization"
QT_MOC_LITERAL(50, 804, 1), // "q"
QT_MOC_LITERAL(51, 806, 25), // "get_parallax_erode_dilate"
QT_MOC_LITERAL(52, 832, 25), // "set_parallax_erode_dilate"
QT_MOC_LITERAL(53, 858, 5), // "value"
QT_MOC_LITERAL(54, 864, 23), // "get_parallax_brightness"
QT_MOC_LITERAL(55, 888, 23), // "set_parallax_brightness"
QT_MOC_LITERAL(56, 912, 10), // "brightness"
QT_MOC_LITERAL(57, 923, 21), // "get_parallax_contrast"
QT_MOC_LITERAL(58, 945, 21), // "set_parallax_contrast"
QT_MOC_LITERAL(59, 967, 8), // "contrast"
QT_MOC_LITERAL(60, 976, 19), // "set_specular_invert"
QT_MOC_LITERAL(61, 996, 19), // "get_specular_invert"
QT_MOC_LITERAL(62, 1016, 19), // "set_specular_thresh"
QT_MOC_LITERAL(63, 1036, 19), // "get_specular_trhesh"
QT_MOC_LITERAL(64, 1056, 21), // "set_specular_contrast"
QT_MOC_LITERAL(65, 1078, 21), // "get_specular_contrast"
QT_MOC_LITERAL(66, 1100, 19), // "set_specular_bright"
QT_MOC_LITERAL(67, 1120, 6), // "bright"
QT_MOC_LITERAL(68, 1127, 19), // "get_specular_bright"
QT_MOC_LITERAL(69, 1147, 17), // "set_specular_blur"
QT_MOC_LITERAL(70, 1165, 4), // "blur"
QT_MOC_LITERAL(71, 1170, 17), // "get_specular_blur"
QT_MOC_LITERAL(72, 1188, 23), // "set_specular_base_color"
QT_MOC_LITERAL(73, 1212, 5), // "Vec4b"
QT_MOC_LITERAL(74, 1218, 5), // "color"
QT_MOC_LITERAL(75, 1224, 23), // "get_specular_base_color"
QT_MOC_LITERAL(76, 1248, 20), // "set_occlusion_invert"
QT_MOC_LITERAL(77, 1269, 20), // "get_occlusion_invert"
QT_MOC_LITERAL(78, 1290, 20), // "set_occlusion_thresh"
QT_MOC_LITERAL(79, 1311, 20), // "get_occlusion_trhesh"
QT_MOC_LITERAL(80, 1332, 22), // "set_occlusion_contrast"
QT_MOC_LITERAL(81, 1355, 22), // "get_occlusion_contrast"
QT_MOC_LITERAL(82, 1378, 20), // "set_occlusion_bright"
QT_MOC_LITERAL(83, 1399, 20), // "get_occlusion_bright"
QT_MOC_LITERAL(84, 1420, 18), // "set_occlusion_blur"
QT_MOC_LITERAL(85, 1439, 18), // "get_occlusion_blur"
QT_MOC_LITERAL(86, 1458, 27), // "set_occlusion_distance_mode"
QT_MOC_LITERAL(87, 1486, 13), // "distance_mode"
QT_MOC_LITERAL(88, 1500, 27), // "get_occlusion_distance_mode"
QT_MOC_LITERAL(89, 1528, 22), // "set_occlusion_distance"
QT_MOC_LITERAL(90, 1551, 22), // "get_occlusion_distance"
QT_MOC_LITERAL(91, 1574, 12), // "get_settings"
QT_MOC_LITERAL(92, 1587, 17), // "get_parallax_type"
QT_MOC_LITERAL(93, 1605, 15), // "fill_neighbours"
QT_MOC_LITERAL(94, 1621, 3), // "Mat"
QT_MOC_LITERAL(95, 1625, 3), // "src"
QT_MOC_LITERAL(96, 1629, 3), // "dst"
QT_MOC_LITERAL(97, 1633, 13), // "set_neighbour"
QT_MOC_LITERAL(98, 1647, 1), // "x"
QT_MOC_LITERAL(99, 1649, 1), // "y"
QT_MOC_LITERAL(100, 1651, 19), // "set_neighbour_image"
QT_MOC_LITERAL(101, 1671, 8), // "fileName"
QT_MOC_LITERAL(102, 1680, 5), // "image"
QT_MOC_LITERAL(103, 1686, 15), // "empty_neighbour"
QT_MOC_LITERAL(104, 1702, 16), // "reset_neighbours"
QT_MOC_LITERAL(105, 1719, 21), // "set_current_heightmap"
QT_MOC_LITERAL(106, 1741, 13), // "get_neighbour"
QT_MOC_LITERAL(107, 1755, 14), // "set_light_list"
QT_MOC_LITERAL(108, 1770, 20), // "QList<LightSource*>&"
QT_MOC_LITERAL(109, 1791, 4), // "list"
QT_MOC_LITERAL(110, 1796, 18), // "get_light_list_ptr"
QT_MOC_LITERAL(111, 1815, 20), // "QList<LightSource*>*"
QT_MOC_LITERAL(112, 1836, 12), // "set_position"
QT_MOC_LITERAL(113, 1849, 7), // "new_pos"
QT_MOC_LITERAL(114, 1857, 12), // "get_position"
QT_MOC_LITERAL(115, 1870, 10), // "QVector3D*"
QT_MOC_LITERAL(116, 1881, 10), // "set_offset"
QT_MOC_LITERAL(117, 1892, 7), // "new_off"
QT_MOC_LITERAL(118, 1900, 10), // "get_offset"
QT_MOC_LITERAL(119, 1911, 12), // "set_selected"
QT_MOC_LITERAL(120, 1924, 12), // "get_selected"
QT_MOC_LITERAL(121, 1937, 8), // "set_zoom"
QT_MOC_LITERAL(122, 1946, 8), // "new_zoom"
QT_MOC_LITERAL(123, 1955, 8), // "get_zoom"
QT_MOC_LITERAL(124, 1964, 6), // "set_sx"
QT_MOC_LITERAL(125, 1971, 6), // "new_sx"
QT_MOC_LITERAL(126, 1978, 6), // "set_sy"
QT_MOC_LITERAL(127, 1985, 6), // "new_sy"
QT_MOC_LITERAL(128, 1992, 6), // "get_sx"
QT_MOC_LITERAL(129, 1999, 6), // "get_sy"
QT_MOC_LITERAL(130, 2006, 10), // "set_tile_x"
QT_MOC_LITERAL(131, 2017, 2), // "tx"
QT_MOC_LITERAL(132, 2020, 10), // "set_tile_y"
QT_MOC_LITERAL(133, 2031, 2), // "ty"
QT_MOC_LITERAL(134, 2034, 10), // "get_tile_x"
QT_MOC_LITERAL(135, 2045, 10), // "get_tile_y"
QT_MOC_LITERAL(136, 2056, 15), // "set_is_parallax"
QT_MOC_LITERAL(137, 2072, 1), // "p"
QT_MOC_LITERAL(138, 2074, 15), // "get_is_parallax"
QT_MOC_LITERAL(139, 2090, 13), // "get_connected"
QT_MOC_LITERAL(140, 2104, 13), // "set_connected"
QT_MOC_LITERAL(141, 2118, 1) // "c"

    },
    "ImageProcessor\0processed\0\0on_idle\0"
    "copy_settings\0ProcessorSettings\0s\0"
    "set_normal_depth\0depth\0get_normal_depth\0"
    "set_normal_blur_radius\0radius\0"
    "get_normal_blur_radius\0set_normal_bisel_depth\0"
    "get_normal_bisel_depth\0set_normal_bisel_distance\0"
    "distance\0get_normal_bisel_distance\0"
    "set_normal_bisel_blur_radius\0"
    "get_normal_bisel_blur_radius\0"
    "set_normal_bisel_soft\0soft\0"
    "get_normal_bisel_soft\0set_normal_invert_x\0"
    "invert\0get_normal_invert_x\0"
    "set_normal_invert_y\0get_normal_invert_y\0"
    "set_normal_invert_z\0get_tileable\0"
    "set_tileable\0t\0set_parallax_invert\0"
    "get_parallax_invert\0set_parallax_focus\0"
    "focus\0get_parallax_focus\0set_parallax_soft\0"
    "get_parallax_soft\0set_parallax_thresh\0"
    "thresh\0get_parallax_thresh\0set_parallax_min\0"
    "min\0get_parallax_min\0set_parallax_type\0"
    "ParallaxType\0ptype\0get_parallax_quantization\0"
    "set_parallax_quantization\0q\0"
    "get_parallax_erode_dilate\0"
    "set_parallax_erode_dilate\0value\0"
    "get_parallax_brightness\0set_parallax_brightness\0"
    "brightness\0get_parallax_contrast\0"
    "set_parallax_contrast\0contrast\0"
    "set_specular_invert\0get_specular_invert\0"
    "set_specular_thresh\0get_specular_trhesh\0"
    "set_specular_contrast\0get_specular_contrast\0"
    "set_specular_bright\0bright\0"
    "get_specular_bright\0set_specular_blur\0"
    "blur\0get_specular_blur\0set_specular_base_color\0"
    "Vec4b\0color\0get_specular_base_color\0"
    "set_occlusion_invert\0get_occlusion_invert\0"
    "set_occlusion_thresh\0get_occlusion_trhesh\0"
    "set_occlusion_contrast\0get_occlusion_contrast\0"
    "set_occlusion_bright\0get_occlusion_bright\0"
    "set_occlusion_blur\0get_occlusion_blur\0"
    "set_occlusion_distance_mode\0distance_mode\0"
    "get_occlusion_distance_mode\0"
    "set_occlusion_distance\0get_occlusion_distance\0"
    "get_settings\0get_parallax_type\0"
    "fill_neighbours\0Mat\0src\0dst\0set_neighbour\0"
    "x\0y\0set_neighbour_image\0fileName\0image\0"
    "empty_neighbour\0reset_neighbours\0"
    "set_current_heightmap\0get_neighbour\0"
    "set_light_list\0QList<LightSource*>&\0"
    "list\0get_light_list_ptr\0QList<LightSource*>*\0"
    "set_position\0new_pos\0get_position\0"
    "QVector3D*\0set_offset\0new_off\0get_offset\0"
    "set_selected\0get_selected\0set_zoom\0"
    "new_zoom\0get_zoom\0set_sx\0new_sx\0set_sy\0"
    "new_sy\0get_sx\0get_sy\0set_tile_x\0tx\0"
    "set_tile_y\0ty\0get_tile_x\0get_tile_y\0"
    "set_is_parallax\0p\0get_is_parallax\0"
    "get_connected\0set_connected\0c"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ImageProcessor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      98,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  504,    2, 0x06 /* Public */,
       3,    0,  505,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,  506,    2, 0x0a /* Public */,
       7,    1,  509,    2, 0x0a /* Public */,
       9,    0,  512,    2, 0x0a /* Public */,
      10,    1,  513,    2, 0x0a /* Public */,
      12,    0,  516,    2, 0x0a /* Public */,
      13,    1,  517,    2, 0x0a /* Public */,
      14,    0,  520,    2, 0x0a /* Public */,
      15,    1,  521,    2, 0x0a /* Public */,
      17,    0,  524,    2, 0x0a /* Public */,
      18,    1,  525,    2, 0x0a /* Public */,
      19,    0,  528,    2, 0x0a /* Public */,
      20,    1,  529,    2, 0x0a /* Public */,
      22,    0,  532,    2, 0x0a /* Public */,
      23,    1,  533,    2, 0x0a /* Public */,
      25,    0,  536,    2, 0x0a /* Public */,
      26,    1,  537,    2, 0x0a /* Public */,
      27,    0,  540,    2, 0x0a /* Public */,
      28,    1,  541,    2, 0x0a /* Public */,
      29,    0,  544,    2, 0x0a /* Public */,
      30,    1,  545,    2, 0x0a /* Public */,
      32,    1,  548,    2, 0x0a /* Public */,
      33,    0,  551,    2, 0x0a /* Public */,
      34,    1,  552,    2, 0x0a /* Public */,
      36,    0,  555,    2, 0x0a /* Public */,
      37,    1,  556,    2, 0x0a /* Public */,
      38,    0,  559,    2, 0x0a /* Public */,
      39,    1,  560,    2, 0x0a /* Public */,
      41,    0,  563,    2, 0x0a /* Public */,
      42,    1,  564,    2, 0x0a /* Public */,
      44,    0,  567,    2, 0x0a /* Public */,
      45,    1,  568,    2, 0x0a /* Public */,
      48,    0,  571,    2, 0x0a /* Public */,
      49,    1,  572,    2, 0x0a /* Public */,
      51,    0,  575,    2, 0x0a /* Public */,
      52,    1,  576,    2, 0x0a /* Public */,
      54,    0,  579,    2, 0x0a /* Public */,
      55,    1,  580,    2, 0x0a /* Public */,
      57,    0,  583,    2, 0x0a /* Public */,
      58,    1,  584,    2, 0x0a /* Public */,
      60,    1,  587,    2, 0x0a /* Public */,
      61,    0,  590,    2, 0x0a /* Public */,
      62,    1,  591,    2, 0x0a /* Public */,
      63,    0,  594,    2, 0x0a /* Public */,
      64,    1,  595,    2, 0x0a /* Public */,
      65,    0,  598,    2, 0x0a /* Public */,
      66,    1,  599,    2, 0x0a /* Public */,
      68,    0,  602,    2, 0x0a /* Public */,
      69,    1,  603,    2, 0x0a /* Public */,
      71,    0,  606,    2, 0x0a /* Public */,
      72,    1,  607,    2, 0x0a /* Public */,
      75,    0,  610,    2, 0x0a /* Public */,
      76,    1,  611,    2, 0x0a /* Public */,
      77,    0,  614,    2, 0x0a /* Public */,
      78,    1,  615,    2, 0x0a /* Public */,
      79,    0,  618,    2, 0x0a /* Public */,
      80,    1,  619,    2, 0x0a /* Public */,
      81,    0,  622,    2, 0x0a /* Public */,
      82,    1,  623,    2, 0x0a /* Public */,
      83,    0,  626,    2, 0x0a /* Public */,
      84,    1,  627,    2, 0x0a /* Public */,
      85,    0,  630,    2, 0x0a /* Public */,
      86,    1,  631,    2, 0x0a /* Public */,
      88,    0,  634,    2, 0x0a /* Public */,
      89,    1,  635,    2, 0x0a /* Public */,
      90,    0,  638,    2, 0x0a /* Public */,
      91,    0,  639,    2, 0x0a /* Public */,
      92,    0,  640,    2, 0x0a /* Public */,
      93,    2,  641,    2, 0x0a /* Public */,
      97,    4,  646,    2, 0x0a /* Public */,
     100,    4,  655,    2, 0x0a /* Public */,
     103,    2,  664,    2, 0x0a /* Public */,
     104,    0,  669,    2, 0x0a /* Public */,
     105,    0,  670,    2, 0x0a /* Public */,
     106,    2,  671,    2, 0x0a /* Public */,
     107,    1,  676,    2, 0x0a /* Public */,
     110,    0,  679,    2, 0x0a /* Public */,
     112,    1,  680,    2, 0x0a /* Public */,
     114,    0,  683,    2, 0x0a /* Public */,
     116,    1,  684,    2, 0x0a /* Public */,
     118,    0,  687,    2, 0x0a /* Public */,
     119,    1,  688,    2, 0x0a /* Public */,
     120,    0,  691,    2, 0x0a /* Public */,
     121,    1,  692,    2, 0x0a /* Public */,
     123,    0,  695,    2, 0x0a /* Public */,
     124,    1,  696,    2, 0x0a /* Public */,
     126,    1,  699,    2, 0x0a /* Public */,
     128,    0,  702,    2, 0x0a /* Public */,
     129,    0,  703,    2, 0x0a /* Public */,
     130,    1,  704,    2, 0x0a /* Public */,
     132,    1,  707,    2, 0x0a /* Public */,
     134,    0,  710,    2, 0x0a /* Public */,
     135,    0,  711,    2, 0x0a /* Public */,
     136,    1,  712,    2, 0x0a /* Public */,
     138,    0,  715,    2, 0x0a /* Public */,
     139,    0,  716,    2, 0x0a /* Public */,
     140,    1,  717,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Bool,   21,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,   24,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Bool,   24,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Bool,   24,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,   31,
    QMetaType::Void, QMetaType::Bool,   24,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int,   35,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   40,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   43,
    QMetaType::Int,
    QMetaType::Void, 0x80000000 | 46,   47,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   50,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   53,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   56,
    QMetaType::Double,
    QMetaType::Void, QMetaType::Int,   59,
    QMetaType::Void, QMetaType::Bool,   24,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int,   40,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   59,
    QMetaType::Double,
    QMetaType::Void, QMetaType::Int,   67,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   70,
    QMetaType::Int,
    QMetaType::Void, 0x80000000 | 73,   74,
    0x80000000 | 73,
    QMetaType::Void, QMetaType::Bool,   24,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int,   40,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   59,
    QMetaType::Double,
    QMetaType::Void, QMetaType::Int,   67,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   70,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Bool,   87,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Int,
    0x80000000 | 5,
    0x80000000 | 46,
    QMetaType::Int, 0x80000000 | 94, 0x80000000 | 94,   95,   96,
    QMetaType::Int, 0x80000000 | 94, 0x80000000 | 94, QMetaType::Int, QMetaType::Int,   95,   96,   98,   99,
    QMetaType::Int, QMetaType::QString, QMetaType::QImage, QMetaType::Int, QMetaType::Int,  101,  102,   98,   99,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   98,   99,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QImage, QMetaType::Int, QMetaType::Int,   98,   99,
    QMetaType::Void, 0x80000000 | 108,  109,
    0x80000000 | 111,
    QMetaType::Void, QMetaType::QVector3D,  113,
    0x80000000 | 115,
    QMetaType::Void, QMetaType::QVector3D,  117,
    0x80000000 | 115,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Float,  122,
    QMetaType::Float,
    QMetaType::Void, QMetaType::Float,  125,
    QMetaType::Void, QMetaType::Float,  127,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Void, QMetaType::Bool,  131,
    QMetaType::Void, QMetaType::Bool,  133,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,  137,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,  141,

       0        // eod
};

void ImageProcessor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ImageProcessor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->processed(); break;
        case 1: _t->on_idle(); break;
        case 2: _t->copy_settings((*reinterpret_cast< ProcessorSettings(*)>(_a[1]))); break;
        case 3: _t->set_normal_depth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: { int _r = _t->get_normal_depth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->set_normal_blur_radius((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: { int _r = _t->get_normal_blur_radius();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->set_normal_bisel_depth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: { int _r = _t->get_normal_bisel_depth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->set_normal_bisel_distance((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: { int _r = _t->get_normal_bisel_distance();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 11: _t->set_normal_bisel_blur_radius((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: { int _r = _t->get_normal_bisel_blur_radius();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 13: _t->set_normal_bisel_soft((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: { bool _r = _t->get_normal_bisel_soft();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 15: _t->set_normal_invert_x((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: { int _r = _t->get_normal_invert_x();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 17: _t->set_normal_invert_y((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: { int _r = _t->get_normal_invert_y();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 19: _t->set_normal_invert_z((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 20: { bool _r = _t->get_tileable();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 21: _t->set_tileable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 22: _t->set_parallax_invert((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 23: { bool _r = _t->get_parallax_invert();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 24: _t->set_parallax_focus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: { int _r = _t->get_parallax_focus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 26: _t->set_parallax_soft((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: { int _r = _t->get_parallax_soft();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 28: _t->set_parallax_thresh((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 29: { int _r = _t->get_parallax_thresh();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 30: _t->set_parallax_min((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 31: { int _r = _t->get_parallax_min();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 32: _t->set_parallax_type((*reinterpret_cast< ParallaxType(*)>(_a[1]))); break;
        case 33: { int _r = _t->get_parallax_quantization();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 34: _t->set_parallax_quantization((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 35: { int _r = _t->get_parallax_erode_dilate();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 36: _t->set_parallax_erode_dilate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 37: { int _r = _t->get_parallax_brightness();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 38: _t->set_parallax_brightness((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 39: { double _r = _t->get_parallax_contrast();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 40: _t->set_parallax_contrast((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 41: _t->set_specular_invert((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 42: { bool _r = _t->get_specular_invert();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 43: _t->set_specular_thresh((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 44: { int _r = _t->get_specular_trhesh();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 45: _t->set_specular_contrast((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 46: { double _r = _t->get_specular_contrast();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 47: _t->set_specular_bright((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 48: { int _r = _t->get_specular_bright();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 49: _t->set_specular_blur((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 50: { int _r = _t->get_specular_blur();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 51: _t->set_specular_base_color((*reinterpret_cast< Vec4b(*)>(_a[1]))); break;
        case 52: { Vec4b _r = _t->get_specular_base_color();
            if (_a[0]) *reinterpret_cast< Vec4b*>(_a[0]) = std::move(_r); }  break;
        case 53: _t->set_occlusion_invert((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 54: { bool _r = _t->get_occlusion_invert();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 55: _t->set_occlusion_thresh((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 56: { int _r = _t->get_occlusion_trhesh();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 57: _t->set_occlusion_contrast((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 58: { double _r = _t->get_occlusion_contrast();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 59: _t->set_occlusion_bright((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 60: { int _r = _t->get_occlusion_bright();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 61: _t->set_occlusion_blur((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 62: { int _r = _t->get_occlusion_blur();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 63: _t->set_occlusion_distance_mode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 64: { bool _r = _t->get_occlusion_distance_mode();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 65: _t->set_occlusion_distance((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 66: { int _r = _t->get_occlusion_distance();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 67: { ProcessorSettings _r = _t->get_settings();
            if (_a[0]) *reinterpret_cast< ProcessorSettings*>(_a[0]) = std::move(_r); }  break;
        case 68: { ParallaxType _r = _t->get_parallax_type();
            if (_a[0]) *reinterpret_cast< ParallaxType*>(_a[0]) = std::move(_r); }  break;
        case 69: { int _r = _t->fill_neighbours((*reinterpret_cast< Mat(*)>(_a[1])),(*reinterpret_cast< Mat(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 70: { int _r = _t->set_neighbour((*reinterpret_cast< Mat(*)>(_a[1])),(*reinterpret_cast< Mat(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 71: { int _r = _t->set_neighbour_image((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QImage(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 72: { int _r = _t->empty_neighbour((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 73: _t->reset_neighbours(); break;
        case 74: _t->set_current_heightmap(); break;
        case 75: { QImage _r = _t->get_neighbour((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QImage*>(_a[0]) = std::move(_r); }  break;
        case 76: _t->set_light_list((*reinterpret_cast< QList<LightSource*>(*)>(_a[1]))); break;
        case 77: { QList<LightSource*>* _r = _t->get_light_list_ptr();
            if (_a[0]) *reinterpret_cast< QList<LightSource*>**>(_a[0]) = std::move(_r); }  break;
        case 78: _t->set_position((*reinterpret_cast< QVector3D(*)>(_a[1]))); break;
        case 79: { QVector3D* _r = _t->get_position();
            if (_a[0]) *reinterpret_cast< QVector3D**>(_a[0]) = std::move(_r); }  break;
        case 80: _t->set_offset((*reinterpret_cast< QVector3D(*)>(_a[1]))); break;
        case 81: { QVector3D* _r = _t->get_offset();
            if (_a[0]) *reinterpret_cast< QVector3D**>(_a[0]) = std::move(_r); }  break;
        case 82: _t->set_selected((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 83: { bool _r = _t->get_selected();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 84: _t->set_zoom((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 85: { float _r = _t->get_zoom();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 86: _t->set_sx((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 87: _t->set_sy((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 88: { float _r = _t->get_sx();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 89: { float _r = _t->get_sy();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 90: _t->set_tile_x((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 91: _t->set_tile_y((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 92: { bool _r = _t->get_tile_x();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 93: { bool _r = _t->get_tile_y();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 94: _t->set_is_parallax((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 95: { bool _r = _t->get_is_parallax();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 96: { bool _r = _t->get_connected();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 97: _t->set_connected((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ImageProcessor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ImageProcessor::processed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ImageProcessor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ImageProcessor::on_idle)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ImageProcessor::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_ImageProcessor.data,
    qt_meta_data_ImageProcessor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ImageProcessor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ImageProcessor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ImageProcessor.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ImageProcessor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 98)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 98;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 98)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 98;
    }
    return _id;
}

// SIGNAL 0
void ImageProcessor::processed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ImageProcessor::on_idle()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
