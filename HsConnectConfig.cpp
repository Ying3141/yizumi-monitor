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
        m_opcClient->requestEndpoints(QUrl(ui->lEdt_url->text()));
    }
}

void HsConnectConfig::on_endpointsRequestFinished(QVector<QOpcUa::QEndpointDescription> endpoints , QOpcUa::UaStatusCode statusCode)
{
    qDebug()<<endpoints.at(0).endpointUrl();
    qDebug()<<statusCode;
    qDebug() << "Endpoints returned:" << endpoints.count();
    qDebug()<<endpoints.size();
    if (endpoints.size())
        m_opcClient->connectToEndpoint(endpoints.at(0).endpointUrl()); // Connect to the first endpoint in the list
}
