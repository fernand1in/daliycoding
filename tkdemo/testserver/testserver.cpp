#include "testserver.h"
#include "ui_testserver.h"  // 自动生成的UI头文件，文件名全小写

testserver::testserver(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::testserver)  // 初始化UI对象，类名全小写
    , tcpServer(new QTcpServer(this))  // 初始化TCP服务器
    , isListening(false)  // 初始化监听状态
{
    ui->setupUi(this);  // 设置UI

    // 设置按钮文本
    ui->startServer->setText("启动服务器");
    ui->stopServer->setText("关闭服务器");
    ui->stopServer->setEnabled(false);  // 初始时关闭按钮不可用

    // 连接按钮的点击信号到槽函数
    connect(ui->startServer, &QPushButton::clicked, this, &testserver::on_startServer_clicked);
    connect(ui->stopServer, &QPushButton::clicked, this, &testserver::on_stopServer_clicked);

    // 连接新连接信号
    connect(tcpServer, &QTcpServer::newConnection, this, &testserver::on_newConnection);
}

testserver::~testserver()
{
    if (tcpServer->isListening())
    {
        tcpServer->close();  // 确保服务器关闭
    }
    delete ui;
}

void testserver::on_startServer_clicked()
{
    if (!isListening)
    {
        quint16 port = 2456;  // 设置监听端口
        if (tcpServer->listen(QHostAddress::Any, port))
        {
            qDebug() << "服务器已启动，监听端口：" << port;
            qDebug() << "监听地址：" << tcpServer->serverAddress().toString();
            qDebug() << "监听端口：" << tcpServer->serverPort();
            ui->startServer->setEnabled(false);
            ui->stopServer->setEnabled(true);
            isListening = true;
        }
        else
        {
            qDebug() << "启动失败：" << tcpServer->errorString();
        }
    }
}

void testserver::on_stopServer_clicked()
{
    if (isListening)
    {
        tcpServer->close();
        qDebug() << "服务器已关闭";
        ui->startServer->setEnabled(true);
        ui->stopServer->setEnabled(false);
        isListening = false;
    }
}

void testserver::on_newConnection() {
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, this, &testserver::on_clientReadyRead);
    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
    // 将clientSocket存入容器（如QList）以便管理
}
void testserver::on_clientReadyRead() {
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    QByteArray data = socket->readAll();
    qDebug() << "收到数据：" << data;
    // 处理数据并回复（示例：回显）
    socket->write("服务器已收到：" + data);
}
