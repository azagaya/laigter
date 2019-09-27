/********************************************************************************
** Form generated from reading UI file 'presetsmanager.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRESETSMANAGER_H
#define UI_PRESETSMANAGER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeWidget>

QT_BEGIN_NAMESPACE

class Ui_PresetsManager
{
public:
    QGridLayout *gridLayout_3;
    QLabel *labelMessage;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonExportPreset;
    QPushButton *pushButtonImportPreset;
    QPushButton *pushButtonDeletePreset;
    QComboBox *comboBoxPreset;
    QListWidget *listWidgetTextures;
    QPushButton *pushButtonAplyPreset;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QLineEdit *lineEditPresetName;
    QTreeWidget *treeWidget;
    QPushButton *pushButtonSavePreset;

    void setupUi(QDialog *PresetsManager)
    {
        if (PresetsManager->objectName().isEmpty())
            PresetsManager->setObjectName(QString::fromUtf8("PresetsManager"));
        PresetsManager->resize(644, 448);
        gridLayout_3 = new QGridLayout(PresetsManager);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        labelMessage = new QLabel(PresetsManager);
        labelMessage->setObjectName(QString::fromUtf8("labelMessage"));

        gridLayout_3->addWidget(labelMessage, 1, 0, 1, 3);

        groupBox_2 = new QGroupBox(PresetsManager);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(87, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        pushButtonExportPreset = new QPushButton(groupBox_2);
        pushButtonExportPreset->setObjectName(QString::fromUtf8("pushButtonExportPreset"));
        pushButtonExportPreset->setMaximumSize(QSize(24, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/export.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonExportPreset->setIcon(icon);

        gridLayout->addWidget(pushButtonExportPreset, 0, 2, 1, 1);

        pushButtonImportPreset = new QPushButton(groupBox_2);
        pushButtonImportPreset->setObjectName(QString::fromUtf8("pushButtonImportPreset"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButtonImportPreset->sizePolicy().hasHeightForWidth());
        pushButtonImportPreset->setSizePolicy(sizePolicy2);
        pushButtonImportPreset->setMaximumSize(QSize(24, 16777215));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/import.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonImportPreset->setIcon(icon1);

        gridLayout->addWidget(pushButtonImportPreset, 0, 3, 1, 1);

        pushButtonDeletePreset = new QPushButton(groupBox_2);
        pushButtonDeletePreset->setObjectName(QString::fromUtf8("pushButtonDeletePreset"));
        pushButtonDeletePreset->setMaximumSize(QSize(24, 16777215));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonDeletePreset->setIcon(icon2);

        gridLayout->addWidget(pushButtonDeletePreset, 0, 4, 1, 1);

        comboBoxPreset = new QComboBox(groupBox_2);
        comboBoxPreset->setObjectName(QString::fromUtf8("comboBoxPreset"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(comboBoxPreset->sizePolicy().hasHeightForWidth());
        comboBoxPreset->setSizePolicy(sizePolicy3);
        comboBoxPreset->setMinimumSize(QSize(100, 0));

        gridLayout->addWidget(comboBoxPreset, 0, 5, 1, 1);

        listWidgetTextures = new QListWidget(groupBox_2);
        listWidgetTextures->setObjectName(QString::fromUtf8("listWidgetTextures"));

        gridLayout->addWidget(listWidgetTextures, 1, 0, 1, 6);

        pushButtonAplyPreset = new QPushButton(groupBox_2);
        pushButtonAplyPreset->setObjectName(QString::fromUtf8("pushButtonAplyPreset"));
        pushButtonAplyPreset->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(pushButtonAplyPreset, 2, 0, 1, 2);


        gridLayout_3->addWidget(groupBox_2, 0, 2, 1, 1);

        groupBox = new QGroupBox(PresetsManager);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy4);
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy5(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy5);

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        lineEditPresetName = new QLineEdit(groupBox);
        lineEditPresetName->setObjectName(QString::fromUtf8("lineEditPresetName"));

        gridLayout_2->addWidget(lineEditPresetName, 0, 1, 1, 2);

        treeWidget = new QTreeWidget(groupBox);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsTristate);
        __qtreewidgetitem->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(__qtreewidgetitem);
        __qtreewidgetitem1->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsTristate);
        __qtreewidgetitem1->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(__qtreewidgetitem1);
        __qtreewidgetitem2->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem3 = new QTreeWidgetItem(__qtreewidgetitem1);
        __qtreewidgetitem3->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem4 = new QTreeWidgetItem(__qtreewidgetitem);
        __qtreewidgetitem4->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsTristate);
        __qtreewidgetitem4->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem5 = new QTreeWidgetItem(__qtreewidgetitem4);
        __qtreewidgetitem5->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem6 = new QTreeWidgetItem(__qtreewidgetitem4);
        __qtreewidgetitem6->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem7 = new QTreeWidgetItem(__qtreewidgetitem4);
        __qtreewidgetitem7->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem8 = new QTreeWidgetItem(__qtreewidgetitem4);
        __qtreewidgetitem8->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem9 = new QTreeWidgetItem(__qtreewidgetitem);
        __qtreewidgetitem9->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsTristate);
        __qtreewidgetitem9->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem10 = new QTreeWidgetItem(__qtreewidgetitem9);
        __qtreewidgetitem10->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem11 = new QTreeWidgetItem(__qtreewidgetitem9);
        __qtreewidgetitem11->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem12 = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem12->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsTristate);
        __qtreewidgetitem12->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem13 = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem13->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsTristate);
        __qtreewidgetitem13->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem14 = new QTreeWidgetItem(__qtreewidgetitem13);
        __qtreewidgetitem14->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem15 = new QTreeWidgetItem(__qtreewidgetitem13);
        __qtreewidgetitem15->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsTristate);
        __qtreewidgetitem15->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem16 = new QTreeWidgetItem(__qtreewidgetitem15);
        __qtreewidgetitem16->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem17 = new QTreeWidgetItem(__qtreewidgetitem15);
        __qtreewidgetitem17->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem18 = new QTreeWidgetItem(__qtreewidgetitem15);
        __qtreewidgetitem18->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem19 = new QTreeWidgetItem(__qtreewidgetitem15);
        __qtreewidgetitem19->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem20 = new QTreeWidgetItem(__qtreewidgetitem13);
        __qtreewidgetitem20->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem21 = new QTreeWidgetItem(__qtreewidgetitem13);
        __qtreewidgetitem21->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsTristate);
        __qtreewidgetitem21->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem22 = new QTreeWidgetItem(__qtreewidgetitem21);
        __qtreewidgetitem22->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem23 = new QTreeWidgetItem(__qtreewidgetitem21);
        __qtreewidgetitem23->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem24 = new QTreeWidgetItem(__qtreewidgetitem13);
        __qtreewidgetitem24->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem25 = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem25->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsTristate);
        __qtreewidgetitem25->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem26 = new QTreeWidgetItem(__qtreewidgetitem25);
        __qtreewidgetitem26->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsTristate);
        __qtreewidgetitem26->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem27 = new QTreeWidgetItem(__qtreewidgetitem25);
        __qtreewidgetitem27->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsTristate);
        __qtreewidgetitem27->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem28 = new QTreeWidgetItem(__qtreewidgetitem25);
        __qtreewidgetitem28->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsTristate);
        __qtreewidgetitem28->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem29 = new QTreeWidgetItem(__qtreewidgetitem25);
        __qtreewidgetitem29->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsTristate);
        __qtreewidgetitem29->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem30 = new QTreeWidgetItem(__qtreewidgetitem25);
        __qtreewidgetitem30->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsTristate);
        __qtreewidgetitem30->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem31 = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem31->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsTristate);
        __qtreewidgetitem31->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem32 = new QTreeWidgetItem(__qtreewidgetitem31);
        __qtreewidgetitem32->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem33 = new QTreeWidgetItem(__qtreewidgetitem31);
        __qtreewidgetitem33->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem34 = new QTreeWidgetItem(__qtreewidgetitem31);
        __qtreewidgetitem34->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem35 = new QTreeWidgetItem(__qtreewidgetitem31);
        __qtreewidgetitem35->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem36 = new QTreeWidgetItem(__qtreewidgetitem31);
        __qtreewidgetitem36->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem37 = new QTreeWidgetItem(__qtreewidgetitem31);
        __qtreewidgetitem37->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem38 = new QTreeWidgetItem(__qtreewidgetitem31);
        __qtreewidgetitem38->setCheckState(0, Qt::Checked);
        QTreeWidgetItem *__qtreewidgetitem39 = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem39->setCheckState(0, Qt::Unchecked);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));

        gridLayout_2->addWidget(treeWidget, 1, 0, 1, 3);

        pushButtonSavePreset = new QPushButton(groupBox);
        pushButtonSavePreset->setObjectName(QString::fromUtf8("pushButtonSavePreset"));
        pushButtonSavePreset->setMaximumSize(QSize(80, 16777215));

        gridLayout_2->addWidget(pushButtonSavePreset, 2, 0, 1, 2);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(PresetsManager);

        QMetaObject::connectSlotsByName(PresetsManager);
    } // setupUi

    void retranslateUi(QDialog *PresetsManager)
    {
        PresetsManager->setWindowTitle(QCoreApplication::translate("PresetsManager", "Presets Manager", nullptr));
        labelMessage->setText(QString());
        groupBox_2->setTitle(QCoreApplication::translate("PresetsManager", "Apply preset:", nullptr));
        label->setText(QCoreApplication::translate("PresetsManager", "Preset:", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonExportPreset->setToolTip(QCoreApplication::translate("PresetsManager", "Export", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonExportPreset->setText(QString());
#if QT_CONFIG(tooltip)
        pushButtonImportPreset->setToolTip(QCoreApplication::translate("PresetsManager", "Import", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonImportPreset->setText(QString());
#if QT_CONFIG(tooltip)
        pushButtonDeletePreset->setToolTip(QCoreApplication::translate("PresetsManager", "Delete", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonDeletePreset->setText(QString());
        pushButtonAplyPreset->setText(QCoreApplication::translate("PresetsManager", "Apply", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PresetsManager", "Save current preset:", nullptr));
        label_2->setText(QCoreApplication::translate("PresetsManager", "Name:", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("PresetsManager", "Code", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("PresetsManager", "Controls", nullptr));

        const bool __sortingEnabled = treeWidget->isSortingEnabled();
        treeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QCoreApplication::translate("PresetsManager", "Normal", nullptr));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem1->child(0);
        ___qtreewidgetitem2->setText(0, QCoreApplication::translate("PresetsManager", "Enhance", nullptr));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem2->child(0);
        ___qtreewidgetitem3->setText(1, QCoreApplication::translate("PresetsManager", "0", nullptr));
        ___qtreewidgetitem3->setText(0, QCoreApplication::translate("PresetsManager", "Height", nullptr));
        QTreeWidgetItem *___qtreewidgetitem4 = ___qtreewidgetitem2->child(1);
        ___qtreewidgetitem4->setText(1, QCoreApplication::translate("PresetsManager", "1", nullptr));
        ___qtreewidgetitem4->setText(0, QCoreApplication::translate("PresetsManager", "Soft", nullptr));
        QTreeWidgetItem *___qtreewidgetitem5 = ___qtreewidgetitem1->child(1);
        ___qtreewidgetitem5->setText(0, QCoreApplication::translate("PresetsManager", "Bump", nullptr));
        QTreeWidgetItem *___qtreewidgetitem6 = ___qtreewidgetitem5->child(0);
        ___qtreewidgetitem6->setText(1, QCoreApplication::translate("PresetsManager", "2", nullptr));
        ___qtreewidgetitem6->setText(0, QCoreApplication::translate("PresetsManager", "Height", nullptr));
        QTreeWidgetItem *___qtreewidgetitem7 = ___qtreewidgetitem5->child(1);
        ___qtreewidgetitem7->setText(1, QCoreApplication::translate("PresetsManager", "3", nullptr));
        ___qtreewidgetitem7->setText(0, QCoreApplication::translate("PresetsManager", "Distance", nullptr));
        QTreeWidgetItem *___qtreewidgetitem8 = ___qtreewidgetitem5->child(2);
        ___qtreewidgetitem8->setText(1, QCoreApplication::translate("PresetsManager", "4", nullptr));
        ___qtreewidgetitem8->setText(0, QCoreApplication::translate("PresetsManager", "Soft", nullptr));
        QTreeWidgetItem *___qtreewidgetitem9 = ___qtreewidgetitem5->child(3);
        ___qtreewidgetitem9->setText(1, QCoreApplication::translate("PresetsManager", "5", nullptr));
        ___qtreewidgetitem9->setText(0, QCoreApplication::translate("PresetsManager", "Cut", nullptr));
        QTreeWidgetItem *___qtreewidgetitem10 = ___qtreewidgetitem1->child(2);
        ___qtreewidgetitem10->setText(0, QCoreApplication::translate("PresetsManager", "Invert", nullptr));
        QTreeWidgetItem *___qtreewidgetitem11 = ___qtreewidgetitem10->child(0);
        ___qtreewidgetitem11->setText(1, QCoreApplication::translate("PresetsManager", "7", nullptr));
        ___qtreewidgetitem11->setText(0, QCoreApplication::translate("PresetsManager", "X Axis", nullptr));
        QTreeWidgetItem *___qtreewidgetitem12 = ___qtreewidgetitem10->child(1);
        ___qtreewidgetitem12->setText(1, QCoreApplication::translate("PresetsManager", "8", nullptr));
        ___qtreewidgetitem12->setText(0, QCoreApplication::translate("PresetsManager", "Y Axis", nullptr));
        QTreeWidgetItem *___qtreewidgetitem13 = treeWidget->topLevelItem(1);
        ___qtreewidgetitem13->setText(1, QCoreApplication::translate("PresetsManager", "6", nullptr));
        ___qtreewidgetitem13->setText(0, QCoreApplication::translate("PresetsManager", "Tile", nullptr));
        QTreeWidgetItem *___qtreewidgetitem14 = treeWidget->topLevelItem(2);
        ___qtreewidgetitem14->setText(0, QCoreApplication::translate("PresetsManager", "Parallax", nullptr));
        QTreeWidgetItem *___qtreewidgetitem15 = ___qtreewidgetitem14->child(0);
        ___qtreewidgetitem15->setText(1, QCoreApplication::translate("PresetsManager", "9", nullptr));
        ___qtreewidgetitem15->setText(0, QCoreApplication::translate("PresetsManager", "Type", nullptr));
        QTreeWidgetItem *___qtreewidgetitem16 = ___qtreewidgetitem14->child(1);
        ___qtreewidgetitem16->setText(0, QCoreApplication::translate("PresetsManager", "Binary", nullptr));
        QTreeWidgetItem *___qtreewidgetitem17 = ___qtreewidgetitem16->child(0);
        ___qtreewidgetitem17->setText(1, QCoreApplication::translate("PresetsManager", "10", nullptr));
        ___qtreewidgetitem17->setText(0, QCoreApplication::translate("PresetsManager", "Threshold", nullptr));
        QTreeWidgetItem *___qtreewidgetitem18 = ___qtreewidgetitem16->child(1);
        ___qtreewidgetitem18->setText(1, QCoreApplication::translate("PresetsManager", "11", nullptr));
        ___qtreewidgetitem18->setText(0, QCoreApplication::translate("PresetsManager", "Focus", nullptr));
        QTreeWidgetItem *___qtreewidgetitem19 = ___qtreewidgetitem16->child(2);
        ___qtreewidgetitem19->setText(1, QCoreApplication::translate("PresetsManager", "13", nullptr));
        ___qtreewidgetitem19->setText(0, QCoreApplication::translate("PresetsManager", "Minimum Height", nullptr));
        QTreeWidgetItem *___qtreewidgetitem20 = ___qtreewidgetitem16->child(3);
        ___qtreewidgetitem20->setText(1, QCoreApplication::translate("PresetsManager", "14", nullptr));
        ___qtreewidgetitem20->setText(0, QCoreApplication::translate("PresetsManager", "Erode / Dilate", nullptr));
        QTreeWidgetItem *___qtreewidgetitem21 = ___qtreewidgetitem14->child(2);
        ___qtreewidgetitem21->setText(1, QCoreApplication::translate("PresetsManager", "12", nullptr));
        ___qtreewidgetitem21->setText(0, QCoreApplication::translate("PresetsManager", "Soft", nullptr));
        QTreeWidgetItem *___qtreewidgetitem22 = ___qtreewidgetitem14->child(3);
        ___qtreewidgetitem22->setText(0, QCoreApplication::translate("PresetsManager", "Height Map", nullptr));
        QTreeWidgetItem *___qtreewidgetitem23 = ___qtreewidgetitem22->child(0);
        ___qtreewidgetitem23->setText(1, QCoreApplication::translate("PresetsManager", "15", nullptr));
        ___qtreewidgetitem23->setText(0, QCoreApplication::translate("PresetsManager", "Brightness", nullptr));
        QTreeWidgetItem *___qtreewidgetitem24 = ___qtreewidgetitem22->child(1);
        ___qtreewidgetitem24->setText(1, QCoreApplication::translate("PresetsManager", "16", nullptr));
        ___qtreewidgetitem24->setText(0, QCoreApplication::translate("PresetsManager", "Contrast", nullptr));
        QTreeWidgetItem *___qtreewidgetitem25 = ___qtreewidgetitem14->child(4);
        ___qtreewidgetitem25->setText(1, QCoreApplication::translate("PresetsManager", "17", nullptr));
        ___qtreewidgetitem25->setText(0, QCoreApplication::translate("PresetsManager", "Invert", nullptr));
        QTreeWidgetItem *___qtreewidgetitem26 = treeWidget->topLevelItem(3);
        ___qtreewidgetitem26->setText(0, QCoreApplication::translate("PresetsManager", "Specular", nullptr));
        QTreeWidgetItem *___qtreewidgetitem27 = ___qtreewidgetitem26->child(0);
        ___qtreewidgetitem27->setText(1, QCoreApplication::translate("PresetsManager", "18", nullptr));
        ___qtreewidgetitem27->setText(0, QCoreApplication::translate("PresetsManager", "Soft", nullptr));
        QTreeWidgetItem *___qtreewidgetitem28 = ___qtreewidgetitem26->child(1);
        ___qtreewidgetitem28->setText(1, QCoreApplication::translate("PresetsManager", "19", nullptr));
        ___qtreewidgetitem28->setText(0, QCoreApplication::translate("PresetsManager", "Brightness", nullptr));
        QTreeWidgetItem *___qtreewidgetitem29 = ___qtreewidgetitem26->child(2);
        ___qtreewidgetitem29->setText(1, QCoreApplication::translate("PresetsManager", "20", nullptr));
        ___qtreewidgetitem29->setText(0, QCoreApplication::translate("PresetsManager", "Contrast", nullptr));
        QTreeWidgetItem *___qtreewidgetitem30 = ___qtreewidgetitem26->child(3);
        ___qtreewidgetitem30->setText(1, QCoreApplication::translate("PresetsManager", "21", nullptr));
        ___qtreewidgetitem30->setText(0, QCoreApplication::translate("PresetsManager", "Threshold", nullptr));
        QTreeWidgetItem *___qtreewidgetitem31 = ___qtreewidgetitem26->child(4);
        ___qtreewidgetitem31->setText(1, QCoreApplication::translate("PresetsManager", "22", nullptr));
        ___qtreewidgetitem31->setText(0, QCoreApplication::translate("PresetsManager", "Invert", nullptr));
        QTreeWidgetItem *___qtreewidgetitem32 = treeWidget->topLevelItem(4);
        ___qtreewidgetitem32->setText(0, QCoreApplication::translate("PresetsManager", "Occlussion", nullptr));
        QTreeWidgetItem *___qtreewidgetitem33 = ___qtreewidgetitem32->child(0);
        ___qtreewidgetitem33->setText(1, QCoreApplication::translate("PresetsManager", "23", nullptr));
        ___qtreewidgetitem33->setText(0, QCoreApplication::translate("PresetsManager", "Soft", nullptr));
        QTreeWidgetItem *___qtreewidgetitem34 = ___qtreewidgetitem32->child(1);
        ___qtreewidgetitem34->setText(1, QCoreApplication::translate("PresetsManager", "24", nullptr));
        ___qtreewidgetitem34->setText(0, QCoreApplication::translate("PresetsManager", "Brightness", nullptr));
        QTreeWidgetItem *___qtreewidgetitem35 = ___qtreewidgetitem32->child(2);
        ___qtreewidgetitem35->setText(1, QCoreApplication::translate("PresetsManager", "25", nullptr));
        ___qtreewidgetitem35->setText(0, QCoreApplication::translate("PresetsManager", "Invert", nullptr));
        QTreeWidgetItem *___qtreewidgetitem36 = ___qtreewidgetitem32->child(3);
        ___qtreewidgetitem36->setText(1, QCoreApplication::translate("PresetsManager", "26", nullptr));
        ___qtreewidgetitem36->setText(0, QCoreApplication::translate("PresetsManager", "Threshold", nullptr));
        QTreeWidgetItem *___qtreewidgetitem37 = ___qtreewidgetitem32->child(4);
        ___qtreewidgetitem37->setText(1, QCoreApplication::translate("PresetsManager", "27", nullptr));
        ___qtreewidgetitem37->setText(0, QCoreApplication::translate("PresetsManager", "Contrast", nullptr));
        QTreeWidgetItem *___qtreewidgetitem38 = ___qtreewidgetitem32->child(5);
        ___qtreewidgetitem38->setText(1, QCoreApplication::translate("PresetsManager", "28", nullptr));
        ___qtreewidgetitem38->setText(0, QCoreApplication::translate("PresetsManager", "Distance", nullptr));
        QTreeWidgetItem *___qtreewidgetitem39 = ___qtreewidgetitem32->child(6);
        ___qtreewidgetitem39->setText(1, QCoreApplication::translate("PresetsManager", "29", nullptr));
        ___qtreewidgetitem39->setText(0, QCoreApplication::translate("PresetsManager", "Distance Mode", nullptr));
        QTreeWidgetItem *___qtreewidgetitem40 = treeWidget->topLevelItem(5);
        ___qtreewidgetitem40->setText(1, QCoreApplication::translate("PresetsManager", "30", nullptr));
        ___qtreewidgetitem40->setText(0, QCoreApplication::translate("PresetsManager", "Lights", nullptr));
        treeWidget->setSortingEnabled(__sortingEnabled);

        pushButtonSavePreset->setText(QCoreApplication::translate("PresetsManager", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PresetsManager: public Ui_PresetsManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRESETSMANAGER_H
