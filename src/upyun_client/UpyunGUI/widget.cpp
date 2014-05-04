#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include "../upyun_client.h"
#include <QFileDialog>
#include <QMessageBox>

#include "dialoglogin.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
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

        foreach(upyun_file_info fi, c.listDir("/")) // 2
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
