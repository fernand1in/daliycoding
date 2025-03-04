#include <QApplication>
#include "client.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    client c;
    c.setWindowTitle("客户端");
    c.resize(400, 300);
    c.show();

    return app.exec();
}
