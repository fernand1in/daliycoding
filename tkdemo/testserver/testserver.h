#ifndef TESTSERVER_H
#define TESTSERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class testserver; }  // 类名全小写
QT_END_NAMESPACE

class testserver : public QMainWindow  // 类名全小写
{
    Q_OBJECT

public:
    testserver(QWidget *parent = nullptr);  // 构造函数
    ~testserver();  // 析构函数

private slots:
    void on_startServer_clicked();  // 启动服务器
    void on_stopServer_clicked();   // 关闭服务器
    void on_newConnection();        // 处理新连接
    void on_clientReadyRead(); // 接收客户端数据
private:
    Ui::testserver *ui;             // UI对象，类名全小写
    QTcpServer *tcpServer;          // 用于监听客户端连接
    bool isListening;               // 标记服务器是否正在监听
};

#endif // TESTSERVER_H
