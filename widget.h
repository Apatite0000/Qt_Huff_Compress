#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include <QFileDialog>
#include "Huff_Zip.h"
#include <QMessageBox>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_choose_path_clicked();

    void on_file_compress_clicked();

    void on_file_decompress_clicked();

    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    QString ori_file_path;
};
#endif // WIDGET_H
