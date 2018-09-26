/********************************************************************************
** Form generated from reading UI file 'codesample.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CODESAMPLE_H
#define UI_CODESAMPLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CodeSampleClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CodeSampleClass)
    {
        if (CodeSampleClass->objectName().isEmpty())
            CodeSampleClass->setObjectName(QStringLiteral("CodeSampleClass"));
        CodeSampleClass->resize(600, 400);
        menuBar = new QMenuBar(CodeSampleClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        CodeSampleClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CodeSampleClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CodeSampleClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(CodeSampleClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        CodeSampleClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(CodeSampleClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CodeSampleClass->setStatusBar(statusBar);

        retranslateUi(CodeSampleClass);

        QMetaObject::connectSlotsByName(CodeSampleClass);
    } // setupUi

    void retranslateUi(QMainWindow *CodeSampleClass)
    {
        CodeSampleClass->setWindowTitle(QApplication::translate("CodeSampleClass", "CodeSample", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CodeSampleClass: public Ui_CodeSampleClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CODESAMPLE_H
