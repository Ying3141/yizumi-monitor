#include "HsMonitoring.h"
#include "ui_HsMonitoring.h"

#include "HsUI.h"
#include "mainwindow.h"
#include "HsDataManage.h"

#include "HsConnectConfig.h"
#include "HsNodeConfig.h"
#include "HsMonitorConfig.h"

HsMonitoring::HsMonitoring(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HsMonitoring)
{
    ui->setupUi(this);

    initializeView();
    initialize_slots();
}

HsMonitoring::~HsMonitoring()
{
    delete ui;
}

void HsMonitoring::showEvent(QShowEvent *event)
{

}

void HsMonitoring::initializeView()
{
    auto &actionMap = MainWindow::getActionMap();

    // 服务器连接配置界面
    m_connectConfig = new HsConnectConfig;
    connect(actionMap["Connect"], &QAction::triggered, this, [&]{
       m_connectConfig->show();
    });

    // 结点配置界面
    m_dataNode = new HsNodeConfig;
    connect(actionMap["Node"], &QAction::triggered, this, [&]{
       m_dataNode->show();
    });
    connect(m_dataNode, &HsNodeConfig::updateView, this, [&]{
       this->loadModelData();
    });

    // 监控配置界面
    m_monitorConfig = new HsMonitorConfig;
    connect(actionMap["Monitor"], &QAction::triggered, this, [&]{
       m_monitorConfig->show();
    });

    loadModelData();

    //设置采集开关
    ui->pushButton->setCheckable(true);

}

void HsMonitoring::loadModelData()
{
    auto &nodes = HsDataManage::instance()->getDataModel()[0].nodes;

    // 配置表格
    QStringList tableHeader;
    //根据节点数添加行数
    ui->tableWidget->setRowCount(nodes.size());
    //初始列数默认包括最大值，最小值，平均值，相关系数，第一模空位
    ui->tableWidget->setColumnCount(5);
    tableHeader << "最大值" << "最小值" << "平均值" << "相关系数" << "1";
    ui->tableWidget->setHorizontalHeaderLabels(tableHeader);

    QStringList vertical_tableHeader;
    for (auto i(0); i < nodes.length(); ++i)
        vertical_tableHeader.append(nodes[i].nodeName);
        //ui->tableWidget->setItem(i, 0, new QTableWidgetItem(nodes[i].nodeName));
    ui->tableWidget->setVerticalHeaderLabels(vertical_tableHeader);

    //初始化时钟
    t_time = new QTimer(this);
    t_time->start(1000);//设置时间间隔为1秒
}

void HsMonitoring::updateModelData()
{
    auto &nodes = HsDataManage::instance()->getDataModel()[0].nodes;
    ui->tableWidget->setRowCount(nodes.size());
    QStringList vertical_tableHeader;
    for (auto i(0); i < nodes.length(); ++i)
        vertical_tableHeader.append(nodes[i].nodeName);
    ui->tableWidget->setVerticalHeaderLabels(vertical_tableHeader);
}

void HsMonitoring::initialize_slots()
{
    connect(t_time, SIGNAL(timeout()), this, SLOT(time_out()));
    connect(m_dataNode,&HsNodeConfig::updateView,this,&HsMonitoring::updateModelData);
}

void HsMonitoring::time_out()
{
    QDateTime t_time = QDateTime::currentDateTime();
    QString t_str = t_time.toString("ddd yyyy-MM-dd hh:mm:ss");
    ui->Time->setText(t_str);
}

void HsMonitoring::on_pushButton_toggled(bool checked)
{
    //如果按下
    if(checked)
    {
        if(m_connectConfig->get_m_opcClient())
        {
            ui->pushButton->setStyleSheet("background-color:rgb(173,255,47)");
            ui->pushButton->setText("正在采集");
            connect(m_connectConfig->get_m_shotcountNode(),&QOpcUaNode::dataChangeOccurred,this,&HsMonitoring::on_new_mold_detected);
        }
    }

    if(!checked)
    {
        ui->pushButton->setStyleSheet("background-color:rgb(255,99,71)");
        ui->pushButton->setText("未在采集");
        m_connectConfig->get_m_shotcountNode()->disconnect();
    }
}

void HsMonitoring::on_new_mold_detected()
{
    //此函数完成读取数据并写入表格的操作
    ui->tableWidget->insertColumn(4);
}
