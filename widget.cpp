#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("title.png"));
    ori_file_path = "";
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_choose_path_clicked()
{
    ori_file_path = QFileDialog::getOpenFileName(NULL,"文件路径选择","C:/Users/Alan/Desktop","");
    ui->file_path->setText(ori_file_path);
}

void Widget::on_file_compress_clicked()
{
    if(ori_file_path.toStdString()=="")
    {
        QMessageBox::information(NULL, "info", "路径为空");
        return;
    }
    Huff_Zip compress_file(ori_file_path.toStdString(),1);
    QString info = "压缩完成，压缩比为" + QString::number(compress_file.get_ratio()*100,'d',2) + '%';
    QMessageBox::information(NULL, "info", info);
}

void Widget::on_file_decompress_clicked()
{
    if(ori_file_path.toStdString()=="")
    {
        QMessageBox::information(NULL, "info", "路径为空");
        return;
    }
    Huff_Zip decompress_file(ori_file_path.toStdString(),0);
    QString info = "解压完成，压缩比为" + QString::number(decompress_file.get_ratio()*100,'d',2) + '%';
    QMessageBox::information(NULL, "info", info);
    if(decompress_file.is_decompress_same())
    {
        QMessageBox::information(NULL, "相同性比对", "根据MD5比对，压缩文件与原文件相等，MD5值均为\n"+ QString::fromStdString(decompress_file.get_md5()));
    }
    else
    {
        QMessageBox::information(NULL, "相同性比对", "根据MD5比对，压缩文件与原文件不同\n请检查文件是否为.huffzip格式或文件是否受损");
    }
}

void Widget::on_pushButton_clicked()
{
    QMessageBox a;
    a.setWindowTitle("About");
    a.setIcon(QMessageBox::Information);
    a.setText("哈夫曼树压缩.exe\n当前版本  0.1 Beta\n生成文件和原文件同目录\npowered by Alan at HFUT 2021/6/4");
    a.exec();
}
