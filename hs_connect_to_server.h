#ifndef HS_CONNECT_TO_SERVER_H
#define HS_CONNECT_TO_SERVER_H

#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>
#include <QLayout>
#include <QtOpcUa>
#include "Hs_OpcUAClient.h"

//连接服务器类，初始化一个服务器类Hs_OpcUAClient对象，根据输入框输入地址，点击连接设备后触发信号。
//自定义信号为发送当前创建的服务器，在Hs_analyse中接受该服务器
namespace Ui {
class Hs_connect_to_server;
}

class Hs_connect_to_server : public QWidget
{
    Q_OBJECT

public:
    explicit Hs_connect_to_server(QWidget *parent = nullptr);
    ~Hs_connect_to_server();
    void initialize();
    void initializeslots();

private:
    Ui::Hs_connect_to_server *ui;
    QPushButton *m_connect_button;
    QLineEdit *m_server_address_input;
    QString *m_serverURL;
    QLabel *m_Label1;
    Hs_OpcUAClient *m_client;

signals:
    void sendclient(Hs_OpcUAClient*);
    void sendstatus(QString);

private slots:
    void on_connect_button_clicked();
    void receive_connect_status(QString);
};

#endif // HS_CONNECT_TO_SERVER_H
