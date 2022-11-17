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

//更新表格内容。信号：HsNodeConfig::updateView
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

            //监测是否新的一模，如果是，则读取参数写入表格
            connect(m_connectConfig->get_m_shotcountNode(),&QOpcUaNode::dataChangeOccurred,this,&HsMonitoring::on_new_mold_detected);

            //把所有nodePath转化为QOpcuanode
            auto &nodes = HsDataManage::instance()->getDataModel()[0].nodes;
            for(auto it:nodes)
            {
                m_OpcUaNode.push_back(m_connectConfig->get_m_opcClient()->node(it.nodeName));
            }
        }
    }

    if(!checked)
    {
        ui->pushButton->setStyleSheet("background-color:rgb(255,99,71)");
        ui->pushButton->setText("未在采集");
        m_connectConfig->get_m_shotcountNode()->disconnect();
        m_OpcUaNode.clear();
    }
}

void HsMonitoring::on_new_mold_detected()
{
    //此函数完成：
    //1.连接所有节点的读信号 信号：&QOpcUaNode::attributeRead， 槽：on_readAttribute_triggered
    //示例：connect(m_nodes[i]->get_m_node(),&QOpcUaNode::attributeRead,this,&Hs_analyse::write_to_table);
    //2.给表格添加新的一列
    //示例：ui->tableWidget->insertColumn(4);
    //3.对所有节点进行读操作
    //示例：m_nodes[i]->get_m_node()->readAttributes(QOpcUa::NodeAttribute::Value);

    ui->tableWidget->insertColumn(4);
    for(auto it:m_OpcUaNode)
    {
        it->disconnect();
        connect(it,&QOpcUaNode::attributeRead,this,&HsMonitoring::on_readAttribute_triggered);
    }
    for(auto it:m_OpcUaNode)
    {
        it->readAttributes(QOpcUa::NodeAttribute::Value);
    }
}

void HsMonitoring::on_readAttribute_triggered()
{
    //此函数完成写入表格的操作
    QOpcUaNode *node=dynamic_cast<QOpcUaNode*>(sender());
    double curvalue=node->valueAttribute().value<double>();
    QTableWidgetItem *Item=Item=new QTableWidgetItem(QString::number(curvalue));

    int index=std::find(m_OpcUaNode.begin(),m_OpcUaNode.end(),node)-m_OpcUaNode.begin();
    ui->tableWidget->setItem(index,4,Item);
}
