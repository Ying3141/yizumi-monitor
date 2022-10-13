#include "hs_opcuaclient.h"
#include "ui_hs_opcuaclient.h"

Hs_OpcUAClient::Hs_OpcUAClient(QString url,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hs_OpcUAClient)
{
    ui->setupUi(this);

    m_sUrl=url;

    //官方文档初始化方法：实例QOpcUaProvider，再实例QOpcUaClient
    m_provider = new QOpcUaProvider(this);
    m_client = m_provider->createClient(QString("open62541"));
    //获取根节点信号，必要性未知
    connect(m_client,&QOpcUaClient::endpointsRequestFinished,this,&Hs_OpcUAClient::SLOT_endpointsRequestFinished);
    //连接状态改变信号，非必要
    connect(m_client,&QOpcUaClient::stateChanged,this,&Hs_OpcUAClient::SLOT_stateChanged);
    //根据机台地址连接，获取根节点
    m_client->requestEndpoints(QUrl(m_sUrl));
}

Hs_OpcUAClient::~Hs_OpcUAClient()
{
    delete ui;
}

void Hs_OpcUAClient::SLOT_endpointsRequestFinished(QVector<QOpcUa::QEndpointDescription> endpoints, QOpcUa::UaStatusCode statusCode)
{
    qDebug()<<endpoints.at(0).endpointUrl();
    qDebug()<<statusCode;
    qDebug() << "Endpoints returned:" << endpoints.count();
    qDebug()<<endpoints.size();
    if (endpoints.size())
        m_client->connectToEndpoint(endpoints.at(0).endpointUrl()); // Connect to the first endpoint in the list
}

void Hs_OpcUAClient::SLOT_stateChanged(QOpcUaClient::ClientState state)
{
    qDebug() << "Client state changed:" << state;
    QMetaEnum metaEnum = QMetaEnum::fromType<QOpcUaClient::ClientState>();
    send_connect_status("Client state changed:" + *metaEnum.valueToKey(state));
}

//void Hs_OpcUAClient::SLOT_attributeRead(QOpcUa::NodeAttributes attributes)
//{
//    qDebug() << "Signal for attributes:" << attributes;
//    qDebug()<<"value:"<<m_node->attribute(QOpcUa::NodeAttribute::Value);
//}


