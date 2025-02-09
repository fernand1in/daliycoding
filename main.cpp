#include "demo4.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("校园导航");
    w.show();
    return a.exec();
}
