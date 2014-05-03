#include <QMessageBox>
#include "dialoglogin.h"
#include "ui_dialoglogin.h"
#include "../upyun_client.h"
#include <QDebug>

DialogLogin::DialogLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLogin)
{
    ui->setupUi(this);
}

DialogLogin::~DialogLogin()
{
    delete ui;
}


void DialogLogin::on_pushButton_2_clicked()
{
    UpyunClient c(ui->lineEdit_2->text(), ui->lineEdit_3->text(), ui->lineEdit->text());
    try
    {
        c.getBucketUsage();

        bucket_ = ui->lineEdit->text();
        operator_ = ui->lineEdit_2->text();
        pass_ = ui->lineEdit_3->text();

        close();

    }
    catch(const QString &e)
    {
        QString msg("登录失败!");
        // msg += "\r\n" + e;
        QMessageBox::information(this, "提示", msg);
    }
}

