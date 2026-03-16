/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *quickViewContainer;
    QLabel *rightTriggerDriftLabel;
    QLabel *leftTriggerDriftLabel;
    QLabel *leftStickDriftLabel;
    QLabel *rightStickDriftLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        quickViewContainer = new QWidget(centralwidget);
        quickViewContainer->setObjectName("quickViewContainer");
        quickViewContainer->setGeometry(QRect(20, 0, 751, 471));
        rightTriggerDriftLabel = new QLabel(centralwidget);
        rightTriggerDriftLabel->setObjectName("rightTriggerDriftLabel");
        rightTriggerDriftLabel->setGeometry(QRect(200, 470, 191, 71));
        QFont font;
        font.setPointSize(15);
        rightTriggerDriftLabel->setFont(font);
        rightTriggerDriftLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        rightTriggerDriftLabel->setWordWrap(true);
        leftTriggerDriftLabel = new QLabel(centralwidget);
        leftTriggerDriftLabel->setObjectName("leftTriggerDriftLabel");
        leftTriggerDriftLabel->setGeometry(QRect(20, 470, 181, 71));
        leftTriggerDriftLabel->setFont(font);
        leftTriggerDriftLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        leftTriggerDriftLabel->setWordWrap(true);
        leftStickDriftLabel = new QLabel(centralwidget);
        leftStickDriftLabel->setObjectName("leftStickDriftLabel");
        leftStickDriftLabel->setGeometry(QRect(390, 470, 191, 71));
        leftStickDriftLabel->setFont(font);
        leftStickDriftLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        leftStickDriftLabel->setWordWrap(true);
        rightStickDriftLabel = new QLabel(centralwidget);
        rightStickDriftLabel->setObjectName("rightStickDriftLabel");
        rightStickDriftLabel->setGeometry(QRect(580, 470, 191, 71));
        rightStickDriftLabel->setFont(font);
        rightStickDriftLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        rightStickDriftLabel->setWordWrap(true);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 26));
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
        rightTriggerDriftLabel->setText(QCoreApplication::translate("MainWindow", "Possible right trigger drift", nullptr));
        leftTriggerDriftLabel->setText(QCoreApplication::translate("MainWindow", "Possible left trigger drift", nullptr));
        leftStickDriftLabel->setText(QCoreApplication::translate("MainWindow", "Possible left stick drift", nullptr));
        rightStickDriftLabel->setText(QCoreApplication::translate("MainWindow", "Possible right stick drift", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
