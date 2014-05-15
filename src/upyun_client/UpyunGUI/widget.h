#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QScopedPointer>


namespace Ui {
class Widget;
}
class QTreeWidgetItem;
class UpyunUser;
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void init();

    ~Widget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_2_clicked();

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

private:
    Ui::Widget *ui;

    QString _cur_dir;

    QScopedPointer<UpyunUser> _upy;

};

#endif // WIDGET_H
