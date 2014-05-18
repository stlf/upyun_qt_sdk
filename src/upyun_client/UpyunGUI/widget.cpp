#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include "../upyun_client.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QDesktopServices>
#include <QDateTime>

#include "dialoglogin.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget), _cur_dir("/"),_upy(new UpyunUser(DialogLogin::get().operator_,
                                                         DialogLogin::get().pass_,
                                                         DialogLogin::get().bucket_))
{
    ui->setupUi(this);
    init();
}

#define PARENT_DIR "上一目录.."
void Widget::init()
{
    try{

        UpyunUser &c = *_upy;
        ui->label_2->setText("当前目录:" + c.pwd());
        ui->label->setText("已用空间:" + QString::number(c.getBucketUsage().toInt() / 1000000.0f) + " MB");
        ui->treeWidget->clear();

        if(c.pwd() != "/")
        {
            QStringList sl; sl << PARENT_DIR;
            QTreeWidgetItem * pitem = new QTreeWidgetItem(ui->treeWidget, sl);
        }

        foreach(upyun_file_info fi, c.listDir())
        {
            QStringList texts;

            texts << fi.name;
            if(fi.type == "N")
                texts << fi.size;
            else
                texts << "";

            texts << QDateTime::fromTime_t(fi.date.toUInt()).toString();
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
    if(path.length() == 0)
        return;

    UpyunUser &c = *_upy;
    const QStringList &sl = path.split("/");
    if(sl.size())
    {
        QString fn = sl[sl.size() - 1];
        try
        {
            c.uploadFile(path);

            init();
        }
        catch(const QString &e)
        {
            QMessageBox::information(this, "error", e);
        }

    }

}

void Widget::on_pushButton_4_clicked()
{
    bool isOK;
    QString text = QInputDialog::getText(NULL, "提示","请输入文件夹名：",
                                         QLineEdit::Normal,
                                         "",
                                         &isOK);
    if(!isOK)
        return;

    UpyunUser &c = *_upy;

    try
    {
        c.makeDir(text);
        init();
    }
    catch(const QString &e)
    {
        QMessageBox::information(this, "error", e);
    }

}

void Widget::on_pushButton_5_clicked()
{
    UpyunUser &c = *_upy;
    QString  msg;
    if(ui->treeWidget->selectedItems().size() > 0)
    {
        const QTreeWidgetItem &ti = *ui->treeWidget->selectedItems()[0];
        msg = "确定删除 " + ti.text(0) + " 吗？";

        if(QMessageBox::No
                == QMessageBox::information(this, "提示", msg, QMessageBox::Yes | QMessageBox::No, QMessageBox::No))
            return;
        try{
            if("" == ti.text(1))
            { // fold
                c.removeDir(ti.text(0));
            }
            else
            { // file
                c.removeFile(ti.text(0));
            }

            init();
        }
        catch(const QString &e)
        {
            QMessageBox::information(this, "error", e);
        }
    }

}

void Widget::on_pushButton_2_clicked()
{
    if(ui->treeWidget->selectedItems().size() <= 0)
        return;
    const QTreeWidgetItem &ti = *ui->treeWidget->selectedItems()[0];
    const QString &fn = ti.text(0);

    UpyunUser &c = *_upy;
    try
    {
        const QByteArray &buf = c.downloadFile(fn);
        const QString &path = QFileDialog::getExistingDirectory(this, tr("Open dir"));

        const QString &fp = path + "/" + fn;
        QFile f(fp);
        if(!f.open(QIODevice::WriteOnly))
            throw QString("open " + fn + " error!");
        f.write(buf);


        if(QMessageBox::Yes
                == QMessageBox::information(this, "提示", "下载成功,现在就查看吗?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No))
        {
            QDesktopServices::openUrl(QUrl::fromLocalFile(fp));
        }

    }
    catch(const QString &e)
    {
        QMessageBox::information(this, "error", e);
    }

}

void Widget::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if(PARENT_DIR == item->text(0))
    {
        _upy->gotoParentDir();
        init();
        return;
    }
    if( "" == item->text(1))
    {
      _upy->cd(item->text(0));
      init();
    }
}
