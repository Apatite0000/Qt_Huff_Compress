/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *choose_path;
    QPushButton *file_compress;
    QPushButton *file_decompress;
    QLabel *file_path;
    QPushButton *pushButton;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(450, 100);
        Widget->setMinimumSize(QSize(450, 100));
        Widget->setMaximumSize(QSize(450, 100));
        choose_path = new QPushButton(Widget);
        choose_path->setObjectName(QString::fromUtf8("choose_path"));
        choose_path->setGeometry(QRect(300, 10, 100, 30));
        file_compress = new QPushButton(Widget);
        file_compress->setObjectName(QString::fromUtf8("file_compress"));
        file_compress->setGeometry(QRect(10, 50, 80, 30));
        file_decompress = new QPushButton(Widget);
        file_decompress->setObjectName(QString::fromUtf8("file_decompress"));
        file_decompress->setGeometry(QRect(190, 50, 80, 30));
        file_path = new QLabel(Widget);
        file_path->setObjectName(QString::fromUtf8("file_path"));
        file_path->setGeometry(QRect(10, 10, 221, 21));
        pushButton = new QPushButton(Widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(390, 60, 50, 20));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Huffman Compress", nullptr));
        choose_path->setText(QCoreApplication::translate("Widget", "\351\200\211\346\213\251\346\226\207\344\273\266\350\267\257\345\276\204", nullptr));
        file_compress->setText(QCoreApplication::translate("Widget", "\345\216\213\347\274\251\346\226\207\344\273\266", nullptr));
        file_decompress->setText(QCoreApplication::translate("Widget", "\350\247\243\345\216\213\346\226\207\344\273\266", nullptr));
        file_path->setText(QCoreApplication::translate("Widget", "Please choose a file", nullptr));
        pushButton->setText(QCoreApplication::translate("Widget", "About", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
