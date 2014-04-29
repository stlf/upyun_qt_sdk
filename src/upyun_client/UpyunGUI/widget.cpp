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
        // c.uploadFile("c:/1.jpg", "hehe.jpg");

        foreach(upyun_file_info fi, c.listDir("/"))
        {
            qDebug() << fi.name << " " << fi.type << " " << fi.size << " " << fi.last_modify_date;
        }

        qDebug() << c.downloadFile("hehe.jpg").size();

        c.makeDir("ilovey/");
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
