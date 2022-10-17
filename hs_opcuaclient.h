#ifndef HS_OPCUACLIENT_H
#define HS_OPCUACLIENT_H

#include <QWidget>
#include <QtOpcUa>

//服务器类，构造函数为连接到指定地址服务器。
namespace Ui {
class Hs_OpcUAClient;
}

class Hs_OpcUAClient : public QWidget
{
    Q_OBJECT

public:
    explicit Hs_OpcUAClient(QString url,QWidget *parent = nullptr);
    ~Hs_OpcUAClient();

public slots:

    void SLOT_endpointsRequestFinished (QVector<QOpcUa::QEndpointDescription> endpoints , QOpcUa::UaStatusCode statusCode);
    void SLOT_stateChanged (QOpcUaClient::ClientState state );

signals:
    void send_connect_status(QString);

public:
    Ui::Hs_OpcUAClient *ui;
    QString         m_sUrl;         //机台地址
    QOpcUaProvider  *m_provider;    //初始化客户端中间量
    QOpcUaClient    *m_client;      //访问者作为客户端
    QOpcUaNode      *m_node;

};

#endif // HS_OPCUACLIENT_H
