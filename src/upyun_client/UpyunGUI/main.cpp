#include "widget.h"
#include <QApplication>
#include "dialoglogin.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DialogLogin::get().exec();

    Widget w;
    w.show();

    return a.exec();
}
