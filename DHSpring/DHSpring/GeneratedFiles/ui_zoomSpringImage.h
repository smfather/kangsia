/********************************************************************************
** Form generated from reading UI file 'zoomSpringImageHp6640.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef ZOOMSPRINGIMAGEHP6640_H
#define ZOOMSPRINGIMAGEHP6640_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SpringImageZoomDialog
{
public:
    QGridLayout *gridLayout;
    QScrollArea *SA;
    QWidget *scrollAreaWidgetContents;
    QLabel *label;
    QLineEdit *LE_Outer_Diameter;
    QLineEdit *LE_Middle_Diameter;
    QLineEdit *LE_Inner_Diameter;
    QLineEdit *LE_Free_Length;
    QLineEdit *LE_Inst_Length;
    QLineEdit *LE_Init_Comp;
    QLineEdit *LE_d;
    QLineEdit *LE_Stroke;
    QLineEdit *LE_Max_Comp;

    void setupUi(QDialog *SpringImageZoomDialog)
    {
        if (SpringImageZoomDialog->objectName().isEmpty())
            SpringImageZoomDialog->setObjectName(QStringLiteral("SpringImageZoomDialog"));
        SpringImageZoomDialog->resize(818, 338);
        SpringImageZoomDialog->setMinimumSize(QSize(818, 338));
        SpringImageZoomDialog->setMaximumSize(QSize(818, 338));
        gridLayout = new QGridLayout(SpringImageZoomDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        SA = new QScrollArea(SpringImageZoomDialog);
        SA->setObjectName(QStringLiteral("SA"));
        SA->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 798, 318));
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 801, 321));
        label->setPixmap(QPixmap(QString::fromUtf8("spring.PNG")));
        label->setScaledContents(true);
        LE_Outer_Diameter = new QLineEdit(scrollAreaWidgetContents);
        LE_Outer_Diameter->setObjectName(QStringLiteral("LE_Outer_Diameter"));
        LE_Outer_Diameter->setGeometry(QRect(40, 198, 31, 20));
        LE_Outer_Diameter->setLayoutDirection(Qt::LeftToRight);
        LE_Outer_Diameter->setCursorPosition(1);
        LE_Outer_Diameter->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        LE_Outer_Diameter->setCursorMoveStyle(Qt::LogicalMoveStyle);
        LE_Middle_Diameter = new QLineEdit(scrollAreaWidgetContents);
        LE_Middle_Diameter->setObjectName(QStringLiteral("LE_Middle_Diameter"));
        LE_Middle_Diameter->setGeometry(QRect(80, 198, 31, 20));
        LE_Middle_Diameter->setLayoutDirection(Qt::LeftToRight);
        LE_Middle_Diameter->setCursorPosition(1);
        LE_Middle_Diameter->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        LE_Middle_Diameter->setCursorMoveStyle(Qt::LogicalMoveStyle);
        LE_Inner_Diameter = new QLineEdit(scrollAreaWidgetContents);
        LE_Inner_Diameter->setObjectName(QStringLiteral("LE_Inner_Diameter"));
        LE_Inner_Diameter->setGeometry(QRect(120, 198, 31, 20));
        LE_Inner_Diameter->setLayoutDirection(Qt::LeftToRight);
        LE_Inner_Diameter->setCursorPosition(1);
        LE_Inner_Diameter->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        LE_Inner_Diameter->setCursorMoveStyle(Qt::LogicalMoveStyle);
        LE_Free_Length = new QLineEdit(scrollAreaWidgetContents);
        LE_Free_Length->setObjectName(QStringLiteral("LE_Free_Length"));
        LE_Free_Length->setGeometry(QRect(620, 10, 31, 20));
        LE_Free_Length->setLayoutDirection(Qt::LeftToRight);
        LE_Free_Length->setCursorPosition(1);
        LE_Free_Length->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        LE_Free_Length->setCursorMoveStyle(Qt::LogicalMoveStyle);
        LE_Inst_Length = new QLineEdit(scrollAreaWidgetContents);
        LE_Inst_Length->setObjectName(QStringLiteral("LE_Inst_Length"));
        LE_Inst_Length->setGeometry(QRect(560, 43, 31, 20));
        LE_Inst_Length->setLayoutDirection(Qt::LeftToRight);
        LE_Inst_Length->setCursorPosition(1);
        LE_Inst_Length->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        LE_Inst_Length->setCursorMoveStyle(Qt::LogicalMoveStyle);
        LE_Init_Comp = new QLineEdit(scrollAreaWidgetContents);
        LE_Init_Comp->setObjectName(QStringLiteral("LE_Init_Comp"));
        LE_Init_Comp->setGeometry(QRect(770, 46, 31, 20));
        LE_Init_Comp->setLayoutDirection(Qt::LeftToRight);
        LE_Init_Comp->setCursorPosition(1);
        LE_Init_Comp->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        LE_Init_Comp->setCursorMoveStyle(Qt::LogicalMoveStyle);
        LE_d = new QLineEdit(scrollAreaWidgetContents);
        LE_d->setObjectName(QStringLiteral("LE_d"));
        LE_d->setGeometry(QRect(460, 260, 31, 20));
        LE_d->setLayoutDirection(Qt::LeftToRight);
        LE_d->setCursorPosition(1);
        LE_d->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        LE_d->setCursorMoveStyle(Qt::LogicalMoveStyle);
        LE_Stroke = new QLineEdit(scrollAreaWidgetContents);
        LE_Stroke->setObjectName(QStringLiteral("LE_Stroke"));
        LE_Stroke->setGeometry(QRect(660, 240, 31, 20));
        LE_Stroke->setLayoutDirection(Qt::LeftToRight);
        LE_Stroke->setCursorPosition(1);
        LE_Stroke->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        LE_Stroke->setCursorMoveStyle(Qt::LogicalMoveStyle);
        LE_Max_Comp = new QLineEdit(scrollAreaWidgetContents);
        LE_Max_Comp->setObjectName(QStringLiteral("LE_Max_Comp"));
        LE_Max_Comp->setGeometry(QRect(670, 270, 31, 20));
        LE_Max_Comp->setLayoutDirection(Qt::LeftToRight);
        LE_Max_Comp->setCursorPosition(1);
        LE_Max_Comp->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        LE_Max_Comp->setCursorMoveStyle(Qt::LogicalMoveStyle);
        SA->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(SA, 0, 0, 1, 1);


        retranslateUi(SpringImageZoomDialog);

        QMetaObject::connectSlotsByName(SpringImageZoomDialog);
    } // setupUi

    void retranslateUi(QDialog *SpringImageZoomDialog)
    {
        SpringImageZoomDialog->setWindowTitle(QApplication::translate("SpringImageZoomDialog", "Spring image", 0));
        label->setText(QString());
        LE_Outer_Diameter->setText(QApplication::translate("SpringImageZoomDialog", "0", 0));
        LE_Middle_Diameter->setText(QApplication::translate("SpringImageZoomDialog", "0", 0));
        LE_Inner_Diameter->setText(QApplication::translate("SpringImageZoomDialog", "0", 0));
        LE_Free_Length->setText(QApplication::translate("SpringImageZoomDialog", "0", 0));
        LE_Inst_Length->setText(QApplication::translate("SpringImageZoomDialog", "0", 0));
        LE_Init_Comp->setText(QApplication::translate("SpringImageZoomDialog", "0", 0));
        LE_d->setText(QApplication::translate("SpringImageZoomDialog", "0", 0));
        LE_Stroke->setText(QApplication::translate("SpringImageZoomDialog", "0", 0));
        LE_Max_Comp->setText(QApplication::translate("SpringImageZoomDialog", "0", 0));
    } // retranslateUi

};

namespace Ui {
    class SpringImageZoomDialog: public Ui_SpringImageZoomDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // ZOOMSPRINGIMAGEHP6640_H
