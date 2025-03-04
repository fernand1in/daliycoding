#include "client.h"
#include "ui_client.h"

client::client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::client)
    , tcpSocket(new QTcpSocket(this))
{
    ui->setupUi(this);

    // 设置默认文本
    ui->hostLineEdit->setText("127.0.0.1");
    ui->portLineEdit->setText("2456");

    // 设置占位符文本
    ui->hostLineEdit->setPlaceholderText("请输入服务器地址");
    ui->portLineEdit->setPlaceholderText("请输入端口号");

    // 连接信号和槽
    connect(ui->connectButton, &QPushButton::clicked, this, &client::on_connectButton_clicked);
    connect(ui->sendButton, &QPushButton::clicked, this, &client::on_sendButton_clicked);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &client::on_readyRead);
}

client::~client()
{
    delete ui;
}

void client::on_connectButton_clicked()
{
    QString host = ui->hostLineEdit->text();
    quint16 port = ui->portLineEdit->text().toUInt();
    tcpSocket->connectToHost(host, port);

    if (tcpSocket->waitForConnected(3000))
    {
        qDebug() << "连接成功";
    }
    else
    {
        qDebug() << "连接失败：" << tcpSocket->errorString();
    }
}

void client::on_sendButton_clicked()
{
    QString message = ui->messageLineEdit->text();
    tcpSocket->write(message.toUtf8());
}

void client::on_readyRead()
{
    QByteArray data = tcpSocket->readAll();
    qDebug() << "收到服务器数据：" << data;
}
