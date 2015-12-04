/********************************************************************************
** Form generated from reading UI file 'resultTable.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESULTTABLE_H
#define UI_RESULTTABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_resultTable
{
public:
    QGridLayout *gridLayout;
    QTableView *tableView;

    void setupUi(QDialog *resultTable)
    {
        if (resultTable->objectName().isEmpty())
            resultTable->setObjectName(QStringLiteral("resultTable"));
        resultTable->resize(686, 474);
        gridLayout = new QGridLayout(resultTable);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tableView = new QTableView(resultTable);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::EditKeyPressed|QAbstractItemView::SelectedClicked);
        tableView->setDefaultDropAction(Qt::IgnoreAction);
        tableView->setSelectionBehavior(QAbstractItemView::SelectItems);

        gridLayout->addWidget(tableView, 0, 0, 1, 1);


        retranslateUi(resultTable);

        QMetaObject::connectSlotsByName(resultTable);
    } // setupUi

    void retranslateUi(QDialog *resultTable)
    {
        resultTable->setWindowTitle(QApplication::translate("resultTable", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class resultTable: public Ui_resultTable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESULTTABLE_H
