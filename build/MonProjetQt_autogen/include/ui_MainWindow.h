/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *settingsGroupBox;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *puzzleSizeLabel;
    QSpacerItem *horizontalSpacer;
    QSpinBox *puzzleSizeSpinBox;
    QHBoxLayout *horizontalLayout_6;
    QLabel *puzzleStateLabel;
    QSpacerItem *horizontalSpacer_2;
    QComboBox *puzzleStateComboBox;
    QHBoxLayout *horizontalLayout_9;
    QLabel *iterationsLabel;
    QSpacerItem *horizontalSpacer_3;
    QSpinBox *iterationsSpinBox;
    QSpacerItem *verticalSpacer;
    QPushButton *createPuzzlePushButton;
    QGroupBox *puzzleGroupBox;
    QVBoxLayout *verticalLayout_4;
    QWidget *puzzleWidget;
    QVBoxLayout *verticalLayout_5;
    QGridLayout *puzzleGridLayout;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1200, 800);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_3 = new QHBoxLayout(centralwidget);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(-1, -1, 0, -1);
        settingsGroupBox = new QGroupBox(centralwidget);
        settingsGroupBox->setObjectName("settingsGroupBox");
        settingsGroupBox->setMaximumSize(QSize(300, 16777215));
        verticalLayout_3 = new QVBoxLayout(settingsGroupBox);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(-1, 0, -1, -1);
        puzzleSizeLabel = new QLabel(settingsGroupBox);
        puzzleSizeLabel->setObjectName("puzzleSizeLabel");

        horizontalLayout_4->addWidget(puzzleSizeLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        puzzleSizeSpinBox = new QSpinBox(settingsGroupBox);
        puzzleSizeSpinBox->setObjectName("puzzleSizeSpinBox");
        puzzleSizeSpinBox->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::UpDownArrows);
        puzzleSizeSpinBox->setMaximum(999);

        horizontalLayout_4->addWidget(puzzleSizeSpinBox);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(-1, 0, -1, -1);
        puzzleStateLabel = new QLabel(settingsGroupBox);
        puzzleStateLabel->setObjectName("puzzleStateLabel");

        horizontalLayout_6->addWidget(puzzleStateLabel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);

        puzzleStateComboBox = new QComboBox(settingsGroupBox);
        puzzleStateComboBox->addItem(QString());
        puzzleStateComboBox->addItem(QString());
        puzzleStateComboBox->addItem(QString());
        puzzleStateComboBox->setObjectName("puzzleStateComboBox");
        puzzleStateComboBox->setFrame(true);

        horizontalLayout_6->addWidget(puzzleStateComboBox);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        horizontalLayout_9->setContentsMargins(-1, 0, -1, -1);
        iterationsLabel = new QLabel(settingsGroupBox);
        iterationsLabel->setObjectName("iterationsLabel");

        horizontalLayout_9->addWidget(iterationsLabel);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_3);

        iterationsSpinBox = new QSpinBox(settingsGroupBox);
        iterationsSpinBox->setObjectName("iterationsSpinBox");
        iterationsSpinBox->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::UpDownArrows);
        iterationsSpinBox->setMaximum(100000);
        iterationsSpinBox->setValue(10000);

        horizontalLayout_9->addWidget(iterationsSpinBox);


        verticalLayout_2->addLayout(horizontalLayout_9);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        createPuzzlePushButton = new QPushButton(settingsGroupBox);
        createPuzzlePushButton->setObjectName("createPuzzlePushButton");

        verticalLayout_2->addWidget(createPuzzlePushButton);


        verticalLayout_3->addLayout(verticalLayout_2);


        horizontalLayout_2->addWidget(settingsGroupBox);

        puzzleGroupBox = new QGroupBox(centralwidget);
        puzzleGroupBox->setObjectName("puzzleGroupBox");
        verticalLayout_4 = new QVBoxLayout(puzzleGroupBox);
        verticalLayout_4->setObjectName("verticalLayout_4");
        puzzleWidget = new QWidget(puzzleGroupBox);
        puzzleWidget->setObjectName("puzzleWidget");
        verticalLayout_5 = new QVBoxLayout(puzzleWidget);
        verticalLayout_5->setObjectName("verticalLayout_5");
        puzzleGridLayout = new QGridLayout();
        puzzleGridLayout->setObjectName("puzzleGridLayout");

        verticalLayout_5->addLayout(puzzleGridLayout);


        verticalLayout_4->addWidget(puzzleWidget);


        horizontalLayout_2->addWidget(puzzleGroupBox);


        horizontalLayout_3->addLayout(horizontalLayout_2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1200, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        settingsGroupBox->setTitle(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        puzzleSizeLabel->setText(QCoreApplication::translate("MainWindow", "Puzzle Size", nullptr));
        puzzleStateLabel->setText(QCoreApplication::translate("MainWindow", "Puzzle State", nullptr));
        puzzleStateComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Default", nullptr));
        puzzleStateComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Solvable", nullptr));
        puzzleStateComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Unsolvable", nullptr));

        iterationsLabel->setText(QCoreApplication::translate("MainWindow", "Puzzle Iterations", nullptr));
        createPuzzlePushButton->setText(QCoreApplication::translate("MainWindow", "Create Puzzle", nullptr));
        puzzleGroupBox->setTitle(QCoreApplication::translate("MainWindow", "Puzzle", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
