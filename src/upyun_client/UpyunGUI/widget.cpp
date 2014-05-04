#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include "../upyun_client.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>

#include "dialoglogin.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget), _cur_dir("/")
{
    ui->setupUi(this);


    UpyunClient c(DialogLogin::get().operator_,
                  DialogLogin::get().pass_,
                  DialogLogin::get().bucket_);

    init();

    try{
        qDebug() << c.getBucketUsage(); // 8

        QString fn = "/hehe2.jpg";
        QString dir = "/lovey3/";

        // c.uploadFile("c:/1.jpg", fn); // 1

        foreach(upyun_file_info fi, c.listDir(_cur_dir)) // 2
        {
            qDebug() << fi.name << " " << fi.type << " " << fi.size << " " << fi.date;
        }

        qDebug() << c.downloadFile(fn).size(); // 3

        qDebug() << c.getFileInfo(fn).date; // 4
        c.removeFile(fn); // 5
        c.makeDir(dir); // 6
        c.removeDir(dir); // 7

    }
    catch(const QString &e)
    {
        qDebug() << "error:" + e;
    }
}

void Widget::init()
{
    try{
        UpyunClient c(DialogLogin::get().operator_,
                      DialogLogin::get().pass_,
                      DialogLogin::get().bucket_);
        ui->label->setText("已用空间:" + c.getBucketUsage());
        ui->treeWidget->clear();
        foreach(upyun_file_info fi, c.listDir("/"))
        {
            QStringList texts;

            texts << fi.name;
            if(fi.type == "N")
                texts << fi.size;
            else
                texts << "";
            texts << fi.date;
            QTreeWidgetItem * pitem = new QTreeWidgetItem(ui->treeWidget, texts);

            // load icon
            QIcon iconf;
            iconf.addPixmap(QPixmap(QString::fromUtf8(":/root/icons/folder.png")));
            QIcon icon;
            icon.addPixmap(QPixmap(QString::fromUtf8(":/root/icons/file.png")));

            if(fi.type == "N")
                pitem->setIcon(0,icon);
            if(fi.type == "F")
                pitem->setIcon(0,iconf);

        }
    }
    catch(...){}
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open file"), ".", tr("All Files(*.*)"));
    if(path.length() == 0) {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
    } else {
        QMessageBox::information(NULL, tr("Path"), tr("You selected ") + path);
    }
}

void Widget::on_pushButton_4_clicked()
{
    bool isOK;
    QString text = QInputDialog::getText(NULL, "提示","请输入文件夹名：",
                                         QLineEdit::Normal,
                                         "",
                                         &isOK);
    if(isOK)
    {
        UpyunClient c(DialogLogin::get().operator_,
                      DialogLogin::get().pass_,
                      DialogLogin::get().bucket_);

        try{
            c.makeDir(_cur_dir + QUrl::toPercentEncoding(text));
            init();
        }catch(const QString &e)
        {
            QMessageBox::information(this, "error", e);
        }
    }
}

void Widget::on_pushButton_5_clicked()
{
    UpyunClient c(DialogLogin::get().operator_,
                  DialogLogin::get().pass_,
                  DialogLogin::get().bucket_);

    QString  msg;
    if(ui->treeWidget->selectedItems().size() > 0)
    {
        const QTreeWidgetItem &ti = *ui->treeWidget->selectedItems()[0];
        msg = "确定删除 " + ti.text(0) + " 吗？";

        if(QMessageBox::No
                == QMessageBox::information(this, "提示", msg, QMessageBox::Yes | QMessageBox::No, QMessageBox::No))
            return;
        try{
            QString url = _cur_dir + ti.text(0);
            if("" == ti.text(1))
            { // fold
                c.removeDir(QUrl::toPercentEncoding(url));
            }
            else
            { // file
                c.removeFile(QUrl::toPercentEncoding(url));
            }

            init();
        }
        catch(const QString &e)
        {
            QMessageBox::information(this, "error", e);
        }
    }

}
