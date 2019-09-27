/********************************************************************************
** Form generated from reading UI file 'nbselector.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NBSELECTOR_H
#define UI_NBSELECTOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_NBSelector
{
public:
    QGridLayout *gridLayout;
    QPushButton *NUL;
    QPushButton *NUM;
    QPushButton *NUR;
    QPushButton *NML;
    QPushButton *NMM;
    QPushButton *NMR;
    QPushButton *NBL;
    QPushButton *NBM;
    QPushButton *NBR;
    QPushButton *pushButtonResetNeighbours;
    QPushButton *pushButton;

    void setupUi(QDialog *NBSelector)
    {
        if (NBSelector->objectName().isEmpty())
            NBSelector->setObjectName(QString::fromUtf8("NBSelector"));
        NBSelector->resize(400, 430);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(NBSelector->sizePolicy().hasHeightForWidth());
        NBSelector->setSizePolicy(sizePolicy);
        NBSelector->setMaximumSize(QSize(400, 430));
        gridLayout = new QGridLayout(NBSelector);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        NUL = new QPushButton(NBSelector);
        NUL->setObjectName(QString::fromUtf8("NUL"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(NUL->sizePolicy().hasHeightForWidth());
        NUL->setSizePolicy(sizePolicy1);
        NUL->setMinimumSize(QSize(123, 123));
        NUL->setMaximumSize(QSize(16777215, 16777215));
        NUL->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid  #33334D;\n"
"    border-radius: 6px;\n"
"}\n"
"QPushButton:hover:!pressed\n"
"{\n"
"  border: 2px solid #8080a0;\n"
"}R"));
        NUL->setIconSize(QSize(115, 115));
        NUL->setFlat(false);

        gridLayout->addWidget(NUL, 0, 0, 1, 1);

        NUM = new QPushButton(NBSelector);
        NUM->setObjectName(QString::fromUtf8("NUM"));
        sizePolicy1.setHeightForWidth(NUM->sizePolicy().hasHeightForWidth());
        NUM->setSizePolicy(sizePolicy1);
        NUM->setMinimumSize(QSize(123, 123));
        NUM->setMaximumSize(QSize(16777215, 16777215));
        NUM->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid  #33334D;\n"
"    border-radius: 6px;\n"
"}\n"
"QPushButton:hover:!pressed\n"
"{\n"
"  border: 2px solid #8080a0;\n"
"}R"));
        NUM->setIconSize(QSize(115, 115));
        NUM->setFlat(false);

        gridLayout->addWidget(NUM, 0, 1, 1, 1);

        NUR = new QPushButton(NBSelector);
        NUR->setObjectName(QString::fromUtf8("NUR"));
        sizePolicy1.setHeightForWidth(NUR->sizePolicy().hasHeightForWidth());
        NUR->setSizePolicy(sizePolicy1);
        NUR->setMinimumSize(QSize(123, 123));
        NUR->setMaximumSize(QSize(16777215, 16777215));
        NUR->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid  #33334D;\n"
"    border-radius: 6px;\n"
"}\n"
"QPushButton:hover:!pressed\n"
"{\n"
"  border: 2px solid #8080a0;\n"
"}R"));
        NUR->setIconSize(QSize(115, 115));
        NUR->setFlat(false);

        gridLayout->addWidget(NUR, 0, 2, 1, 1);

        NML = new QPushButton(NBSelector);
        NML->setObjectName(QString::fromUtf8("NML"));
        sizePolicy1.setHeightForWidth(NML->sizePolicy().hasHeightForWidth());
        NML->setSizePolicy(sizePolicy1);
        NML->setMinimumSize(QSize(123, 123));
        NML->setMaximumSize(QSize(16777215, 16777215));
        NML->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid  #33334D;\n"
"    border-radius: 6px;\n"
"}\n"
"QPushButton:hover:!pressed\n"
"{\n"
"  border: 2px solid #8080a0;\n"
"}R"));
        NML->setIconSize(QSize(115, 115));
        NML->setFlat(false);

        gridLayout->addWidget(NML, 1, 0, 1, 1);

        NMM = new QPushButton(NBSelector);
        NMM->setObjectName(QString::fromUtf8("NMM"));
        sizePolicy1.setHeightForWidth(NMM->sizePolicy().hasHeightForWidth());
        NMM->setSizePolicy(sizePolicy1);
        NMM->setMinimumSize(QSize(123, 123));
        NMM->setMaximumSize(QSize(16777215, 16777215));
        NMM->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid  #33334D;\n"
"    border-radius: 6px;\n"
"}\n"
"QPushButton:hover:!pressed\n"
"{\n"
"  border: 2px solid #8080a0;\n"
"}R"));
        NMM->setIconSize(QSize(115, 115));
        NMM->setFlat(false);

        gridLayout->addWidget(NMM, 1, 1, 1, 1);

        NMR = new QPushButton(NBSelector);
        NMR->setObjectName(QString::fromUtf8("NMR"));
        sizePolicy1.setHeightForWidth(NMR->sizePolicy().hasHeightForWidth());
        NMR->setSizePolicy(sizePolicy1);
        NMR->setMinimumSize(QSize(123, 123));
        NMR->setMaximumSize(QSize(16777215, 16777215));
        NMR->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid  #33334D;\n"
"    border-radius: 6px;\n"
"}\n"
"QPushButton:hover:!pressed\n"
"{\n"
"  border: 2px solid #8080a0;\n"
"}R"));
        NMR->setIconSize(QSize(115, 115));
        NMR->setFlat(false);

        gridLayout->addWidget(NMR, 1, 2, 1, 1);

        NBL = new QPushButton(NBSelector);
        NBL->setObjectName(QString::fromUtf8("NBL"));
        sizePolicy1.setHeightForWidth(NBL->sizePolicy().hasHeightForWidth());
        NBL->setSizePolicy(sizePolicy1);
        NBL->setMinimumSize(QSize(123, 123));
        NBL->setMaximumSize(QSize(16777215, 16777215));
        NBL->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid  #33334D;\n"
"    border-radius: 6px;\n"
"}\n"
"QPushButton:hover:!pressed\n"
"{\n"
"  border: 2px solid #8080a0;\n"
"}R"));
        NBL->setIconSize(QSize(115, 115));
        NBL->setFlat(false);

        gridLayout->addWidget(NBL, 2, 0, 1, 1);

        NBM = new QPushButton(NBSelector);
        NBM->setObjectName(QString::fromUtf8("NBM"));
        sizePolicy1.setHeightForWidth(NBM->sizePolicy().hasHeightForWidth());
        NBM->setSizePolicy(sizePolicy1);
        NBM->setMinimumSize(QSize(123, 123));
        NBM->setMaximumSize(QSize(16777215, 16777215));
        NBM->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid  #33334D;\n"
"    border-radius: 6px;\n"
"}\n"
"QPushButton:hover:!pressed\n"
"{\n"
"  border: 2px solid #8080a0;\n"
"}R"));
        NBM->setIconSize(QSize(115, 115));
        NBM->setFlat(false);

        gridLayout->addWidget(NBM, 2, 1, 1, 1);

        NBR = new QPushButton(NBSelector);
        NBR->setObjectName(QString::fromUtf8("NBR"));
        sizePolicy1.setHeightForWidth(NBR->sizePolicy().hasHeightForWidth());
        NBR->setSizePolicy(sizePolicy1);
        NBR->setMinimumSize(QSize(123, 123));
        NBR->setMaximumSize(QSize(16777215, 16777215));
        NBR->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid  #33334D;\n"
"    border-radius: 6px;\n"
"}\n"
"QPushButton:hover:!pressed\n"
"{\n"
"  border: 2px solid #8080a0;\n"
"}R"));
        NBR->setIconSize(QSize(115, 115));
        NBR->setFlat(false);

        gridLayout->addWidget(NBR, 2, 2, 1, 1);

        pushButtonResetNeighbours = new QPushButton(NBSelector);
        pushButtonResetNeighbours->setObjectName(QString::fromUtf8("pushButtonResetNeighbours"));

        gridLayout->addWidget(pushButtonResetNeighbours, 3, 2, 1, 1);

        pushButton = new QPushButton(NBSelector);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 3, 1, 1, 1);


        retranslateUi(NBSelector);

        NUL->setDefault(false);
        NUM->setDefault(false);
        NUR->setDefault(false);
        NML->setDefault(false);
        NMM->setDefault(false);
        NMR->setDefault(false);
        NBL->setDefault(false);
        NBM->setDefault(false);
        NBR->setDefault(false);


        QMetaObject::connectSlotsByName(NBSelector);
    } // setupUi

    void retranslateUi(QDialog *NBSelector)
    {
        NBSelector->setWindowTitle(QCoreApplication::translate("NBSelector", "Neighbours selector", nullptr));
        NUL->setText(QString());
        NUM->setText(QString());
        NUR->setText(QString());
        NML->setText(QString());
        NMM->setText(QString());
        NMR->setText(QString());
        NBL->setText(QString());
        NBM->setText(QString());
        NBR->setText(QString());
        pushButtonResetNeighbours->setText(QCoreApplication::translate("NBSelector", "Reset Neighbours", nullptr));
        pushButton->setText(QCoreApplication::translate("NBSelector", "Empty Neighbours", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NBSelector: public Ui_NBSelector {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NBSELECTOR_H
