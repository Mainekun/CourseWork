/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *ManagementBox;
    QPushButton *AddBtn;
    QPushButton *RemoveBtn;
    QPushButton *OpenBtn;
    QPushButton *SaveBtn;
    QListView *VectorView;
    QLineEdit *VectorPreview;
    QPushButton *SaveChangesBtn;
    QTabWidget *FuncTabBox;
    QWidget *CalcTab;
    QTextEdit *SentanceField;
    QPushButton *SolveBtn;
    QTextEdit *ResultField;
    QPushButton *SaveResultBtn;
    QWidget *UtilityTab;
    QComboBox *OperandBox;
    QTextEdit *ResultLine;
    QPushButton *MaxIndexesBtn;
    QPushButton *MinIndexesBtn;
    QWidget *tab;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setEnabled(true);
        MainWindow->resize(402, 523);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(402, 523));
        MainWindow->setMaximumSize(QSize(402, 523));
        MainWindow->setAcceptDrops(false);
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::DriveOptical));
        MainWindow->setWindowIcon(icon);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonIconOnly);
        MainWindow->setTabShape(QTabWidget::TabShape::Rounded);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        ManagementBox = new QGroupBox(centralwidget);
        ManagementBox->setObjectName("ManagementBox");
        ManagementBox->setGeometry(QRect(10, 10, 381, 291));
        AddBtn = new QPushButton(ManagementBox);
        AddBtn->setObjectName("AddBtn");
        AddBtn->setGeometry(QRect(285, 60, 90, 24));
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::ListAdd));
        AddBtn->setIcon(icon1);
        RemoveBtn = new QPushButton(ManagementBox);
        RemoveBtn->setObjectName("RemoveBtn");
        RemoveBtn->setGeometry(QRect(285, 90, 90, 24));
        QIcon icon2(QIcon::fromTheme(QIcon::ThemeIcon::ListRemove));
        RemoveBtn->setIcon(icon2);
        OpenBtn = new QPushButton(ManagementBox);
        OpenBtn->setObjectName("OpenBtn");
        OpenBtn->setGeometry(QRect(285, 120, 90, 24));
        QIcon icon3(QIcon::fromTheme(QIcon::ThemeIcon::DocumentOpen));
        OpenBtn->setIcon(icon3);
        SaveBtn = new QPushButton(ManagementBox);
        SaveBtn->setObjectName("SaveBtn");
        SaveBtn->setGeometry(QRect(285, 150, 90, 24));
        QIcon icon4(QIcon::fromTheme(QIcon::ThemeIcon::DocumentSave));
        SaveBtn->setIcon(icon4);
        VectorView = new QListView(ManagementBox);
        VectorView->setObjectName("VectorView");
        VectorView->setGeometry(QRect(10, 60, 270, 220));
        VectorPreview = new QLineEdit(ManagementBox);
        VectorPreview->setObjectName("VectorPreview");
        VectorPreview->setGeometry(QRect(10, 30, 271, 24));
        SaveChangesBtn = new QPushButton(ManagementBox);
        SaveChangesBtn->setObjectName("SaveChangesBtn");
        SaveChangesBtn->setGeometry(QRect(285, 30, 90, 24));
        QIcon icon5(QIcon::fromTheme(QIcon::ThemeIcon::MailMessageNew));
        SaveChangesBtn->setIcon(icon5);
        SaveChangesBtn->setCheckable(false);
        SaveChangesBtn->setChecked(false);
        SaveChangesBtn->setAutoRepeat(false);
        SaveChangesBtn->setAutoExclusive(false);
        FuncTabBox = new QTabWidget(centralwidget);
        FuncTabBox->setObjectName("FuncTabBox");
        FuncTabBox->setGeometry(QRect(10, 310, 381, 161));
        FuncTabBox->setElideMode(Qt::TextElideMode::ElideNone);
        FuncTabBox->setMovable(false);
        FuncTabBox->setTabBarAutoHide(false);
        CalcTab = new QWidget();
        CalcTab->setObjectName("CalcTab");
        SentanceField = new QTextEdit(CalcTab);
        SentanceField->setObjectName("SentanceField");
        SentanceField->setGeometry(QRect(10, 10, 281, 31));
        SolveBtn = new QPushButton(CalcTab);
        SolveBtn->setObjectName("SolveBtn");
        SolveBtn->setGeometry(QRect(300, 10, 71, 30));
        ResultField = new QTextEdit(CalcTab);
        ResultField->setObjectName("ResultField");
        ResultField->setGeometry(QRect(10, 50, 281, 70));
        SaveResultBtn = new QPushButton(CalcTab);
        SaveResultBtn->setObjectName("SaveResultBtn");
        SaveResultBtn->setGeometry(QRect(300, 50, 70, 70));
        FuncTabBox->addTab(CalcTab, QString());
        FuncTabBox->setTabText(FuncTabBox->indexOf(CalcTab), QString::fromUtf8("\320\232\320\260\320\273\321\214\320\272\321\203\320\273\321\217\321\202\320\276\321\200"));
        UtilityTab = new QWidget();
        UtilityTab->setObjectName("UtilityTab");
        OperandBox = new QComboBox(UtilityTab);
        OperandBox->setObjectName("OperandBox");
        OperandBox->setGeometry(QRect(10, 10, 110, 30));
        ResultLine = new QTextEdit(UtilityTab);
        ResultLine->setObjectName("ResultLine");
        ResultLine->setGeometry(QRect(10, 50, 351, 70));
        MaxIndexesBtn = new QPushButton(UtilityTab);
        MaxIndexesBtn->setObjectName("MaxIndexesBtn");
        MaxIndexesBtn->setGeometry(QRect(130, 10, 110, 30));
        MinIndexesBtn = new QPushButton(UtilityTab);
        MinIndexesBtn->setObjectName("MinIndexesBtn");
        MinIndexesBtn->setGeometry(QRect(250, 10, 110, 30));
        FuncTabBox->addTab(UtilityTab, QString());
        tab = new QWidget();
        tab->setObjectName("tab");
        pushButton = new QPushButton(tab);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(10, 10, 360, 120));
        FuncTabBox->addTab(tab, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 402, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        sizePolicy.setHeightForWidth(statusbar->sizePolicy().hasHeightForWidth());
        statusbar->setSizePolicy(sizePolicy);
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        FuncTabBox->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\222\320\265\320\272\321\202\320\276\321\200\320\275\321\213\320\271 \320\272\320\260\320\273\321\214\320\272\321\203\320\273\321\217\321\202\320\276\321\200", nullptr));
        ManagementBox->setTitle(QCoreApplication::translate("MainWindow", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\262\320\265\320\272\321\202\320\276\321\200\320\260\320\274\320\270", nullptr));
        AddBtn->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        RemoveBtn->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        OpenBtn->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", nullptr));
        SaveBtn->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        SaveChangesBtn->setText(QCoreApplication::translate("MainWindow", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        SolveBtn->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\321\210\320\270\321\202\321\214", nullptr));
        SaveResultBtn->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214\n"
" \321\200\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202", nullptr));
        MaxIndexesBtn->setText(QCoreApplication::translate("MainWindow", "\320\230\320\275\320\264\320\265\320\272\321\201\321\213 \320\274\320\260\320\272\321\201.", nullptr));
        MinIndexesBtn->setText(QCoreApplication::translate("MainWindow", "\320\230\320\275\320\264\320\265\320\272\321\201\321\213 \320\274\320\270\320\275.", nullptr));
        FuncTabBox->setTabText(FuncTabBox->indexOf(UtilityTab), QCoreApplication::translate("MainWindow", "\320\240\320\260\320\267\320\275\320\276\320\265", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\277\321\200\320\260\320\262\320\272\320\260", nullptr));
        FuncTabBox->setTabText(FuncTabBox->indexOf(tab), QCoreApplication::translate("MainWindow", "\320\236\320\277\320\265\321\200\320\260\321\206\320\270\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
