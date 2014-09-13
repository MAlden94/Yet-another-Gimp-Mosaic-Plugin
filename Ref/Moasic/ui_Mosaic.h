/********************************************************************************
** Form generated from reading UI file 'Mosaic.ui'
**
** Created: Fri Jun 20 09:30:39 2014
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOSAIC_H
#define UI_MOSAIC_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDockWidget>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
//#include "kurlrequester.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGraphicsView *graphicsView;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;
    QDockWidget *dockWidget_3;
    QWidget *dockWidgetContents_3;
    QVBoxLayout *_2;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    KUrlComboRequester *kurlcomborequester_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    KUrlComboRequester *kurlcomborequester_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    KUrlComboRequester *kurlcomborequester;
    QGridLayout *gridLayout_2;
    QComboBox *comboBox_3;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBox;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_6;
    QComboBox *comboBox_2;
    QLabel *label_7;
    QCheckBox *checkBox;
    QSlider *horizontalSlider;
    QGridLayout *gridLayout_3;
    QLabel *label_8;
    QLabel *label_9;
    QSpinBox *spinBox_2;
    QSpinBox *spinBox;
    QPushButton *pushButton;
    QProgressBar *progressBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QHBoxLayout *horizontalLayout_3;
    QListWidget *listWidget;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(905, 681);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        verticalLayout->addWidget(graphicsView);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 905, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        dockWidget_3 = new QDockWidget(MainWindow);
        dockWidget_3->setObjectName(QString::fromUtf8("dockWidget_3"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(8);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dockWidget_3->sizePolicy().hasHeightForWidth());
        dockWidget_3->setSizePolicy(sizePolicy);
        dockWidget_3->setBaseSize(QSize(90, 0));
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QString::fromUtf8("dockWidgetContents_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(dockWidgetContents_3->sizePolicy().hasHeightForWidth());
        dockWidgetContents_3->setSizePolicy(sizePolicy1);
        _2 = new QVBoxLayout(dockWidgetContents_3);
        _2->setObjectName(QString::fromUtf8("_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout->setContentsMargins(-1, 0, -1, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, 0, -1, -1);
        label_5 = new QLabel(dockWidgetContents_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_4->addWidget(label_5);

        kurlcomborequester_2 = new KUrlComboRequester(dockWidgetContents_3);
        kurlcomborequester_2->setObjectName(QString::fromUtf8("kurlcomborequester_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(kurlcomborequester_2->sizePolicy().hasHeightForWidth());
        kurlcomborequester_2->setSizePolicy(sizePolicy2);
        kurlcomborequester_2->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_4->addWidget(kurlcomborequester_2, 0, Qt::AlignRight);


        gridLayout->addLayout(horizontalLayout_4, 8, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, 0, -1, -1);
        label_3 = new QLabel(dockWidgetContents_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_5->addWidget(label_3);

        kurlcomborequester_3 = new KUrlComboRequester(dockWidgetContents_3);
        kurlcomborequester_3->setObjectName(QString::fromUtf8("kurlcomborequester_3"));
        sizePolicy2.setHeightForWidth(kurlcomborequester_3->sizePolicy().hasHeightForWidth());
        kurlcomborequester_3->setSizePolicy(sizePolicy2);
        kurlcomborequester_3->setMaximumSize(QSize(16777215, 16777215));
        kurlcomborequester_3->setMode(KFile::Directory|KFile::ExistingOnly|KFile::LocalOnly);

        horizontalLayout_5->addWidget(kurlcomborequester_3, 0, Qt::AlignRight);


        gridLayout->addLayout(horizontalLayout_5, 14, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, -1, -1);
        label_4 = new QLabel(dockWidgetContents_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_4->setMargin(0);
        label_4->setIndent(0);
        label_4->setOpenExternalLinks(false);

        horizontalLayout_2->addWidget(label_4);

        kurlcomborequester = new KUrlComboRequester(dockWidgetContents_3);
        kurlcomborequester->setObjectName(QString::fromUtf8("kurlcomborequester"));
        sizePolicy2.setHeightForWidth(kurlcomborequester->sizePolicy().hasHeightForWidth());
        kurlcomborequester->setSizePolicy(sizePolicy2);
        kurlcomborequester->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_2->addWidget(kurlcomborequester, 0, Qt::AlignRight);


        gridLayout->addLayout(horizontalLayout_2, 3, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(-1, 0, -1, 0);
        comboBox_3 = new QComboBox(dockWidgetContents_3);
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));

        gridLayout_2->addWidget(comboBox_3, 4, 1, 1, 1);

        label_2 = new QLabel(dockWidgetContents_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 2, 0, 1, 1);

        doubleSpinBox = new QDoubleSpinBox(dockWidgetContents_3);
        doubleSpinBox->setObjectName(QString::fromUtf8("doubleSpinBox"));

        gridLayout_2->addWidget(doubleSpinBox, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 1, 1, 1);

        label = new QLabel(dockWidgetContents_3);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        comboBox = new QComboBox(dockWidgetContents_3);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
#ifndef QT_NO_ACCESSIBILITY
        comboBox->setAccessibleName(QString::fromUtf8(""));
#endif // QT_NO_ACCESSIBILITY
        comboBox->setEditable(false);
        comboBox->setModelColumn(0);

        gridLayout_2->addWidget(comboBox, 2, 1, 1, 1);

        label_6 = new QLabel(dockWidgetContents_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 4, 0, 1, 1);

        comboBox_2 = new QComboBox(dockWidgetContents_3);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

        gridLayout_2->addWidget(comboBox_2, 3, 1, 1, 1);

        label_7 = new QLabel(dockWidgetContents_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 3, 0, 1, 1);

        checkBox = new QCheckBox(dockWidgetContents_3);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        gridLayout_2->addWidget(checkBox, 5, 1, 1, 1);

        horizontalSlider = new QSlider(dockWidgetContents_3);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(horizontalSlider, 1, 1, 1, 1);


        gridLayout->addLayout(gridLayout_2, 16, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(-1, -1, -1, 0);
        label_8 = new QLabel(dockWidgetContents_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_3->addWidget(label_8, 2, 0, 1, 1);

        label_9 = new QLabel(dockWidgetContents_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_3->addWidget(label_9, 3, 0, 1, 1);

        spinBox_2 = new QSpinBox(dockWidgetContents_3);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));

        gridLayout_3->addWidget(spinBox_2, 2, 1, 1, 1);

        spinBox = new QSpinBox(dockWidgetContents_3);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setInputMethodHints(Qt::ImhNone);

        gridLayout_3->addWidget(spinBox, 3, 1, 1, 1);


        gridLayout->addLayout(gridLayout_3, 18, 0, 1, 1);


        _2->addLayout(gridLayout);

        pushButton = new QPushButton(dockWidgetContents_3);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        _2->addWidget(pushButton);

        progressBar = new QProgressBar(dockWidgetContents_3);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(24);

        _2->addWidget(progressBar);

        dockWidget_3->setWidget(dockWidgetContents_3);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget_3);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(dockWidget->sizePolicy().hasHeightForWidth());
        dockWidget->setSizePolicy(sizePolicy3);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        horizontalLayout_3 = new QHBoxLayout(dockWidgetContents);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        listWidget = new QListWidget(dockWidgetContents);
        new QListWidgetItem(listWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy4);

        horizontalLayout_3->addWidget(listWidget);

        dockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget);

        menubar->addAction(menuFile->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "Output: ", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Thumbnails: ", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "Input: ", 0, QApplication::UnicodeUTF8));
        comboBox_3->clear();
        comboBox_3->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Random", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Ignore", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "A-Z", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Z-A", 0, QApplication::UnicodeUTF8)
        );
        label_2->setText(QApplication::translate("MainWindow", "Metric: ", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Threshold:", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Euclidean", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Max", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Manhattan", 0, QApplication::UnicodeUTF8)
        );
        label_6->setText(QApplication::translate("MainWindow", "Sort:", 0, QApplication::UnicodeUTF8));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Normal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Scale", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Adaptive", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Crop", 0, QApplication::UnicodeUTF8)
        );
        label_7->setText(QApplication::translate("MainWindow", "Resize:", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("MainWindow", "Make thumbnails unique", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "Canvas size: ", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "Thumbnail: ", 0, QApplication::UnicodeUTF8));
        spinBox->setSpecialValueText(QString());
        pushButton->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("MainWindow", "DDDD", 0, QApplication::UnicodeUTF8));
        listWidget->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOSAIC_H
