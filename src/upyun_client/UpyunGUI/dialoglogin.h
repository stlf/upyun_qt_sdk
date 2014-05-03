#ifndef DIALOGLOGIN_H
#define DIALOGLOGIN_H

#include <QDialog>

namespace Ui {
class DialogLogin;
}

class DialogLogin : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLogin(QWidget *parent = 0);
    ~DialogLogin();

    static DialogLogin &get()
    {
        static DialogLogin dlg;
        return dlg;
    }

private slots:

    void on_pushButton_2_clicked();

public:
    QString bucket_;
    QString operator_;
    QString pass_;

private:
    Ui::DialogLogin *ui;
};

#endif // DIALOGLOGIN_H
