#include <QApplication>
#include "testserver.h"  // 文件名全小写

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    testserver server;  // 类名全小写
    server.setWindowTitle("测试服务器");
    server.resize(400, 300);
    server.show();

    return app.exec();
}
