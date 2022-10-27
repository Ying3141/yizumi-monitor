#include "HsConnectConfig.h"
#include "ui_HsConnectConfig.h"

#include <QtOpcUa>

#include "HsDataManage.h"

HsConnectConfig::HsConnectConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HsConnectConfig)
{
    ui->setupUi(this);

    initializeView();
}

HsConnectConfig::~HsConnectConfig()
{
    delete ui;
}

void HsConnectConfig::initializeView()
{
    this->setWindowTitle(tr("连接设置"));
    this->setWindowModality(Qt::ApplicationModal);

    auto &dataModel = HsDataManage::instance()->getDataModel();
    auto &connect = dataModel[0].connect;

    ui->lEdt_name->setText(connect.connectName);
    ui->lEdt_url->setText(connect.connectUrl);

    ui->anonymous->setChecked(connect.authMethod == 0);
}

void HsConnectConfig::on_connect_clicked()
{
    if (!m_opcPrivider) {
        m_opcPrivider = new QOpcUaProvider;
        m_opcClient = m_opcPrivider->createClient(QString("open62541"));
        //根据机台地址连接，获取根节点
        connect(m_opcClient,&QOpcUaClient::endpointsRequestFinished,this,&HsConnectConfig::on_endpointsRequestFinished);
        connect(m_opcClient,&QOpcUaClient::stateChanged,this,&HsConnectConfig::on_stateChanged);
        m_opcClient->requestEndpoints(QUrl(ui->lEdt_url->text()));
    }

    this->close();
}

void HsConnectConfig::on_endpointsRequestFinished(QVector<QOpcUa::QEndpointDescription> endpoints , QOpcUa::UaStatusCode statusCode)
{
    qDebug()<<endpoints.at(0).endpointUrl();
    qDebug()<<statusCode;
    qDebug() << "Endpoints returned:" << endpoints.count();
    qDebug()<<endpoints.size();
    if (endpoints.size())
        m_opcClient->connectToEndpoint(endpoints.at(0).endpointUrl()); // Connect to the first endpoint in the list
//    auto node = m_opcClient->node("ns=0;i=84");
    qDebug() << m_opcClient->node("ns=0;i=84");
    qDebug() << m_opcClient->node("ns=2;i=1");
    qDebug() << m_opcClient->node("ns=2;i=2");
}

void HsConnectConfig::on_stateChanged(QOpcUaClient::ClientState state)
{
    qDebug() << "Client state changed:" << state;

    if (state == QOpcUaClient::ClientState::Disconnected)
    {
        m_shotcountNode = nullptr;
    }

    else if (state == QOpcUaClient::ClientState::Connected)
    {
        //定义一个表示模次号的node，用于自动采集数据
        m_shotcountNode = m_opcClient->node("ns=4;s=APPL.system.sv_iShotCounterAct");
        //对模次号参数进行监视
        m_shotcountNode->enableMonitoring(QOpcUa::NodeAttribute::Value,QOpcUaMonitoringParameters());
    }
}

QOpcUaClient* HsConnectConfig::get_m_opcClient()
{
    return m_opcClient;
}

QOpcUaNode* HsConnectConfig::get_m_shotcountNode()
{
    return m_shotcountNode;
}
