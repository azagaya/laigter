/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "src/openglwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionFitZoom;
    QAction *actionZoom_100;
    QAction *actionZoomIn;
    QAction *actionZoomOut;
    QAction *actionExport;
    QAction *actionPresets;
    QAction *actionExportPreview;
    QAction *actionAbout;
    QAction *actionAdd_Light;
    QWidget *centralWidget;
    QGridLayout *gridLayout_5;
    OpenGlWidget *openGLPreviewWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *normalDockWidget;
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout_7;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QSlider *normalDepthSlider;
    QLabel *label_2;
    QSlider *normalBlurSlider;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_8;
    QCheckBox *normalInvertX;
    QCheckBox *normalInvertY;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_6;
    QFormLayout *formLayout_2;
    QLabel *label_5;
    QSlider *normalBevelSlider;
    QLabel *label_3;
    QSlider *normalBiselDistanceSlider;
    QLabel *label_4;
    QSlider *normalBiselBlurSlider;
    QRadioButton *biselSoftRadio;
    QRadioButton *biselAbruptRadio;
    QDockWidget *dockWidget_2;
    QWidget *dockWidgetContents_2;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QTabWidget *tabWidget;
    QWidget *tabDif;
    QGridLayout *gridLayout_16;
    QLabel *label_6;
    QSlider *horizontalSliderDiffLight;
    QWidget *tabSpec;
    QGridLayout *gridLayout_9;
    QLabel *label_12;
    QLabel *label_13;
    QSlider *horizontalSliderSpec;
    QSlider *horizontalSliderSpecScatter;
    QWidget *tabAmb;
    QGridLayout *gridLayout_17;
    QLabel *label_11;
    QSlider *horizontalSliderAmbientLight;
    QLabel *label_9;
    QPushButton *pushButtonAmbientColor;
    QLabel *label_10;
    QPushButton *pushButtonBackgroundColor;
    QLabel *label_8;
    QSlider *horizontalSliderDiffHeight;
    QLabel *label_7;
    QPushButton *pushButtonColor;
    QCheckBox *checkBoxLightsPerTexture;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_3;
    QLabel *label_24;
    QComboBox *comboBoxView;
    QFrame *line;
    QCheckBox *checkBoxPixelated;
    QGroupBox *groupBox_Tile_Preview;
    QGridLayout *gridLayout_12;
    QCheckBox *checkBoxMosaicoY;
    QCheckBox *checkBoxMosaicoX;
    QCheckBox *checkBoxParallax;
    QSlider *sliderParallax;
    QDockWidget *dockWidgetTextures;
    QWidget *dockWidgetContents_3;
    QGridLayout *gridLayout_10;
    QListWidget *listWidget;
    QDockWidget *parallaxDockWidget;
    QWidget *dockWidgetContents_4;
    QGridLayout *gridLayout_14;
    QLabel *label_16;
    QComboBox *comboBox;
    QGroupBox *groupBox_9;
    QGridLayout *gridLayout_15;
    QSpacerItem *horizontalSpacer_2;
    QLabel *labelQuantization;
    QLabel *labelThreshParallax;
    QLabel *labelThreshMin;
    QLabel *labelThreshSoft;
    QSlider *sliderParallaxBright;
    QLabel *labelContrast;
    QSlider *parallaxFocusSlider;
    QCheckBox *checkBoxParallaxInvert;
    QLabel *labelThreshFocus;
    QLabel *labelBrightness;
    QSlider *parallaxMinHeight;
    QSlider *parallaxSoftSlider;
    QSlider *parallaxThreshSlider;
    QSlider *parallaxQuantizationSlider;
    QSlider *sliderParallaxContrast;
    QLabel *labelErodeDilate;
    QSlider *sliderParallaxErodeDilate;
    QDockWidget *specularDockWidget;
    QWidget *dockWidgetContents_5;
    QGridLayout *gridLayout_18;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_19;
    QSlider *sliderSpecThresh;
    QLabel *label_15;
    QLabel *label_18;
    QSlider *sliderSpecBright;
    QSlider *sliderSpecSoft;
    QSpacerItem *horizontalSpacer;
    QLabel *label_17;
    QCheckBox *checkBoxSpecInvert;
    QLabel *label_19;
    QSlider *sliderSpecContrast;
    QDockWidget *occlusionDockWidget;
    QWidget *dockWidgetContents_6;
    QGridLayout *gridLayout_21;
    QGroupBox *groupBox_10;
    QGridLayout *gridLayout_20;
    QCheckBox *checkBoxOcclusionInvert;
    QLabel *label_23;
    QSlider *sliderOcclusionBright;
    QSlider *sliderOcclusionSoft;
    QSlider *sliderOcclusionThresh;
    QLabel *label_21;
    QSpacerItem *horizontalSpacer_3;
    QSlider *sliderOcclusionContrast;
    QLabel *label_22;
    QLabel *label_20;
    QCheckBox *checkBoxOcclusionDistance;
    QSlider *sliderOcclusionDistance;
    QDockWidget *TileDockWidget;
    QWidget *dockWidgetContents_7;
    QGridLayout *gridLayout_22;
    QGroupBox *groupBox_8;
    QGridLayout *gridLayout_13;
    QPushButton *pushButton_2;
    QCheckBox *checkBoxTileable;
    QDockWidget *dockWidgetExport;
    QWidget *dockWidgetContents_9;
    QGridLayout *gridLayout_23;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_11;
    QCheckBox *checkBoxExportNormal;
    QCheckBox *checkBoxExportSpecular;
    QCheckBox *checkBoxExportOcclusion;
    QCheckBox *checkBoxExportParallax;
    QCheckBox *checkBoxExportPreview;
    QPushButton *pushButtonExportTo;
    QPushButton *pushButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1200, 1311);
        MainWindow->setWindowOpacity(1.000000000000000);
        MainWindow->setStyleSheet(QString::fromUtf8("QDockWidget{\n"
"	color: rgb(235, 235, 235);\n"
"    border: 1px solid black;\n"
"    titlebar-close-icon: url(close.png);\n"
"    titlebar-normal-icon: url(undock.png);\n"
"	margin: 0px\n"
"}\n"
"QDockWidget::title{\n"
"	background: rgb(40%, 40%, 50%);\n"
"	border-radius:4px;\n"
"	margin:2px;\n"
"	padding: 3px\n"
"}\n"
""));
        MainWindow->setDockNestingEnabled(true);
        MainWindow->setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon);
        actionFitZoom = new QAction(MainWindow);
        actionFitZoom->setObjectName(QString::fromUtf8("actionFitZoom"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/zoomfit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFitZoom->setIcon(icon1);
        actionZoom_100 = new QAction(MainWindow);
        actionZoom_100->setObjectName(QString::fromUtf8("actionZoom_100"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/zoom100.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_100->setIcon(icon2);
        actionZoomIn = new QAction(MainWindow);
        actionZoomIn->setObjectName(QString::fromUtf8("actionZoomIn"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/zoom+.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoomIn->setIcon(icon3);
        actionZoomOut = new QAction(MainWindow);
        actionZoomOut->setObjectName(QString::fromUtf8("actionZoomOut"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/zoom-.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoomOut->setIcon(icon4);
        actionExport = new QAction(MainWindow);
        actionExport->setObjectName(QString::fromUtf8("actionExport"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/export.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExport->setIcon(icon5);
        actionPresets = new QAction(MainWindow);
        actionPresets->setObjectName(QString::fromUtf8("actionPresets"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/presets.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPresets->setIcon(icon6);
        actionExportPreview = new QAction(MainWindow);
        actionExportPreview->setObjectName(QString::fromUtf8("actionExportPreview"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/export-preview.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExportPreview->setIcon(icon7);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icons/info.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon8);
        actionAdd_Light = new QAction(MainWindow);
        actionAdd_Light->setObjectName(QString::fromUtf8("actionAdd_Light"));
        actionAdd_Light->setCheckable(true);
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/icons/add-light.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAdd_Light->setIcon(icon9);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_5 = new QGridLayout(centralWidget);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        openGLPreviewWidget = new OpenGlWidget(centralWidget);
        openGLPreviewWidget->setObjectName(QString::fromUtf8("openGLPreviewWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(openGLPreviewWidget->sizePolicy().hasHeightForWidth());
        openGLPreviewWidget->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(openGLPreviewWidget, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1200, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        normalDockWidget = new QDockWidget(MainWindow);
        normalDockWidget->setObjectName(QString::fromUtf8("normalDockWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(normalDockWidget->sizePolicy().hasHeightForWidth());
        normalDockWidget->setSizePolicy(sizePolicy1);
        normalDockWidget->setFeatures(QDockWidget::DockWidgetMovable);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        gridLayout_7 = new QGridLayout(dockWidgetContents);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        groupBox_2 = new QGroupBox(dockWidgetContents);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMaximumSize(QSize(16777215, 16777215));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        normalDepthSlider = new QSlider(groupBox_2);
        normalDepthSlider->setObjectName(QString::fromUtf8("normalDepthSlider"));
        normalDepthSlider->setMinimum(0);
        normalDepthSlider->setMaximum(1000);
        normalDepthSlider->setValue(100);
        normalDepthSlider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(0, QFormLayout::FieldRole, normalDepthSlider);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        normalBlurSlider = new QSlider(groupBox_2);
        normalBlurSlider->setObjectName(QString::fromUtf8("normalBlurSlider"));
        normalBlurSlider->setMinimum(0);
        normalBlurSlider->setMaximum(40);
        normalBlurSlider->setSingleStep(1);
        normalBlurSlider->setValue(5);
        normalBlurSlider->setOrientation(Qt::Horizontal);

        formLayout->setWidget(1, QFormLayout::FieldRole, normalBlurSlider);


        gridLayout->addLayout(formLayout, 0, 0, 1, 1);


        gridLayout_7->addWidget(groupBox_2, 0, 0, 1, 1);

        groupBox_4 = new QGroupBox(dockWidgetContents);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setMaximumSize(QSize(16777215, 16777215));
        gridLayout_8 = new QGridLayout(groupBox_4);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        normalInvertX = new QCheckBox(groupBox_4);
        normalInvertX->setObjectName(QString::fromUtf8("normalInvertX"));

        gridLayout_8->addWidget(normalInvertX, 0, 0, 1, 1);

        normalInvertY = new QCheckBox(groupBox_4);
        normalInvertY->setObjectName(QString::fromUtf8("normalInvertY"));

        gridLayout_8->addWidget(normalInvertY, 0, 1, 1, 1);


        gridLayout_7->addWidget(groupBox_4, 2, 0, 1, 1);

        groupBox_3 = new QGroupBox(dockWidgetContents);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setMaximumSize(QSize(16777215, 16777215));
        gridLayout_6 = new QGridLayout(groupBox_3);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        formLayout_2 = new QFormLayout();
        formLayout_2->setSpacing(6);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_5);

        normalBevelSlider = new QSlider(groupBox_3);
        normalBevelSlider->setObjectName(QString::fromUtf8("normalBevelSlider"));
        normalBevelSlider->setMaximum(4000);
        normalBevelSlider->setValue(1000);
        normalBevelSlider->setOrientation(Qt::Horizontal);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, normalBevelSlider);

        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_3);

        normalBiselDistanceSlider = new QSlider(groupBox_3);
        normalBiselDistanceSlider->setObjectName(QString::fromUtf8("normalBiselDistanceSlider"));
        normalBiselDistanceSlider->setMaximum(255);
        normalBiselDistanceSlider->setValue(60);
        normalBiselDistanceSlider->setOrientation(Qt::Horizontal);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, normalBiselDistanceSlider);

        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_4);

        normalBiselBlurSlider = new QSlider(groupBox_3);
        normalBiselBlurSlider->setObjectName(QString::fromUtf8("normalBiselBlurSlider"));
        normalBiselBlurSlider->setMinimum(0);
        normalBiselBlurSlider->setMaximum(40);
        normalBiselBlurSlider->setSingleStep(1);
        normalBiselBlurSlider->setValue(10);
        normalBiselBlurSlider->setOrientation(Qt::Horizontal);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, normalBiselBlurSlider);

        biselSoftRadio = new QRadioButton(groupBox_3);
        biselSoftRadio->setObjectName(QString::fromUtf8("biselSoftRadio"));
        biselSoftRadio->setChecked(true);

        formLayout_2->setWidget(3, QFormLayout::LabelRole, biselSoftRadio);

        biselAbruptRadio = new QRadioButton(groupBox_3);
        biselAbruptRadio->setObjectName(QString::fromUtf8("biselAbruptRadio"));
        biselAbruptRadio->setLayoutDirection(Qt::LeftToRight);

        formLayout_2->setWidget(3, QFormLayout::FieldRole, biselAbruptRadio);


        gridLayout_6->addLayout(formLayout_2, 0, 0, 1, 1);


        gridLayout_7->addWidget(groupBox_3, 1, 0, 1, 1);

        normalDockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(Qt::LeftDockWidgetArea, normalDockWidget);
        dockWidget_2 = new QDockWidget(MainWindow);
        dockWidget_2->setObjectName(QString::fromUtf8("dockWidget_2"));
        sizePolicy1.setHeightForWidth(dockWidget_2->sizePolicy().hasHeightForWidth());
        dockWidget_2->setSizePolicy(sizePolicy1);
        dockWidget_2->setFeatures(QDockWidget::DockWidgetMovable);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
        gridLayout_2 = new QGridLayout(dockWidgetContents_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox = new QGroupBox(dockWidgetContents_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMaximumSize(QSize(16777215, 16777215));
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        tabWidget = new QTabWidget(groupBox);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy2);
        tabWidget->setMinimumSize(QSize(225, 0));
        tabWidget->setMaximumSize(QSize(16777215, 118));
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabDif = new QWidget();
        tabDif->setObjectName(QString::fromUtf8("tabDif"));
        gridLayout_16 = new QGridLayout(tabDif);
        gridLayout_16->setSpacing(6);
        gridLayout_16->setContentsMargins(11, 11, 11, 11);
        gridLayout_16->setObjectName(QString::fromUtf8("gridLayout_16"));
        label_6 = new QLabel(tabDif);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_16->addWidget(label_6, 0, 0, 1, 1);

        horizontalSliderDiffLight = new QSlider(tabDif);
        horizontalSliderDiffLight->setObjectName(QString::fromUtf8("horizontalSliderDiffLight"));
        horizontalSliderDiffLight->setMaximum(400);
        horizontalSliderDiffLight->setValue(60);
        horizontalSliderDiffLight->setOrientation(Qt::Horizontal);

        gridLayout_16->addWidget(horizontalSliderDiffLight, 0, 1, 1, 1);

        tabWidget->addTab(tabDif, QString());
        tabSpec = new QWidget();
        tabSpec->setObjectName(QString::fromUtf8("tabSpec"));
        gridLayout_9 = new QGridLayout(tabSpec);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        gridLayout_9->setHorizontalSpacing(5);
        gridLayout_9->setVerticalSpacing(1);
        gridLayout_9->setContentsMargins(5, 5, 5, 5);
        label_12 = new QLabel(tabSpec);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_9->addWidget(label_12, 0, 0, 1, 1);

        label_13 = new QLabel(tabSpec);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_9->addWidget(label_13, 1, 0, 1, 1);

        horizontalSliderSpec = new QSlider(tabSpec);
        horizontalSliderSpec->setObjectName(QString::fromUtf8("horizontalSliderSpec"));
        horizontalSliderSpec->setMaximum(400);
        horizontalSliderSpec->setValue(60);
        horizontalSliderSpec->setOrientation(Qt::Horizontal);

        gridLayout_9->addWidget(horizontalSliderSpec, 0, 1, 1, 1);

        horizontalSliderSpecScatter = new QSlider(tabSpec);
        horizontalSliderSpecScatter->setObjectName(QString::fromUtf8("horizontalSliderSpecScatter"));
        horizontalSliderSpecScatter->setMinimum(1);
        horizontalSliderSpecScatter->setMaximum(255);
        horizontalSliderSpecScatter->setValue(32);
        horizontalSliderSpecScatter->setOrientation(Qt::Horizontal);

        gridLayout_9->addWidget(horizontalSliderSpecScatter, 1, 1, 1, 1);

        tabWidget->addTab(tabSpec, QString());
        tabAmb = new QWidget();
        tabAmb->setObjectName(QString::fromUtf8("tabAmb"));
        gridLayout_17 = new QGridLayout(tabAmb);
        gridLayout_17->setSpacing(6);
        gridLayout_17->setContentsMargins(11, 11, 11, 11);
        gridLayout_17->setObjectName(QString::fromUtf8("gridLayout_17"));
        label_11 = new QLabel(tabAmb);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_17->addWidget(label_11, 0, 0, 1, 1);

        horizontalSliderAmbientLight = new QSlider(tabAmb);
        horizontalSliderAmbientLight->setObjectName(QString::fromUtf8("horizontalSliderAmbientLight"));
        horizontalSliderAmbientLight->setMaximum(100);
        horizontalSliderAmbientLight->setValue(80);
        horizontalSliderAmbientLight->setOrientation(Qt::Horizontal);

        gridLayout_17->addWidget(horizontalSliderAmbientLight, 0, 1, 1, 1);

        label_9 = new QLabel(tabAmb);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_17->addWidget(label_9, 1, 0, 1, 1);

        pushButtonAmbientColor = new QPushButton(tabAmb);
        pushButtonAmbientColor->setObjectName(QString::fromUtf8("pushButtonAmbientColor"));
        pushButtonAmbientColor->setMinimumSize(QSize(23, 23));
        pushButtonAmbientColor->setMaximumSize(QSize(100, 23));

        gridLayout_17->addWidget(pushButtonAmbientColor, 1, 1, 1, 1);

        label_10 = new QLabel(tabAmb);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_17->addWidget(label_10, 2, 0, 1, 1);

        pushButtonBackgroundColor = new QPushButton(tabAmb);
        pushButtonBackgroundColor->setObjectName(QString::fromUtf8("pushButtonBackgroundColor"));
        pushButtonBackgroundColor->setMinimumSize(QSize(0, 23));
        pushButtonBackgroundColor->setMaximumSize(QSize(100, 23));

        gridLayout_17->addWidget(pushButtonBackgroundColor, 2, 1, 1, 1);

        tabWidget->addTab(tabAmb, QString());

        gridLayout_4->addWidget(tabWidget, 0, 0, 1, 3);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_4->addWidget(label_8, 1, 0, 1, 1);

        horizontalSliderDiffHeight = new QSlider(groupBox);
        horizontalSliderDiffHeight->setObjectName(QString::fromUtf8("horizontalSliderDiffHeight"));
        horizontalSliderDiffHeight->setMinimum(-100);
        horizontalSliderDiffHeight->setMaximum(100);
        horizontalSliderDiffHeight->setValue(30);
        horizontalSliderDiffHeight->setOrientation(Qt::Horizontal);

        gridLayout_4->addWidget(horizontalSliderDiffHeight, 1, 1, 1, 2);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_4->addWidget(label_7, 2, 0, 1, 1);

        pushButtonColor = new QPushButton(groupBox);
        pushButtonColor->setObjectName(QString::fromUtf8("pushButtonColor"));
        pushButtonColor->setMinimumSize(QSize(0, 23));
        pushButtonColor->setMaximumSize(QSize(100, 23));

        gridLayout_4->addWidget(pushButtonColor, 2, 1, 1, 1);

        checkBoxLightsPerTexture = new QCheckBox(groupBox);
        checkBoxLightsPerTexture->setObjectName(QString::fromUtf8("checkBoxLightsPerTexture"));
        checkBoxLightsPerTexture->setChecked(false);

        gridLayout_4->addWidget(checkBoxLightsPerTexture, 2, 2, 1, 1);


        gridLayout_2->addWidget(groupBox, 1, 0, 1, 1);

        groupBox_5 = new QGroupBox(dockWidgetContents_2);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setMaximumSize(QSize(16777215, 16777215));
        gridLayout_3 = new QGridLayout(groupBox_5);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setVerticalSpacing(3);
        gridLayout_3->setContentsMargins(5, 5, 5, 5);
        label_24 = new QLabel(groupBox_5);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setMaximumSize(QSize(50, 16777215));

        gridLayout_3->addWidget(label_24, 0, 0, 1, 1);

        comboBoxView = new QComboBox(groupBox_5);
        comboBoxView->addItem(QString());
        comboBoxView->addItem(QString());
        comboBoxView->addItem(QString());
        comboBoxView->addItem(QString());
        comboBoxView->addItem(QString());
        comboBoxView->addItem(QString());
        comboBoxView->setObjectName(QString::fromUtf8("comboBoxView"));

        gridLayout_3->addWidget(comboBoxView, 0, 1, 1, 1);

        line = new QFrame(groupBox_5);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line, 1, 0, 1, 2);

        checkBoxPixelated = new QCheckBox(groupBox_5);
        checkBoxPixelated->setObjectName(QString::fromUtf8("checkBoxPixelated"));

        gridLayout_3->addWidget(checkBoxPixelated, 2, 0, 1, 1);


        gridLayout_2->addWidget(groupBox_5, 0, 0, 1, 1);

        groupBox_Tile_Preview = new QGroupBox(dockWidgetContents_2);
        groupBox_Tile_Preview->setObjectName(QString::fromUtf8("groupBox_Tile_Preview"));
        groupBox_Tile_Preview->setMaximumSize(QSize(16777215, 16777215));
        gridLayout_12 = new QGridLayout(groupBox_Tile_Preview);
        gridLayout_12->setSpacing(6);
        gridLayout_12->setContentsMargins(11, 11, 11, 11);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        gridLayout_12->setVerticalSpacing(3);
        gridLayout_12->setContentsMargins(-1, 5, -1, 5);
        checkBoxMosaicoY = new QCheckBox(groupBox_Tile_Preview);
        checkBoxMosaicoY->setObjectName(QString::fromUtf8("checkBoxMosaicoY"));

        gridLayout_12->addWidget(checkBoxMosaicoY, 0, 1, 1, 1);

        checkBoxMosaicoX = new QCheckBox(groupBox_Tile_Preview);
        checkBoxMosaicoX->setObjectName(QString::fromUtf8("checkBoxMosaicoX"));

        gridLayout_12->addWidget(checkBoxMosaicoX, 0, 0, 1, 1);

        checkBoxParallax = new QCheckBox(groupBox_Tile_Preview);
        checkBoxParallax->setObjectName(QString::fromUtf8("checkBoxParallax"));

        gridLayout_12->addWidget(checkBoxParallax, 1, 0, 1, 1);

        sliderParallax = new QSlider(groupBox_Tile_Preview);
        sliderParallax->setObjectName(QString::fromUtf8("sliderParallax"));
        sliderParallax->setMaximum(300);
        sliderParallax->setValue(30);
        sliderParallax->setOrientation(Qt::Horizontal);

        gridLayout_12->addWidget(sliderParallax, 1, 1, 1, 1);


        gridLayout_2->addWidget(groupBox_Tile_Preview, 2, 0, 1, 1);

        dockWidget_2->setWidget(dockWidgetContents_2);
        MainWindow->addDockWidget(Qt::RightDockWidgetArea, dockWidget_2);
        dockWidgetTextures = new QDockWidget(MainWindow);
        dockWidgetTextures->setObjectName(QString::fromUtf8("dockWidgetTextures"));
        dockWidgetTextures->setFeatures(QDockWidget::DockWidgetMovable);
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QString::fromUtf8("dockWidgetContents_3"));
        gridLayout_10 = new QGridLayout(dockWidgetContents_3);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        gridLayout_10->setVerticalSpacing(3);
        listWidget = new QListWidget(dockWidgetContents_3);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        gridLayout_10->addWidget(listWidget, 0, 0, 1, 2);

        dockWidgetTextures->setWidget(dockWidgetContents_3);
        MainWindow->addDockWidget(Qt::RightDockWidgetArea, dockWidgetTextures);
        parallaxDockWidget = new QDockWidget(MainWindow);
        parallaxDockWidget->setObjectName(QString::fromUtf8("parallaxDockWidget"));
        dockWidgetContents_4 = new QWidget();
        dockWidgetContents_4->setObjectName(QString::fromUtf8("dockWidgetContents_4"));
        gridLayout_14 = new QGridLayout(dockWidgetContents_4);
        gridLayout_14->setSpacing(6);
        gridLayout_14->setContentsMargins(11, 11, 11, 11);
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        label_16 = new QLabel(dockWidgetContents_4);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_14->addWidget(label_16, 0, 0, 1, 1);

        comboBox = new QComboBox(dockWidgetContents_4);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout_14->addWidget(comboBox, 0, 1, 1, 1);

        groupBox_9 = new QGroupBox(dockWidgetContents_4);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        gridLayout_15 = new QGridLayout(groupBox_9);
        gridLayout_15->setSpacing(6);
        gridLayout_15->setContentsMargins(11, 11, 11, 11);
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        horizontalSpacer_2 = new QSpacerItem(120, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_15->addItem(horizontalSpacer_2, 8, 0, 1, 1);

        labelQuantization = new QLabel(groupBox_9);
        labelQuantization->setObjectName(QString::fromUtf8("labelQuantization"));

        gridLayout_15->addWidget(labelQuantization, 4, 0, 1, 1);

        labelThreshParallax = new QLabel(groupBox_9);
        labelThreshParallax->setObjectName(QString::fromUtf8("labelThreshParallax"));

        gridLayout_15->addWidget(labelThreshParallax, 0, 0, 1, 1);

        labelThreshMin = new QLabel(groupBox_9);
        labelThreshMin->setObjectName(QString::fromUtf8("labelThreshMin"));

        gridLayout_15->addWidget(labelThreshMin, 3, 0, 1, 1);

        labelThreshSoft = new QLabel(groupBox_9);
        labelThreshSoft->setObjectName(QString::fromUtf8("labelThreshSoft"));

        gridLayout_15->addWidget(labelThreshSoft, 2, 0, 1, 1);

        sliderParallaxBright = new QSlider(groupBox_9);
        sliderParallaxBright->setObjectName(QString::fromUtf8("sliderParallaxBright"));
        sliderParallaxBright->setMinimum(-255);
        sliderParallaxBright->setMaximum(255);
        sliderParallaxBright->setOrientation(Qt::Horizontal);

        gridLayout_15->addWidget(sliderParallaxBright, 5, 1, 1, 1);

        labelContrast = new QLabel(groupBox_9);
        labelContrast->setObjectName(QString::fromUtf8("labelContrast"));

        gridLayout_15->addWidget(labelContrast, 6, 0, 1, 1);

        parallaxFocusSlider = new QSlider(groupBox_9);
        parallaxFocusSlider->setObjectName(QString::fromUtf8("parallaxFocusSlider"));
        parallaxFocusSlider->setMaximum(50);
        parallaxFocusSlider->setSingleStep(1);
        parallaxFocusSlider->setValue(3);
        parallaxFocusSlider->setOrientation(Qt::Horizontal);

        gridLayout_15->addWidget(parallaxFocusSlider, 1, 1, 1, 1);

        checkBoxParallaxInvert = new QCheckBox(groupBox_9);
        checkBoxParallaxInvert->setObjectName(QString::fromUtf8("checkBoxParallaxInvert"));

        gridLayout_15->addWidget(checkBoxParallaxInvert, 8, 1, 1, 1);

        labelThreshFocus = new QLabel(groupBox_9);
        labelThreshFocus->setObjectName(QString::fromUtf8("labelThreshFocus"));

        gridLayout_15->addWidget(labelThreshFocus, 1, 0, 1, 1);

        labelBrightness = new QLabel(groupBox_9);
        labelBrightness->setObjectName(QString::fromUtf8("labelBrightness"));

        gridLayout_15->addWidget(labelBrightness, 5, 0, 1, 1);

        parallaxMinHeight = new QSlider(groupBox_9);
        parallaxMinHeight->setObjectName(QString::fromUtf8("parallaxMinHeight"));
        parallaxMinHeight->setMaximum(255);
        parallaxMinHeight->setOrientation(Qt::Horizontal);

        gridLayout_15->addWidget(parallaxMinHeight, 3, 1, 1, 1);

        parallaxSoftSlider = new QSlider(groupBox_9);
        parallaxSoftSlider->setObjectName(QString::fromUtf8("parallaxSoftSlider"));
        parallaxSoftSlider->setMaximum(50);
        parallaxSoftSlider->setValue(10);
        parallaxSoftSlider->setOrientation(Qt::Horizontal);

        gridLayout_15->addWidget(parallaxSoftSlider, 2, 1, 1, 1);

        parallaxThreshSlider = new QSlider(groupBox_9);
        parallaxThreshSlider->setObjectName(QString::fromUtf8("parallaxThreshSlider"));
        parallaxThreshSlider->setMaximum(255);
        parallaxThreshSlider->setPageStep(10);
        parallaxThreshSlider->setValue(140);
        parallaxThreshSlider->setOrientation(Qt::Horizontal);

        gridLayout_15->addWidget(parallaxThreshSlider, 0, 1, 1, 1);

        parallaxQuantizationSlider = new QSlider(groupBox_9);
        parallaxQuantizationSlider->setObjectName(QString::fromUtf8("parallaxQuantizationSlider"));
        parallaxQuantizationSlider->setMinimum(1);
        parallaxQuantizationSlider->setMaximum(255);
        parallaxQuantizationSlider->setOrientation(Qt::Horizontal);

        gridLayout_15->addWidget(parallaxQuantizationSlider, 4, 1, 1, 1);

        sliderParallaxContrast = new QSlider(groupBox_9);
        sliderParallaxContrast->setObjectName(QString::fromUtf8("sliderParallaxContrast"));
        sliderParallaxContrast->setMinimum(1);
        sliderParallaxContrast->setMaximum(4000);
        sliderParallaxContrast->setValue(1000);
        sliderParallaxContrast->setOrientation(Qt::Horizontal);

        gridLayout_15->addWidget(sliderParallaxContrast, 6, 1, 1, 1);

        labelErodeDilate = new QLabel(groupBox_9);
        labelErodeDilate->setObjectName(QString::fromUtf8("labelErodeDilate"));

        gridLayout_15->addWidget(labelErodeDilate, 7, 0, 1, 1);

        sliderParallaxErodeDilate = new QSlider(groupBox_9);
        sliderParallaxErodeDilate->setObjectName(QString::fromUtf8("sliderParallaxErodeDilate"));
        sliderParallaxErodeDilate->setMinimum(-99);
        sliderParallaxErodeDilate->setValue(0);
        sliderParallaxErodeDilate->setOrientation(Qt::Horizontal);

        gridLayout_15->addWidget(sliderParallaxErodeDilate, 7, 1, 1, 1);


        gridLayout_14->addWidget(groupBox_9, 1, 0, 1, 2);

        parallaxDockWidget->setWidget(dockWidgetContents_4);
        MainWindow->addDockWidget(Qt::LeftDockWidgetArea, parallaxDockWidget);
        specularDockWidget = new QDockWidget(MainWindow);
        specularDockWidget->setObjectName(QString::fromUtf8("specularDockWidget"));
        dockWidgetContents_5 = new QWidget();
        dockWidgetContents_5->setObjectName(QString::fromUtf8("dockWidgetContents_5"));
        gridLayout_18 = new QGridLayout(dockWidgetContents_5);
        gridLayout_18->setSpacing(6);
        gridLayout_18->setContentsMargins(11, 11, 11, 11);
        gridLayout_18->setObjectName(QString::fromUtf8("gridLayout_18"));
        groupBox_6 = new QGroupBox(dockWidgetContents_5);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        gridLayout_19 = new QGridLayout(groupBox_6);
        gridLayout_19->setSpacing(6);
        gridLayout_19->setContentsMargins(11, 11, 11, 11);
        gridLayout_19->setObjectName(QString::fromUtf8("gridLayout_19"));
        sliderSpecThresh = new QSlider(groupBox_6);
        sliderSpecThresh->setObjectName(QString::fromUtf8("sliderSpecThresh"));
        sliderSpecThresh->setMaximum(255);
        sliderSpecThresh->setValue(127);
        sliderSpecThresh->setOrientation(Qt::Horizontal);

        gridLayout_19->addWidget(sliderSpecThresh, 0, 1, 1, 1);

        label_15 = new QLabel(groupBox_6);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_19->addWidget(label_15, 0, 0, 1, 1);

        label_18 = new QLabel(groupBox_6);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout_19->addWidget(label_18, 2, 0, 1, 1);

        sliderSpecBright = new QSlider(groupBox_6);
        sliderSpecBright->setObjectName(QString::fromUtf8("sliderSpecBright"));
        sliderSpecBright->setMinimum(-255);
        sliderSpecBright->setMaximum(255);
        sliderSpecBright->setOrientation(Qt::Horizontal);

        gridLayout_19->addWidget(sliderSpecBright, 1, 1, 1, 1);

        sliderSpecSoft = new QSlider(groupBox_6);
        sliderSpecSoft->setObjectName(QString::fromUtf8("sliderSpecSoft"));
        sliderSpecSoft->setMaximum(50);
        sliderSpecSoft->setValue(10);
        sliderSpecSoft->setOrientation(Qt::Horizontal);

        gridLayout_19->addWidget(sliderSpecSoft, 3, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(60, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_19->addItem(horizontalSpacer, 4, 0, 1, 1);

        label_17 = new QLabel(groupBox_6);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_19->addWidget(label_17, 1, 0, 1, 1);

        checkBoxSpecInvert = new QCheckBox(groupBox_6);
        checkBoxSpecInvert->setObjectName(QString::fromUtf8("checkBoxSpecInvert"));

        gridLayout_19->addWidget(checkBoxSpecInvert, 4, 1, 1, 1);

        label_19 = new QLabel(groupBox_6);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout_19->addWidget(label_19, 3, 0, 1, 1);

        sliderSpecContrast = new QSlider(groupBox_6);
        sliderSpecContrast->setObjectName(QString::fromUtf8("sliderSpecContrast"));
        sliderSpecContrast->setMinimum(1);
        sliderSpecContrast->setMaximum(4000);
        sliderSpecContrast->setValue(1000);
        sliderSpecContrast->setOrientation(Qt::Horizontal);

        gridLayout_19->addWidget(sliderSpecContrast, 2, 1, 1, 1);


        gridLayout_18->addWidget(groupBox_6, 0, 0, 1, 1);

        specularDockWidget->setWidget(dockWidgetContents_5);
        MainWindow->addDockWidget(Qt::LeftDockWidgetArea, specularDockWidget);
        occlusionDockWidget = new QDockWidget(MainWindow);
        occlusionDockWidget->setObjectName(QString::fromUtf8("occlusionDockWidget"));
        dockWidgetContents_6 = new QWidget();
        dockWidgetContents_6->setObjectName(QString::fromUtf8("dockWidgetContents_6"));
        gridLayout_21 = new QGridLayout(dockWidgetContents_6);
        gridLayout_21->setSpacing(6);
        gridLayout_21->setContentsMargins(11, 11, 11, 11);
        gridLayout_21->setObjectName(QString::fromUtf8("gridLayout_21"));
        groupBox_10 = new QGroupBox(dockWidgetContents_6);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        gridLayout_20 = new QGridLayout(groupBox_10);
        gridLayout_20->setSpacing(6);
        gridLayout_20->setContentsMargins(11, 11, 11, 11);
        gridLayout_20->setObjectName(QString::fromUtf8("gridLayout_20"));
        checkBoxOcclusionInvert = new QCheckBox(groupBox_10);
        checkBoxOcclusionInvert->setObjectName(QString::fromUtf8("checkBoxOcclusionInvert"));

        gridLayout_20->addWidget(checkBoxOcclusionInvert, 5, 1, 1, 1);

        label_23 = new QLabel(groupBox_10);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        gridLayout_20->addWidget(label_23, 3, 0, 1, 1);

        sliderOcclusionBright = new QSlider(groupBox_10);
        sliderOcclusionBright->setObjectName(QString::fromUtf8("sliderOcclusionBright"));
        sliderOcclusionBright->setMinimum(-255);
        sliderOcclusionBright->setMaximum(255);
        sliderOcclusionBright->setValue(10);
        sliderOcclusionBright->setOrientation(Qt::Horizontal);

        gridLayout_20->addWidget(sliderOcclusionBright, 1, 1, 1, 1);

        sliderOcclusionSoft = new QSlider(groupBox_10);
        sliderOcclusionSoft->setObjectName(QString::fromUtf8("sliderOcclusionSoft"));
        sliderOcclusionSoft->setMaximum(50);
        sliderOcclusionSoft->setValue(10);
        sliderOcclusionSoft->setOrientation(Qt::Horizontal);

        gridLayout_20->addWidget(sliderOcclusionSoft, 3, 1, 1, 1);

        sliderOcclusionThresh = new QSlider(groupBox_10);
        sliderOcclusionThresh->setObjectName(QString::fromUtf8("sliderOcclusionThresh"));
        sliderOcclusionThresh->setMaximum(255);
        sliderOcclusionThresh->setValue(1);
        sliderOcclusionThresh->setOrientation(Qt::Horizontal);

        gridLayout_20->addWidget(sliderOcclusionThresh, 0, 1, 1, 1);

        label_21 = new QLabel(groupBox_10);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        gridLayout_20->addWidget(label_21, 2, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(60, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_20->addItem(horizontalSpacer_3, 5, 0, 1, 1);

        sliderOcclusionContrast = new QSlider(groupBox_10);
        sliderOcclusionContrast->setObjectName(QString::fromUtf8("sliderOcclusionContrast"));
        sliderOcclusionContrast->setMinimum(1);
        sliderOcclusionContrast->setMaximum(4000);
        sliderOcclusionContrast->setValue(1000);
        sliderOcclusionContrast->setOrientation(Qt::Horizontal);

        gridLayout_20->addWidget(sliderOcclusionContrast, 2, 1, 1, 1);

        label_22 = new QLabel(groupBox_10);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        gridLayout_20->addWidget(label_22, 1, 0, 1, 1);

        label_20 = new QLabel(groupBox_10);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        gridLayout_20->addWidget(label_20, 0, 0, 1, 1);

        checkBoxOcclusionDistance = new QCheckBox(groupBox_10);
        checkBoxOcclusionDistance->setObjectName(QString::fromUtf8("checkBoxOcclusionDistance"));
        checkBoxOcclusionDistance->setChecked(true);

        gridLayout_20->addWidget(checkBoxOcclusionDistance, 4, 0, 1, 1);

        sliderOcclusionDistance = new QSlider(groupBox_10);
        sliderOcclusionDistance->setObjectName(QString::fromUtf8("sliderOcclusionDistance"));
        sliderOcclusionDistance->setMaximum(1024);
        sliderOcclusionDistance->setValue(10);
        sliderOcclusionDistance->setOrientation(Qt::Horizontal);

        gridLayout_20->addWidget(sliderOcclusionDistance, 4, 1, 1, 1);


        gridLayout_21->addWidget(groupBox_10, 0, 0, 1, 1);

        occlusionDockWidget->setWidget(dockWidgetContents_6);
        MainWindow->addDockWidget(Qt::LeftDockWidgetArea, occlusionDockWidget);
        TileDockWidget = new QDockWidget(MainWindow);
        TileDockWidget->setObjectName(QString::fromUtf8("TileDockWidget"));
        dockWidgetContents_7 = new QWidget();
        dockWidgetContents_7->setObjectName(QString::fromUtf8("dockWidgetContents_7"));
        gridLayout_22 = new QGridLayout(dockWidgetContents_7);
        gridLayout_22->setSpacing(6);
        gridLayout_22->setContentsMargins(11, 11, 11, 11);
        gridLayout_22->setObjectName(QString::fromUtf8("gridLayout_22"));
        groupBox_8 = new QGroupBox(dockWidgetContents_7);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        groupBox_8->setMaximumSize(QSize(16777215, 16777215));
        gridLayout_13 = new QGridLayout(groupBox_8);
        gridLayout_13->setSpacing(6);
        gridLayout_13->setContentsMargins(11, 11, 11, 11);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        pushButton_2 = new QPushButton(groupBox_8);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(0, 23));
        pushButton_2->setMaximumSize(QSize(16777215, 23));

        gridLayout_13->addWidget(pushButton_2, 0, 0, 1, 1);

        checkBoxTileable = new QCheckBox(groupBox_8);
        checkBoxTileable->setObjectName(QString::fromUtf8("checkBoxTileable"));
        checkBoxTileable->setLayoutDirection(Qt::LeftToRight);

        gridLayout_13->addWidget(checkBoxTileable, 0, 1, 1, 1);


        gridLayout_22->addWidget(groupBox_8, 0, 0, 1, 1);

        TileDockWidget->setWidget(dockWidgetContents_7);
        MainWindow->addDockWidget(Qt::LeftDockWidgetArea, TileDockWidget);
        dockWidgetExport = new QDockWidget(MainWindow);
        dockWidgetExport->setObjectName(QString::fromUtf8("dockWidgetExport"));
        dockWidgetContents_9 = new QWidget();
        dockWidgetContents_9->setObjectName(QString::fromUtf8("dockWidgetContents_9"));
        gridLayout_23 = new QGridLayout(dockWidgetContents_9);
        gridLayout_23->setSpacing(6);
        gridLayout_23->setContentsMargins(11, 11, 11, 11);
        gridLayout_23->setObjectName(QString::fromUtf8("gridLayout_23"));
        scrollArea = new QScrollArea(dockWidgetContents_9);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 254, 309));
        gridLayout_11 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        checkBoxExportNormal = new QCheckBox(scrollAreaWidgetContents);
        checkBoxExportNormal->setObjectName(QString::fromUtf8("checkBoxExportNormal"));
        checkBoxExportNormal->setChecked(true);

        gridLayout_11->addWidget(checkBoxExportNormal, 0, 0, 1, 1);

        checkBoxExportSpecular = new QCheckBox(scrollAreaWidgetContents);
        checkBoxExportSpecular->setObjectName(QString::fromUtf8("checkBoxExportSpecular"));
        checkBoxExportSpecular->setChecked(true);

        gridLayout_11->addWidget(checkBoxExportSpecular, 1, 0, 1, 1);

        checkBoxExportOcclusion = new QCheckBox(scrollAreaWidgetContents);
        checkBoxExportOcclusion->setObjectName(QString::fromUtf8("checkBoxExportOcclusion"));
        checkBoxExportOcclusion->setChecked(true);

        gridLayout_11->addWidget(checkBoxExportOcclusion, 2, 0, 1, 1);

        checkBoxExportParallax = new QCheckBox(scrollAreaWidgetContents);
        checkBoxExportParallax->setObjectName(QString::fromUtf8("checkBoxExportParallax"));
        checkBoxExportParallax->setChecked(true);

        gridLayout_11->addWidget(checkBoxExportParallax, 3, 0, 1, 1);

        checkBoxExportPreview = new QCheckBox(scrollAreaWidgetContents);
        checkBoxExportPreview->setObjectName(QString::fromUtf8("checkBoxExportPreview"));
        checkBoxExportPreview->setChecked(false);

        gridLayout_11->addWidget(checkBoxExportPreview, 4, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_23->addWidget(scrollArea, 0, 0, 1, 2);

        pushButtonExportTo = new QPushButton(dockWidgetContents_9);
        pushButtonExportTo->setObjectName(QString::fromUtf8("pushButtonExportTo"));

        gridLayout_23->addWidget(pushButtonExportTo, 1, 0, 1, 1);

        pushButton = new QPushButton(dockWidgetContents_9);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(0, 23));
        pushButton->setMaximumSize(QSize(16777215, 23));

        gridLayout_23->addWidget(pushButton, 1, 1, 1, 1);

        dockWidgetExport->setWidget(dockWidgetContents_9);
        MainWindow->addDockWidget(Qt::RightDockWidgetArea, dockWidgetExport);

        mainToolBar->addAction(actionOpen);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionFitZoom);
        mainToolBar->addAction(actionZoom_100);
        mainToolBar->addAction(actionZoomIn);
        mainToolBar->addAction(actionZoomOut);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionExport);
        mainToolBar->addAction(actionExportPreview);
        mainToolBar->addAction(actionAdd_Light);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionPresets);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionAbout);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Laigter", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
#if QT_CONFIG(tooltip)
        actionOpen->setToolTip(QCoreApplication::translate("MainWindow", "Open", nullptr));
#endif // QT_CONFIG(tooltip)
        actionFitZoom->setText(QCoreApplication::translate("MainWindow", "Fit Zoom", nullptr));
#if QT_CONFIG(tooltip)
        actionFitZoom->setToolTip(QCoreApplication::translate("MainWindow", "Fit Zoom", nullptr));
#endif // QT_CONFIG(tooltip)
        actionZoom_100->setText(QCoreApplication::translate("MainWindow", "Zoom 100%", nullptr));
        actionZoomIn->setText(QCoreApplication::translate("MainWindow", "Zoom +", nullptr));
        actionZoomOut->setText(QCoreApplication::translate("MainWindow", "Zoom -", nullptr));
        actionExport->setText(QCoreApplication::translate("MainWindow", "Export", nullptr));
#if QT_CONFIG(tooltip)
        actionExport->setToolTip(QCoreApplication::translate("MainWindow", "Export", nullptr));
#endif // QT_CONFIG(tooltip)
        actionPresets->setText(QCoreApplication::translate("MainWindow", "Presets", nullptr));
        actionExportPreview->setText(QCoreApplication::translate("MainWindow", "Export Preview", nullptr));
#if QT_CONFIG(tooltip)
        actionExportPreview->setToolTip(QCoreApplication::translate("MainWindow", "Export Preview", nullptr));
#endif // QT_CONFIG(tooltip)
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
#if QT_CONFIG(tooltip)
        actionAbout->setToolTip(QCoreApplication::translate("MainWindow", "About", nullptr));
#endif // QT_CONFIG(tooltip)
        actionAdd_Light->setText(QCoreApplication::translate("MainWindow", "Add Light", nullptr));
#if QT_CONFIG(tooltip)
        actionAdd_Light->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600; text-decoration: underline;\">Add Light Source:</span></p><p>Left click to add light source.</p><p>Right click to remove light source or cancel.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        normalDockWidget->setWindowTitle(QCoreApplication::translate("MainWindow", "Normal", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Enhance:", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Height:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Soft:", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "Axis:", nullptr));
        normalInvertX->setText(QCoreApplication::translate("MainWindow", "Invert x", nullptr));
        normalInvertY->setText(QCoreApplication::translate("MainWindow", "Invert y", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Bump:", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Height:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Distance:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Soft:", nullptr));
        biselSoftRadio->setText(QCoreApplication::translate("MainWindow", "Soft", nullptr));
        biselAbruptRadio->setText(QCoreApplication::translate("MainWindow", "Abrupt", nullptr));
        dockWidget_2->setWindowTitle(QCoreApplication::translate("MainWindow", "Visualization", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Light", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Intensity:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabDif), QCoreApplication::translate("MainWindow", "Diffuse", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Intensity:", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Scatter:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabSpec), QCoreApplication::translate("MainWindow", "Specular", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Intensity:", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Color:", nullptr));
        pushButtonAmbientColor->setText(QString());
        label_10->setText(QCoreApplication::translate("MainWindow", "Background:", nullptr));
        pushButtonBackgroundColor->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tabAmb), QCoreApplication::translate("MainWindow", "Ambient", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Height:", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Color:", nullptr));
        pushButtonColor->setText(QString());
#if QT_CONFIG(tooltip)
        checkBoxLightsPerTexture->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>If enabled, each texture will have its own lights, with its own respective settings.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxLightsPerTexture->setText(QCoreApplication::translate("MainWindow", "Lights per texture", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "View", nullptr));
        label_24->setText(QCoreApplication::translate("MainWindow", "Mode:", nullptr));
        comboBoxView->setItemText(0, QCoreApplication::translate("MainWindow", "Texture", nullptr));
        comboBoxView->setItemText(1, QCoreApplication::translate("MainWindow", "Normal Map", nullptr));
        comboBoxView->setItemText(2, QCoreApplication::translate("MainWindow", "Specular Map", nullptr));
        comboBoxView->setItemText(3, QCoreApplication::translate("MainWindow", "Parallax Map", nullptr));
        comboBoxView->setItemText(4, QCoreApplication::translate("MainWindow", "Occlussion Map", nullptr));
        comboBoxView->setItemText(5, QCoreApplication::translate("MainWindow", "Preview", nullptr));

        checkBoxPixelated->setText(QCoreApplication::translate("MainWindow", "Pixelated", nullptr));
        groupBox_Tile_Preview->setTitle(QCoreApplication::translate("MainWindow", "Tile", nullptr));
        checkBoxMosaicoY->setText(QCoreApplication::translate("MainWindow", "Tile y", nullptr));
        checkBoxMosaicoX->setText(QCoreApplication::translate("MainWindow", "Tile x", nullptr));
        checkBoxParallax->setText(QCoreApplication::translate("MainWindow", "Parallax", nullptr));
        dockWidgetTextures->setWindowTitle(QCoreApplication::translate("MainWindow", "Textures", nullptr));
        parallaxDockWidget->setWindowTitle(QCoreApplication::translate("MainWindow", "Parallax", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Binary", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Height Map", nullptr));

        groupBox_9->setTitle(QCoreApplication::translate("MainWindow", "Controls:", nullptr));
        labelQuantization->setText(QCoreApplication::translate("MainWindow", "Quantization:", nullptr));
        labelThreshParallax->setText(QCoreApplication::translate("MainWindow", "Threshold:", nullptr));
        labelThreshMin->setText(QCoreApplication::translate("MainWindow", "Minimum Height:", nullptr));
        labelThreshSoft->setText(QCoreApplication::translate("MainWindow", "Soft:", nullptr));
        labelContrast->setText(QCoreApplication::translate("MainWindow", "Contrast:", nullptr));
        checkBoxParallaxInvert->setText(QCoreApplication::translate("MainWindow", "Invert", nullptr));
        labelThreshFocus->setText(QCoreApplication::translate("MainWindow", "Focus:", nullptr));
        labelBrightness->setText(QCoreApplication::translate("MainWindow", "Brightness:", nullptr));
        labelErodeDilate->setText(QCoreApplication::translate("MainWindow", "Erode / Dilate:", nullptr));
        specularDockWidget->setWindowTitle(QCoreApplication::translate("MainWindow", "Specular", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("MainWindow", "Controls:", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Threshold:", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "Contrast:", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "Brightness:", nullptr));
        checkBoxSpecInvert->setText(QCoreApplication::translate("MainWindow", "Invert", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "Soft:", nullptr));
        occlusionDockWidget->setWindowTitle(QCoreApplication::translate("MainWindow", "Occlussion", nullptr));
        groupBox_10->setTitle(QCoreApplication::translate("MainWindow", "Controls:", nullptr));
        checkBoxOcclusionInvert->setText(QCoreApplication::translate("MainWindow", "Invert", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "Soft:", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "Contrast:", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "Brightness:", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "Threshold:", nullptr));
        checkBoxOcclusionDistance->setText(QCoreApplication::translate("MainWindow", "Distance:", nullptr));
        TileDockWidget->setWindowTitle(QCoreApplication::translate("MainWindow", "Tile", nullptr));
        groupBox_8->setTitle(QCoreApplication::translate("MainWindow", "Controls:", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Neighbours", nullptr));
        checkBoxTileable->setText(QCoreApplication::translate("MainWindow", "Tile", nullptr));
        dockWidgetExport->setWindowTitle(QCoreApplication::translate("MainWindow", "Export", nullptr));
        checkBoxExportNormal->setText(QCoreApplication::translate("MainWindow", "Normal", nullptr));
        checkBoxExportSpecular->setText(QCoreApplication::translate("MainWindow", "Specular", nullptr));
        checkBoxExportOcclusion->setText(QCoreApplication::translate("MainWindow", "Occlussion", nullptr));
        checkBoxExportParallax->setText(QCoreApplication::translate("MainWindow", "Parallax", nullptr));
        checkBoxExportPreview->setText(QCoreApplication::translate("MainWindow", "Preview", nullptr));
        pushButtonExportTo->setText(QCoreApplication::translate("MainWindow", "Export to...", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Export", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
