/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[65];
    char stringdata0[1372];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 20), // "normal_depth_changed"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 5), // "value"
QT_MOC_LITERAL(4, 39, 12), // "update_scene"
QT_MOC_LITERAL(5, 52, 13), // "add_processor"
QT_MOC_LITERAL(6, 66, 15), // "ImageProcessor*"
QT_MOC_LITERAL(7, 82, 1), // "p"
QT_MOC_LITERAL(8, 84, 20), // "selectedLightChanged"
QT_MOC_LITERAL(9, 105, 12), // "LightSource*"
QT_MOC_LITERAL(10, 118, 5), // "light"
QT_MOC_LITERAL(11, 124, 15), // "stopAddingLight"
QT_MOC_LITERAL(12, 140, 15), // "set_light_color"
QT_MOC_LITERAL(13, 156, 5), // "color"
QT_MOC_LITERAL(14, 162, 17), // "set_ambient_color"
QT_MOC_LITERAL(15, 180, 20), // "set_background_color"
QT_MOC_LITERAL(16, 201, 25), // "selectedProcessorsChanged"
QT_MOC_LITERAL(17, 227, 22), // "QList<ImageProcessor*>"
QT_MOC_LITERAL(18, 250, 4), // "list"
QT_MOC_LITERAL(19, 255, 18), // "processor_selected"
QT_MOC_LITERAL(20, 274, 9), // "processor"
QT_MOC_LITERAL(21, 284, 8), // "selected"
QT_MOC_LITERAL(22, 293, 24), // "set_enabled_map_controls"
QT_MOC_LITERAL(23, 318, 1), // "e"
QT_MOC_LITERAL(24, 320, 17), // "connect_processor"
QT_MOC_LITERAL(25, 338, 20), // "disconnect_processor"
QT_MOC_LITERAL(26, 359, 28), // "showContextMenuForListWidget"
QT_MOC_LITERAL(27, 388, 3), // "pos"
QT_MOC_LITERAL(28, 392, 26), // "list_menu_action_triggered"
QT_MOC_LITERAL(29, 419, 8), // "QAction*"
QT_MOC_LITERAL(30, 428, 6), // "action"
QT_MOC_LITERAL(31, 435, 18), // "openGL_initialized"
QT_MOC_LITERAL(32, 454, 23), // "on_actionOpen_triggered"
QT_MOC_LITERAL(33, 478, 26), // "on_actionFitZoom_triggered"
QT_MOC_LITERAL(34, 505, 27), // "on_actionZoom_100_triggered"
QT_MOC_LITERAL(35, 533, 25), // "on_actionZoomIn_triggered"
QT_MOC_LITERAL(36, 559, 26), // "on_actionZoomOut_triggered"
QT_MOC_LITERAL(37, 586, 25), // "on_actionExport_triggered"
QT_MOC_LITERAL(38, 612, 26), // "on_pushButtonColor_clicked"
QT_MOC_LITERAL(39, 639, 42), // "on_horizontalSliderDiffHeight..."
QT_MOC_LITERAL(40, 682, 41), // "on_horizontalSliderDiffLight_..."
QT_MOC_LITERAL(41, 724, 44), // "on_horizontalSliderAmbientLig..."
QT_MOC_LITERAL(42, 769, 33), // "on_pushButtonAmbientColor_cli..."
QT_MOC_LITERAL(43, 803, 27), // "on_actionLicencia_triggered"
QT_MOC_LITERAL(44, 831, 34), // "on_actionReconocimientos_trig..."
QT_MOC_LITERAL(45, 866, 34), // "on_listWidget_itemSelectionCh..."
QT_MOC_LITERAL(46, 901, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(47, 923, 36), // "on_pushButtonBackgroundColor_..."
QT_MOC_LITERAL(48, 960, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(49, 984, 31), // "on_comboBox_currentIndexChanged"
QT_MOC_LITERAL(50, 1016, 5), // "index"
QT_MOC_LITERAL(51, 1022, 29), // "on_pushButtonExportTo_clicked"
QT_MOC_LITERAL(52, 1052, 10), // "open_files"
QT_MOC_LITERAL(53, 1063, 9), // "fileNames"
QT_MOC_LITERAL(54, 1073, 26), // "on_actionPresets_triggered"
QT_MOC_LITERAL(55, 1100, 36), // "on_horizontalSliderSpec_value..."
QT_MOC_LITERAL(56, 1137, 43), // "on_horizontalSliderSpecScatte..."
QT_MOC_LITERAL(57, 1181, 35), // "on_comboBoxView_currentIndexC..."
QT_MOC_LITERAL(58, 1217, 32), // "on_actionExportPreview_triggered"
QT_MOC_LITERAL(59, 1250, 24), // "on_actionAbout_triggered"
QT_MOC_LITERAL(60, 1275, 28), // "on_actionAdd_Light_triggered"
QT_MOC_LITERAL(61, 1304, 7), // "checked"
QT_MOC_LITERAL(62, 1312, 35), // "on_checkBoxLightsPerTexture_t..."
QT_MOC_LITERAL(63, 1348, 13), // "onFileChanged"
QT_MOC_LITERAL(64, 1362, 9) // "file_path"

    },
    "MainWindow\0normal_depth_changed\0\0value\0"
    "update_scene\0add_processor\0ImageProcessor*\0"
    "p\0selectedLightChanged\0LightSource*\0"
    "light\0stopAddingLight\0set_light_color\0"
    "color\0set_ambient_color\0set_background_color\0"
    "selectedProcessorsChanged\0"
    "QList<ImageProcessor*>\0list\0"
    "processor_selected\0processor\0selected\0"
    "set_enabled_map_controls\0e\0connect_processor\0"
    "disconnect_processor\0showContextMenuForListWidget\0"
    "pos\0list_menu_action_triggered\0QAction*\0"
    "action\0openGL_initialized\0"
    "on_actionOpen_triggered\0"
    "on_actionFitZoom_triggered\0"
    "on_actionZoom_100_triggered\0"
    "on_actionZoomIn_triggered\0"
    "on_actionZoomOut_triggered\0"
    "on_actionExport_triggered\0"
    "on_pushButtonColor_clicked\0"
    "on_horizontalSliderDiffHeight_valueChanged\0"
    "on_horizontalSliderDiffLight_valueChanged\0"
    "on_horizontalSliderAmbientLight_valueChanged\0"
    "on_pushButtonAmbientColor_clicked\0"
    "on_actionLicencia_triggered\0"
    "on_actionReconocimientos_triggered\0"
    "on_listWidget_itemSelectionChanged\0"
    "on_pushButton_clicked\0"
    "on_pushButtonBackgroundColor_clicked\0"
    "on_pushButton_2_clicked\0"
    "on_comboBox_currentIndexChanged\0index\0"
    "on_pushButtonExportTo_clicked\0open_files\0"
    "fileNames\0on_actionPresets_triggered\0"
    "on_horizontalSliderSpec_valueChanged\0"
    "on_horizontalSliderSpecScatter_valueChanged\0"
    "on_comboBoxView_currentIndexChanged\0"
    "on_actionExportPreview_triggered\0"
    "on_actionAbout_triggered\0"
    "on_actionAdd_Light_triggered\0checked\0"
    "on_checkBoxLightsPerTexture_toggled\0"
    "onFileChanged\0file_path"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      45,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  239,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,  242,    2, 0x0a /* Public */,
       5,    1,  243,    2, 0x0a /* Public */,
       8,    1,  246,    2, 0x0a /* Public */,
      11,    0,  249,    2, 0x0a /* Public */,
      12,    1,  250,    2, 0x0a /* Public */,
      14,    1,  253,    2, 0x0a /* Public */,
      15,    1,  256,    2, 0x0a /* Public */,
      16,    1,  259,    2, 0x0a /* Public */,
      19,    2,  262,    2, 0x0a /* Public */,
      22,    1,  267,    2, 0x0a /* Public */,
      24,    1,  270,    2, 0x08 /* Private */,
      25,    1,  273,    2, 0x08 /* Private */,
      26,    1,  276,    2, 0x08 /* Private */,
      28,    1,  279,    2, 0x08 /* Private */,
      31,    0,  282,    2, 0x08 /* Private */,
      32,    0,  283,    2, 0x08 /* Private */,
      33,    0,  284,    2, 0x08 /* Private */,
      34,    0,  285,    2, 0x08 /* Private */,
      35,    0,  286,    2, 0x08 /* Private */,
      36,    0,  287,    2, 0x08 /* Private */,
      37,    0,  288,    2, 0x08 /* Private */,
      38,    0,  289,    2, 0x08 /* Private */,
      39,    1,  290,    2, 0x08 /* Private */,
      40,    1,  293,    2, 0x08 /* Private */,
      41,    1,  296,    2, 0x08 /* Private */,
      42,    0,  299,    2, 0x08 /* Private */,
      43,    0,  300,    2, 0x08 /* Private */,
      44,    0,  301,    2, 0x08 /* Private */,
      45,    0,  302,    2, 0x08 /* Private */,
      46,    0,  303,    2, 0x08 /* Private */,
      47,    0,  304,    2, 0x08 /* Private */,
      48,    0,  305,    2, 0x08 /* Private */,
      49,    1,  306,    2, 0x08 /* Private */,
      51,    0,  309,    2, 0x08 /* Private */,
      52,    1,  310,    2, 0x08 /* Private */,
      54,    0,  313,    2, 0x08 /* Private */,
      55,    1,  314,    2, 0x08 /* Private */,
      56,    1,  317,    2, 0x08 /* Private */,
      57,    1,  320,    2, 0x08 /* Private */,
      58,    0,  323,    2, 0x08 /* Private */,
      59,    0,  324,    2, 0x08 /* Private */,
      60,    1,  325,    2, 0x08 /* Private */,
      62,    1,  328,    2, 0x08 /* Private */,
      63,    1,  331,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QColor,   13,
    QMetaType::Void, QMetaType::QColor,   13,
    QMetaType::Void, QMetaType::QColor,   13,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, 0x80000000 | 6, QMetaType::Bool,   20,   21,
    QMetaType::Void, QMetaType::Bool,   23,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::QPoint,   27,
    QMetaType::Void, 0x80000000 | 29,   30,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   50,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,   53,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,   50,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::QString,   64,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->normal_depth_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->update_scene(); break;
        case 2: _t->add_processor((*reinterpret_cast< ImageProcessor*(*)>(_a[1]))); break;
        case 3: _t->selectedLightChanged((*reinterpret_cast< LightSource*(*)>(_a[1]))); break;
        case 4: _t->stopAddingLight(); break;
        case 5: _t->set_light_color((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 6: _t->set_ambient_color((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 7: _t->set_background_color((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 8: _t->selectedProcessorsChanged((*reinterpret_cast< QList<ImageProcessor*>(*)>(_a[1]))); break;
        case 9: _t->processor_selected((*reinterpret_cast< ImageProcessor*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 10: _t->set_enabled_map_controls((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->connect_processor((*reinterpret_cast< ImageProcessor*(*)>(_a[1]))); break;
        case 12: _t->disconnect_processor((*reinterpret_cast< ImageProcessor*(*)>(_a[1]))); break;
        case 13: _t->showContextMenuForListWidget((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 14: _t->list_menu_action_triggered((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 15: _t->openGL_initialized(); break;
        case 16: _t->on_actionOpen_triggered(); break;
        case 17: _t->on_actionFitZoom_triggered(); break;
        case 18: _t->on_actionZoom_100_triggered(); break;
        case 19: _t->on_actionZoomIn_triggered(); break;
        case 20: _t->on_actionZoomOut_triggered(); break;
        case 21: _t->on_actionExport_triggered(); break;
        case 22: _t->on_pushButtonColor_clicked(); break;
        case 23: _t->on_horizontalSliderDiffHeight_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: _t->on_horizontalSliderDiffLight_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->on_horizontalSliderAmbientLight_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: _t->on_pushButtonAmbientColor_clicked(); break;
        case 27: _t->on_actionLicencia_triggered(); break;
        case 28: _t->on_actionReconocimientos_triggered(); break;
        case 29: _t->on_listWidget_itemSelectionChanged(); break;
        case 30: _t->on_pushButton_clicked(); break;
        case 31: _t->on_pushButtonBackgroundColor_clicked(); break;
        case 32: _t->on_pushButton_2_clicked(); break;
        case 33: _t->on_comboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 34: _t->on_pushButtonExportTo_clicked(); break;
        case 35: _t->open_files((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 36: _t->on_actionPresets_triggered(); break;
        case 37: _t->on_horizontalSliderSpec_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 38: _t->on_horizontalSliderSpecScatter_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 39: _t->on_comboBoxView_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 40: _t->on_actionExportPreview_triggered(); break;
        case 41: _t->on_actionAbout_triggered(); break;
        case 42: _t->on_actionAdd_Light_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 43: _t->on_checkBoxLightsPerTexture_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 44: _t->onFileChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ImageProcessor* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< LightSource* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<ImageProcessor*> >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ImageProcessor* >(); break;
            }
            break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ImageProcessor* >(); break;
            }
            break;
        case 12:
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
            using _t = void (MainWindow::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::normal_depth_changed)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 45)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 45;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 45)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 45;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::normal_depth_changed(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
