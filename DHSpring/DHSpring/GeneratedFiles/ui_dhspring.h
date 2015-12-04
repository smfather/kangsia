/********************************************************************************
** Form generated from reading UI file 'dhspringqn9136.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef DHSPRINGQN9136_H
#define DHSPRINGQN9136_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DHSpringClass
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *N;
    QLineEdit *LE_N_value;
    QVBoxLayout *verticalLayout_2;
    QLabel *D;
    QLineEdit *LE_D_Value;
    QVBoxLayout *verticalLayout_3;
    QLabel *d;
    QLineEdit *LE_d_Value;
    QVBoxLayout *verticalLayout_4;
    QLabel *L;
    QLineEdit *LE_Free_length_Value;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_6;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *LE_inst_length;
    QLineEdit *LE_stroke;
    QGroupBox *groupBox_3;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout_4;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_17;
    QLabel *label_8;
    QLineEdit *LE_N_lower;
    QLineEdit *LE_N_upper;
    QLineEdit *LE_N_delta;
    QLabel *label_9;
    QLineEdit *LE_D_lower;
    QLineEdit *LE_D_upper;
    QLineEdit *LE_D_delta;
    QLabel *label_10;
    QLineEdit *LE_d_lower;
    QLineEdit *LE_d_upper;
    QLineEdit *LE_d_delta;
    QLabel *label_11;
    QLineEdit *LE_L_lower;
    QLineEdit *LE_L_upper;
    QLineEdit *LE_L_delta;
    QGroupBox *groupBox_4;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_14;
    QLineEdit *LE_density;
    QLabel *label_15;
    QLineEdit *LE_shear_modulus;
    QLabel *label_16;
    QLineEdit *LE_eq_mass;
    QGroupBox *groupBox_5;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *analyzeButton;
    QPushButton *PB_result;
    QProgressBar *progressBar;
    QGroupBox *groupBox_6;
    QWidget *layoutWidget5;
    QGridLayout *gridLayout_3;
    QLabel *label_21;
    QLineEdit *LE_BH_rate;
    QLabel *label_26;
    QLineEdit *LE_Max_Stress;
    QLabel *label_22;
    QLineEdit *LE_BH_stress_const;
    QWidget *layoutWidget6;
    QGridLayout *gridLayout;
    QLabel *label_24;
    QLineEdit *LE_aspect_ratio_const;
    QLabel *label_35;
    QLineEdit *LE_Potential_const;
    QLabel *label_23;
    QLineEdit *LE_Min_Spring_index_const;
    QLabel *label_18;
    QLineEdit *LE_Max_Spring_index_const;
    QGroupBox *groupBox_7;
    QWidget *layoutWidget7;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_3;
    QLineEdit *LE_Iner_Diameter;
    QVBoxLayout *verticalLayout_12;
    QLabel *label_4;
    QLineEdit *LE_Outer_Diameter;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_5;
    QLineEdit *LE_pre_comp;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_6;
    QLineEdit *LE_total_comp;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_7;
    QLineEdit *LE_block_height;
    QScrollArea *SA_spring_pic;
    QWidget *scrollAreaWidgetContents;
    QLabel *SpringImageLabel;
    QToolButton *TB_ZoomSpringImage;
    QLabel *label_19;
    QTextEdit *messageWindow;
    QMenuBar *menuBar;
    QStatusBar *statusBar;
    QToolBar *inputToolbar;

    void setupUi(QMainWindow *DHSpringClass)
    {
        if (DHSpringClass->objectName().isEmpty())
            DHSpringClass->setObjectName(QStringLiteral("DHSpringClass"));
        DHSpringClass->resize(820, 480);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DHSpringClass->sizePolicy().hasHeightForWidth());
        DHSpringClass->setSizePolicy(sizePolicy);
        DHSpringClass->setMinimumSize(QSize(820, 480));
        DHSpringClass->setMaximumSize(QSize(820, 480));
        centralWidget = new QWidget(DHSpringClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(300, 10, 331, 71));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(11, 21, 311, 42));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        N = new QLabel(layoutWidget);
        N->setObjectName(QStringLiteral("N"));

        verticalLayout->addWidget(N);

        LE_N_value = new QLineEdit(layoutWidget);
        LE_N_value->setObjectName(QStringLiteral("LE_N_value"));
        LE_N_value->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(LE_N_value);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        D = new QLabel(layoutWidget);
        D->setObjectName(QStringLiteral("D"));

        verticalLayout_2->addWidget(D);

        LE_D_Value = new QLineEdit(layoutWidget);
        LE_D_Value->setObjectName(QStringLiteral("LE_D_Value"));
        LE_D_Value->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(LE_D_Value);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        d = new QLabel(layoutWidget);
        d->setObjectName(QStringLiteral("d"));

        verticalLayout_3->addWidget(d);

        LE_d_Value = new QLineEdit(layoutWidget);
        LE_d_Value->setObjectName(QStringLiteral("LE_d_Value"));
        LE_d_Value->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(LE_d_Value);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        L = new QLabel(layoutWidget);
        L->setObjectName(QStringLiteral("L"));

        verticalLayout_4->addWidget(L);

        LE_Free_length_Value = new QLineEdit(layoutWidget);
        LE_Free_length_Value->setObjectName(QStringLiteral("LE_Free_length_Value"));
        LE_Free_length_Value->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(LE_Free_length_Value);


        horizontalLayout->addLayout(verticalLayout_4);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(640, 10, 171, 71));
        layoutWidget1 = new QWidget(groupBox_2);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 22, 151, 40));
        gridLayout_6 = new QGridLayout(layoutWidget1);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget1);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_6->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_6->addWidget(label_2, 0, 1, 1, 1);

        LE_inst_length = new QLineEdit(layoutWidget1);
        LE_inst_length->setObjectName(QStringLiteral("LE_inst_length"));
        LE_inst_length->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(LE_inst_length, 1, 0, 1, 1);

        LE_stroke = new QLineEdit(layoutWidget1);
        LE_stroke->setObjectName(QStringLiteral("LE_stroke"));
        LE_stroke->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(LE_stroke, 1, 1, 1, 1);

        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 220, 271, 151));
        layoutWidget2 = new QWidget(groupBox_3);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 20, 251, 121));
        gridLayout_4 = new QGridLayout(layoutWidget2);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        label_12 = new QLabel(layoutWidget2);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setAcceptDrops(false);
        label_12->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_12, 0, 1, 1, 1);

        label_13 = new QLabel(layoutWidget2);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_13, 0, 2, 1, 1);

        label_17 = new QLabel(layoutWidget2);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_17, 0, 3, 1, 1);

        label_8 = new QLabel(layoutWidget2);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_4->addWidget(label_8, 1, 0, 1, 1);

        LE_N_lower = new QLineEdit(layoutWidget2);
        LE_N_lower->setObjectName(QStringLiteral("LE_N_lower"));
        LE_N_lower->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(LE_N_lower, 1, 1, 1, 1);

        LE_N_upper = new QLineEdit(layoutWidget2);
        LE_N_upper->setObjectName(QStringLiteral("LE_N_upper"));
        LE_N_upper->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(LE_N_upper, 1, 2, 1, 1);

        LE_N_delta = new QLineEdit(layoutWidget2);
        LE_N_delta->setObjectName(QStringLiteral("LE_N_delta"));
        LE_N_delta->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(LE_N_delta, 1, 3, 1, 1);

        label_9 = new QLabel(layoutWidget2);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_4->addWidget(label_9, 2, 0, 1, 1);

        LE_D_lower = new QLineEdit(layoutWidget2);
        LE_D_lower->setObjectName(QStringLiteral("LE_D_lower"));
        LE_D_lower->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(LE_D_lower, 2, 1, 1, 1);

        LE_D_upper = new QLineEdit(layoutWidget2);
        LE_D_upper->setObjectName(QStringLiteral("LE_D_upper"));
        LE_D_upper->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(LE_D_upper, 2, 2, 1, 1);

        LE_D_delta = new QLineEdit(layoutWidget2);
        LE_D_delta->setObjectName(QStringLiteral("LE_D_delta"));
        LE_D_delta->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(LE_D_delta, 2, 3, 1, 1);

        label_10 = new QLabel(layoutWidget2);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_4->addWidget(label_10, 3, 0, 1, 1);

        LE_d_lower = new QLineEdit(layoutWidget2);
        LE_d_lower->setObjectName(QStringLiteral("LE_d_lower"));
        LE_d_lower->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(LE_d_lower, 3, 1, 1, 1);

        LE_d_upper = new QLineEdit(layoutWidget2);
        LE_d_upper->setObjectName(QStringLiteral("LE_d_upper"));
        LE_d_upper->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(LE_d_upper, 3, 2, 1, 1);

        LE_d_delta = new QLineEdit(layoutWidget2);
        LE_d_delta->setObjectName(QStringLiteral("LE_d_delta"));
        LE_d_delta->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(LE_d_delta, 3, 3, 1, 1);

        label_11 = new QLabel(layoutWidget2);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_4->addWidget(label_11, 4, 0, 1, 1);

        LE_L_lower = new QLineEdit(layoutWidget2);
        LE_L_lower->setObjectName(QStringLiteral("LE_L_lower"));
        LE_L_lower->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(LE_L_lower, 4, 1, 1, 1);

        LE_L_upper = new QLineEdit(layoutWidget2);
        LE_L_upper->setObjectName(QStringLiteral("LE_L_upper"));
        LE_L_upper->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(LE_L_upper, 4, 2, 1, 1);

        LE_L_delta = new QLineEdit(layoutWidget2);
        LE_L_delta->setObjectName(QStringLiteral("LE_L_delta"));
        LE_L_delta->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(LE_L_delta, 4, 3, 1, 1);

        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(300, 280, 511, 51));
        layoutWidget3 = new QWidget(groupBox_4);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(11, 20, 491, 22));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_14 = new QLabel(layoutWidget3);
        label_14->setObjectName(QStringLiteral("label_14"));

        horizontalLayout_3->addWidget(label_14);

        LE_density = new QLineEdit(layoutWidget3);
        LE_density->setObjectName(QStringLiteral("LE_density"));
        LE_density->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(LE_density);

        label_15 = new QLabel(layoutWidget3);
        label_15->setObjectName(QStringLiteral("label_15"));

        horizontalLayout_3->addWidget(label_15);

        LE_shear_modulus = new QLineEdit(layoutWidget3);
        LE_shear_modulus->setObjectName(QStringLiteral("LE_shear_modulus"));
        LE_shear_modulus->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(LE_shear_modulus);

        label_16 = new QLabel(layoutWidget3);
        label_16->setObjectName(QStringLiteral("label_16"));

        horizontalLayout_3->addWidget(label_16);

        LE_eq_mass = new QLineEdit(layoutWidget3);
        LE_eq_mass->setObjectName(QStringLiteral("LE_eq_mass"));
        LE_eq_mass->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(LE_eq_mass);

        groupBox_5 = new QGroupBox(centralWidget);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 380, 271, 41));
        layoutWidget4 = new QWidget(groupBox_5);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(10, 12, 251, 25));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        analyzeButton = new QPushButton(layoutWidget4);
        analyzeButton->setObjectName(QStringLiteral("analyzeButton"));

        horizontalLayout_4->addWidget(analyzeButton);

        PB_result = new QPushButton(layoutWidget4);
        PB_result->setObjectName(QStringLiteral("PB_result"));

        horizontalLayout_4->addWidget(PB_result);

        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(300, 340, 511, 32));
        progressBar->setValue(24);
        groupBox_6 = new QGroupBox(centralWidget);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setGeometry(QRect(300, 170, 511, 101));
        layoutWidget5 = new QWidget(groupBox_6);
        layoutWidget5->setObjectName(QStringLiteral("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(11, 18, 211, 74));
        gridLayout_3 = new QGridLayout(layoutWidget5);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        label_21 = new QLabel(layoutWidget5);
        label_21->setObjectName(QStringLiteral("label_21"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_21->sizePolicy().hasHeightForWidth());
        label_21->setSizePolicy(sizePolicy1);
        label_21->setStyleSheet(QStringLiteral(""));
        label_21->setInputMethodHints(Qt::ImhNone);
        label_21->setTextInteractionFlags(Qt::LinksAccessibleByMouse);

        gridLayout_3->addWidget(label_21, 0, 0, 1, 1);

        LE_BH_rate = new QLineEdit(layoutWidget5);
        LE_BH_rate->setObjectName(QStringLiteral("LE_BH_rate"));
        LE_BH_rate->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(LE_BH_rate, 0, 1, 1, 1);

        label_26 = new QLabel(layoutWidget5);
        label_26->setObjectName(QStringLiteral("label_26"));

        gridLayout_3->addWidget(label_26, 1, 0, 1, 1);

        LE_Max_Stress = new QLineEdit(layoutWidget5);
        LE_Max_Stress->setObjectName(QStringLiteral("LE_Max_Stress"));
        LE_Max_Stress->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(LE_Max_Stress, 1, 1, 1, 1);

        label_22 = new QLabel(layoutWidget5);
        label_22->setObjectName(QStringLiteral("label_22"));

        gridLayout_3->addWidget(label_22, 2, 0, 1, 1);

        LE_BH_stress_const = new QLineEdit(layoutWidget5);
        LE_BH_stress_const->setObjectName(QStringLiteral("LE_BH_stress_const"));
        LE_BH_stress_const->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(LE_BH_stress_const, 2, 1, 1, 1);

        layoutWidget6 = new QWidget(groupBox_6);
        layoutWidget6->setObjectName(QStringLiteral("layoutWidget6"));
        layoutWidget6->setGeometry(QRect(230, 19, 271, 74));
        gridLayout = new QGridLayout(layoutWidget6);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_24 = new QLabel(layoutWidget6);
        label_24->setObjectName(QStringLiteral("label_24"));

        gridLayout->addWidget(label_24, 0, 0, 1, 1);

        LE_aspect_ratio_const = new QLineEdit(layoutWidget6);
        LE_aspect_ratio_const->setObjectName(QStringLiteral("LE_aspect_ratio_const"));
        LE_aspect_ratio_const->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(LE_aspect_ratio_const, 0, 1, 1, 3);

        label_35 = new QLabel(layoutWidget6);
        label_35->setObjectName(QStringLiteral("label_35"));

        gridLayout->addWidget(label_35, 1, 0, 1, 1);

        LE_Potential_const = new QLineEdit(layoutWidget6);
        LE_Potential_const->setObjectName(QStringLiteral("LE_Potential_const"));
        LE_Potential_const->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(LE_Potential_const, 1, 1, 1, 3);

        label_23 = new QLabel(layoutWidget6);
        label_23->setObjectName(QStringLiteral("label_23"));

        gridLayout->addWidget(label_23, 2, 0, 1, 1);

        LE_Min_Spring_index_const = new QLineEdit(layoutWidget6);
        LE_Min_Spring_index_const->setObjectName(QStringLiteral("LE_Min_Spring_index_const"));
        LE_Min_Spring_index_const->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(LE_Min_Spring_index_const, 2, 1, 1, 1);

        label_18 = new QLabel(layoutWidget6);
        label_18->setObjectName(QStringLiteral("label_18"));

        gridLayout->addWidget(label_18, 2, 2, 1, 1);

        LE_Max_Spring_index_const = new QLineEdit(layoutWidget6);
        LE_Max_Spring_index_const->setObjectName(QStringLiteral("LE_Max_Spring_index_const"));
        LE_Max_Spring_index_const->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(LE_Max_Spring_index_const, 2, 3, 1, 1);

        groupBox_7 = new QGroupBox(centralWidget);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        groupBox_7->setGeometry(QRect(300, 90, 511, 71));
        layoutWidget7 = new QWidget(groupBox_7);
        layoutWidget7->setObjectName(QStringLiteral("layoutWidget7"));
        layoutWidget7->setGeometry(QRect(10, 20, 491, 42));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget7);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        label_3 = new QLabel(layoutWidget7);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_5->addWidget(label_3);

        LE_Iner_Diameter = new QLineEdit(layoutWidget7);
        LE_Iner_Diameter->setObjectName(QStringLiteral("LE_Iner_Diameter"));
        LE_Iner_Diameter->setAutoFillBackground(false);
        LE_Iner_Diameter->setStyleSheet(QStringLiteral("background-color: rgb(222, 222, 222);"));
        LE_Iner_Diameter->setAlignment(Qt::AlignCenter);
        LE_Iner_Diameter->setReadOnly(true);

        verticalLayout_5->addWidget(LE_Iner_Diameter);


        horizontalLayout_2->addLayout(verticalLayout_5);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        label_4 = new QLabel(layoutWidget7);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout_12->addWidget(label_4);

        LE_Outer_Diameter = new QLineEdit(layoutWidget7);
        LE_Outer_Diameter->setObjectName(QStringLiteral("LE_Outer_Diameter"));
        LE_Outer_Diameter->setStyleSheet(QStringLiteral("background-color: rgb(222, 222, 222);"));
        LE_Outer_Diameter->setAlignment(Qt::AlignCenter);
        LE_Outer_Diameter->setReadOnly(true);

        verticalLayout_12->addWidget(LE_Outer_Diameter);


        horizontalLayout_2->addLayout(verticalLayout_12);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        label_5 = new QLabel(layoutWidget7);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout_8->addWidget(label_5);

        LE_pre_comp = new QLineEdit(layoutWidget7);
        LE_pre_comp->setObjectName(QStringLiteral("LE_pre_comp"));
        LE_pre_comp->setStyleSheet(QStringLiteral("background-color: rgb(222, 222, 222);"));
        LE_pre_comp->setAlignment(Qt::AlignCenter);
        LE_pre_comp->setReadOnly(true);

        verticalLayout_8->addWidget(LE_pre_comp);


        horizontalLayout_2->addLayout(verticalLayout_8);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        label_6 = new QLabel(layoutWidget7);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout_9->addWidget(label_6);

        LE_total_comp = new QLineEdit(layoutWidget7);
        LE_total_comp->setObjectName(QStringLiteral("LE_total_comp"));
        LE_total_comp->setStyleSheet(QStringLiteral("background-color: rgb(222, 222, 222);"));
        LE_total_comp->setAlignment(Qt::AlignCenter);
        LE_total_comp->setReadOnly(true);

        verticalLayout_9->addWidget(LE_total_comp);


        horizontalLayout_2->addLayout(verticalLayout_9);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        label_7 = new QLabel(layoutWidget7);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout_10->addWidget(label_7);

        LE_block_height = new QLineEdit(layoutWidget7);
        LE_block_height->setObjectName(QStringLiteral("LE_block_height"));
        LE_block_height->setStyleSheet(QStringLiteral("background-color: rgb(222, 222, 222);"));
        LE_block_height->setAlignment(Qt::AlignCenter);
        LE_block_height->setReadOnly(true);

        verticalLayout_10->addWidget(LE_block_height);


        horizontalLayout_2->addLayout(verticalLayout_10);

        SA_spring_pic = new QScrollArea(centralWidget);
        SA_spring_pic->setObjectName(QStringLiteral("SA_spring_pic"));
        SA_spring_pic->setGeometry(QRect(10, 70, 271, 141));
        SA_spring_pic->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        SA_spring_pic->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        SA_spring_pic->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 269, 139));
        SpringImageLabel = new QLabel(scrollAreaWidgetContents);
        SpringImageLabel->setObjectName(QStringLiteral("SpringImageLabel"));
        SpringImageLabel->setGeometry(QRect(0, 0, 271, 141));
        sizePolicy1.setHeightForWidth(SpringImageLabel->sizePolicy().hasHeightForWidth());
        SpringImageLabel->setSizePolicy(sizePolicy1);
        SpringImageLabel->setPixmap(QPixmap(QString::fromUtf8(":/DHSpring/spring.PNG")));
        SpringImageLabel->setScaledContents(true);
        SpringImageLabel->setOpenExternalLinks(true);
        SpringImageLabel->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);
        TB_ZoomSpringImage = new QToolButton(scrollAreaWidgetContents);
        TB_ZoomSpringImage->setObjectName(QStringLiteral("TB_ZoomSpringImage"));
        TB_ZoomSpringImage->setGeometry(QRect(0, 121, 21, 18));
        QIcon icon;
        icon.addFile(QStringLiteral(":/DHSpring/Plus.png"), QSize(), QIcon::Normal, QIcon::Off);
        TB_ZoomSpringImage->setIcon(icon);
        SA_spring_pic->setWidget(scrollAreaWidgetContents);
        label_19 = new QLabel(centralWidget);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(10, 10, 271, 51));
        label_19->setPixmap(QPixmap(QString::fromUtf8(":/DHSpring/logo.PNG")));
        label_19->setScaledContents(true);
        messageWindow = new QTextEdit(centralWidget);
        messageWindow->setObjectName(QStringLiteral("messageWindow"));
        messageWindow->setGeometry(QRect(300, 380, 511, 41));
        messageWindow->setReadOnly(true);
        DHSpringClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DHSpringClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 820, 21));
        DHSpringClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(DHSpringClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        DHSpringClass->setStatusBar(statusBar);
        inputToolbar = new QToolBar(DHSpringClass);
        inputToolbar->setObjectName(QStringLiteral("inputToolbar"));
        DHSpringClass->addToolBar(Qt::TopToolBarArea, inputToolbar);
        QWidget::setTabOrder(LE_N_value, LE_D_Value);
        QWidget::setTabOrder(LE_D_Value, LE_d_Value);
        QWidget::setTabOrder(LE_d_Value, LE_Free_length_Value);
        QWidget::setTabOrder(LE_Free_length_Value, LE_inst_length);
        QWidget::setTabOrder(LE_inst_length, LE_stroke);
        QWidget::setTabOrder(LE_stroke, LE_BH_rate);
        QWidget::setTabOrder(LE_BH_rate, LE_aspect_ratio_const);
        QWidget::setTabOrder(LE_aspect_ratio_const, LE_Max_Stress);
        QWidget::setTabOrder(LE_Max_Stress, LE_Potential_const);
        QWidget::setTabOrder(LE_Potential_const, LE_BH_stress_const);
        QWidget::setTabOrder(LE_BH_stress_const, LE_Min_Spring_index_const);
        QWidget::setTabOrder(LE_Min_Spring_index_const, LE_Max_Spring_index_const);
        QWidget::setTabOrder(LE_Max_Spring_index_const, LE_N_lower);
        QWidget::setTabOrder(LE_N_lower, LE_N_upper);
        QWidget::setTabOrder(LE_N_upper, LE_N_delta);
        QWidget::setTabOrder(LE_N_delta, LE_D_lower);
        QWidget::setTabOrder(LE_D_lower, LE_D_upper);
        QWidget::setTabOrder(LE_D_upper, LE_D_delta);
        QWidget::setTabOrder(LE_D_delta, LE_d_lower);
        QWidget::setTabOrder(LE_d_lower, LE_d_upper);
        QWidget::setTabOrder(LE_d_upper, LE_d_delta);
        QWidget::setTabOrder(LE_d_delta, LE_L_lower);
        QWidget::setTabOrder(LE_L_lower, LE_L_upper);
        QWidget::setTabOrder(LE_L_upper, LE_L_delta);
        QWidget::setTabOrder(LE_L_delta, LE_density);
        QWidget::setTabOrder(LE_density, LE_shear_modulus);
        QWidget::setTabOrder(LE_shear_modulus, LE_eq_mass);
        QWidget::setTabOrder(LE_eq_mass, analyzeButton);
        QWidget::setTabOrder(analyzeButton, PB_result);
        QWidget::setTabOrder(PB_result, LE_Iner_Diameter);
        QWidget::setTabOrder(LE_Iner_Diameter, LE_Outer_Diameter);
        QWidget::setTabOrder(LE_Outer_Diameter, LE_pre_comp);
        QWidget::setTabOrder(LE_pre_comp, LE_total_comp);
        QWidget::setTabOrder(LE_total_comp, LE_block_height);

        retranslateUi(DHSpringClass);

        QMetaObject::connectSlotsByName(DHSpringClass);
    } // setupUi

    void retranslateUi(QMainWindow *DHSpringClass)
    {
        DHSpringClass->setWindowTitle(QApplication::translate("DHSpringClass", "DHSpring v1.00", 0));
        groupBox->setTitle(QApplication::translate("DHSpringClass", "Reference of design variable", 0));
        N->setText(QApplication::translate("DHSpringClass", "\354\234\240\355\232\250\352\266\214\354\210\230(N)", 0));
        D->setText(QApplication::translate("DHSpringClass", "\354\244\221\354\213\254\352\262\275(D)", 0));
        d->setText(QApplication::translate("DHSpringClass", "\354\206\214\354\204\240\352\262\275(d)", 0));
        L->setText(QApplication::translate("DHSpringClass", "\354\236\220\354\234\240\354\236\245(L)", 0));
        groupBox_2->setTitle(QApplication::translate("DHSpringClass", "System variable", 0));
        label->setText(QApplication::translate("DHSpringClass", "\354\236\245\354\260\251\352\270\270\354\235\264", 0));
        label_2->setText(QApplication::translate("DHSpringClass", "\354\212\244\355\212\270\353\241\234\355\201\254", 0));
        groupBox_3->setTitle(QApplication::translate("DHSpringClass", "Design variable", 0));
        label_12->setText(QApplication::translate("DHSpringClass", "\355\225\230\355\225\234", 0));
        label_13->setText(QApplication::translate("DHSpringClass", "\354\203\201\355\225\234", 0));
        label_17->setText(QApplication::translate("DHSpringClass", "\354\246\235\353\266\204", 0));
        label_8->setText(QApplication::translate("DHSpringClass", "\354\234\240\355\232\250\352\266\214\354\210\230(N)", 0));
        label_9->setText(QApplication::translate("DHSpringClass", "\354\244\221\354\213\254\352\262\275(D)", 0));
        label_10->setText(QApplication::translate("DHSpringClass", "\354\236\254\354\247\210\352\262\275(d)", 0));
        label_11->setText(QApplication::translate("DHSpringClass", "\354\236\220\354\234\240\354\236\245(L)", 0));
        groupBox_4->setTitle(QApplication::translate("DHSpringClass", "Material variable", 0));
        label_14->setText(QApplication::translate("DHSpringClass", "\353\260\200\353\217\204", 0));
        label_15->setText(QApplication::translate("DHSpringClass", "\354\240\204\353\213\250 \355\203\204\354\204\261\353\245\240", 0));
        label_16->setText(QApplication::translate("DHSpringClass", "\353\223\261\352\260\200\354\247\210\353\237\211", 0));
        groupBox_5->setTitle(QApplication::translate("DHSpringClass", "Simulation", 0));
        analyzeButton->setText(QApplication::translate("DHSpringClass", "\355\225\264\354\204\235", 0));
        PB_result->setText(QApplication::translate("DHSpringClass", "\352\262\260\352\263\274", 0));
        groupBox_6->setTitle(QApplication::translate("DHSpringClass", "Constraint condition", 0));
#ifndef QT_NO_TOOLTIP
        label_21->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        label_21->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        label_21->setText(QApplication::translate("DHSpringClass", "\353\260\200\354\260\251\354\234\250(\354\203\201\355\225\234)", 0));
        label_26->setText(QApplication::translate("DHSpringClass", "\354\265\234\353\214\200\354\235\221\353\240\245(\354\203\201\355\225\234)", 0));
        label_22->setText(QApplication::translate("DHSpringClass", "\353\260\200\354\260\251\352\263\240\354\235\221\353\240\245(\354\203\201\355\225\234)", 0));
        label_24->setText(QApplication::translate("DHSpringClass", "\354\242\205\355\232\241\353\271\204(\354\203\201\355\225\234)", 0));
        label_35->setText(QApplication::translate("DHSpringClass", "\354\234\240\355\232\250\355\217\254\355\205\220\354\205\234(\302\261%)", 0));
        label_23->setText(QApplication::translate("DHSpringClass", "\354\212\244\355\224\204\353\247\201\354\247\200\354\210\230(\355\225\230\355\225\234~\354\203\201\355\225\234)", 0));
        label_18->setText(QApplication::translate("DHSpringClass", "~", 0));
        groupBox_7->setTitle(QApplication::translate("DHSpringClass", "Spring spec.", 0));
        label_3->setText(QApplication::translate("DHSpringClass", "\353\202\264\352\262\275(D1)", 0));
        label_4->setText(QApplication::translate("DHSpringClass", "\354\231\270\352\262\275(D2)", 0));
        label_5->setText(QApplication::translate("DHSpringClass", "\354\264\210\352\270\260 \354\225\225\354\266\225\353\237\211", 0));
        label_6->setText(QApplication::translate("DHSpringClass", "\354\265\234\353\214\200 \354\225\225\354\266\225\353\237\211", 0));
        label_7->setText(QApplication::translate("DHSpringClass", "\353\260\200\354\260\251\352\263\240", 0));
        SpringImageLabel->setText(QString());
        TB_ZoomSpringImage->setText(QApplication::translate("DHSpringClass", "...", 0));
        label_19->setText(QString());
        inputToolbar->setWindowTitle(QApplication::translate("DHSpringClass", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class DHSpringClass: public Ui_DHSpringClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // DHSPRINGQN9136_H
