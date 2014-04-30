#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

#include "../upyun_client.h"

#define BUCKET "stlf-first-bucket"
#define OPERATOR ""
#define PASS ""

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);


    UpyunClient c(OPERATOR,PASS, BUCKET);

    try{
        QString fn = "/hehe2.jpg";
        QString dir = "/lovey3/";

        c.uploadFile("c:/1.jpg", fn); // 1

        foreach(upyun_file_info fi, c.listDir("/")) // 2
        {
            qDebug() << fi.name << " " << fi.type << " " << fi.size << " " << fi.date;
        }

        qDebug() << c.downloadFile(fn).size(); // 3

        qDebug() << c.getFileInfo(fn).date; // 4
        c.removeFile(fn); // 5
        c.makeDir(dir); // 6
        c.removeDir(dir); // 7

        qDebug() << c.getBucketUsage(); // 8
    }
    catch(const QString &e)
    {
        qDebug() << "error:" + e;
    }
}

Widget::~Widget()
{
    delete ui;
}
