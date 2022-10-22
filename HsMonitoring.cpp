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

void HsMonitoring::initializeView()
{
    auto &actionMap = MainWindow::getActionMap();
    auto &nodes = HsDataManage::instance()->getDataModel()[0].nodes;

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

    // 监控配置界面
    m_monitorConfig = new HsMonitorConfig;
    connect(actionMap["Monitor"], &QAction::triggered, this, [&]{
       m_monitorConfig->show();
    });

    // 配置表格
    QStringList tableHeader;
    ui->tableWidget->setRowCount(5);
    ui->tableWidget->setColumnCount(5);
    tableHeader << "node name" << "1" << "2" << "3" << "4";
    ui->tableWidget->setHorizontalHeaderLabels(tableHeader);

    for (auto i(0); i < nodes.length(); ++i) {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(nodes[i].nodeName));

    //初始化时钟
    t_time = new QTimer(this);
    t_time->start(1000);//设置时间间隔为1秒
    }
}

void HsMonitoring::initialize_slots()
{
    connect(t_time, SIGNAL(timeout()), this, SLOT(time_out()));
}

void HsMonitoring::time_out()
{
    QDateTime t_time = QDateTime::currentDateTime();
    QString t_str = t_time.toString("ddd yyyy-MM-dd hh:mm:ss");
    ui->Time->setText(t_str);
}
