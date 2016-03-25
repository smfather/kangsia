/********************************************************************************
** Form generated from reading UI file 'parviewNl7996.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef PARVIEWNL7996_H
#define PARVIEWNL7996_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_parVIEW
{
public:
    QAction *actionChange_Shape;
	QAction *actionExport;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QScrollArea *GraphicArea;
    QWidget *scrollAreaWidgetContents;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *secToolBar;

    void setupUi(QMainWindow *parVIEW)
    {
        if (parVIEW->objectName().isEmpty())
            parVIEW->setObjectName(QStringLiteral("parVIEW"));
        parVIEW->resize(600, 400);
        actionChange_Shape = new QAction(parVIEW);
        actionChange_Shape->setObjectName(QStringLiteral("actionChange_Shape"));
        actionChange_Shape->setCheckable(true);
		actionExport = new QAction(parVIEW);
		actionExport->setObjectName(QStringLiteral("actionExport"));
		actionExport->setCheckable(true);
        centralWidget = new QWidget(parVIEW);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        GraphicArea = new QScrollArea(centralWidget);
        GraphicArea->setObjectName(QStringLiteral("GraphicArea"));
        GraphicArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 580, 315));
        GraphicArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(GraphicArea, 0, 0, 1, 1);

        parVIEW->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(parVIEW);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        parVIEW->setMenuBar(menuBar);
        mainToolBar = new QToolBar(parVIEW);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setMovable(false);
        mainToolBar->setFloatable(false);
        parVIEW->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(parVIEW);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        parVIEW->setStatusBar(statusBar);
        secToolBar = new QToolBar(parVIEW);
        secToolBar->setObjectName(QStringLiteral("secToolBar"));
        parVIEW->addToolBar(Qt::TopToolBarArea, secToolBar);
        parVIEW->insertToolBarBreak(secToolBar);

        menuBar->addAction(menu->menuAction());
		menu->addAction(actionChange_Shape);
		menu->addAction(actionExport);

        retranslateUi(parVIEW);

        QMetaObject::connectSlotsByName(parVIEW);
    } // setupUi

    void retranslateUi(QMainWindow *parVIEW)
    {
        parVIEW->setWindowTitle(QApplication::translate("parVIEW", "parVIEW", 0));
        actionChange_Shape->setText(QApplication::translate("parVIEW", "Change Shape", 0));
		actionExport->setText(QApplication::translate("parVIEW", "Export", 0));
        menu->setTitle(QApplication::translate("parVIEW", "\352\270\260\353\212\245", 0));
        secToolBar->setWindowTitle(QApplication::translate("parVIEW", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class parVIEW: public Ui_parVIEW {};
} // namespace Ui

QT_END_NAMESPACE

#endif // PARVIEWNL7996_H
