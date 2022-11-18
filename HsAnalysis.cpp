#include "HsAnalysis.h"
#include "ui_HsAnalysis.h"

#include "HsDataManage.h"
#include "HsConnectConfig.h"
#include "HsNodeConfig.h"
#include "HsMonitorConfig.h"

HsAnalysis::HsAnalysis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HsAnalysis)
{
    ui->setupUi(this);

    loadModelData();
}

HsAnalysis::~HsAnalysis()
{
    delete ui;
}

void HsAnalysis::on_statistic_data_receive(std::vector<statistic_data>statistic_data)
{
    update_table(statistic_data);
}

void HsAnalysis::loadModelData()
{
    auto &nodes = HsDataManage::instance()->getDataModel()[0].nodes;

    // 配置表格
    QStringList tableHeader;
    //根据节点数添加行数
    ui->tableWidget->setRowCount(nodes.size());
    //初始列数默认包括最大值，最小值，平均值，相关系数
    ui->tableWidget->setColumnCount(5);
    tableHeader << "最大值" << "最小值" << "平均值" << "方差" << "相关系数";
    ui->tableWidget->setHorizontalHeaderLabels(tableHeader);

    QStringList vertical_tableHeader;
    for (auto i(0); i < nodes.length(); ++i)
        vertical_tableHeader.append(nodes[i].nodeName);
        //ui->tableWidget->setItem(i, 0, new QTableWidgetItem(nodes[i].nodeName));
    ui->tableWidget->setVerticalHeaderLabels(vertical_tableHeader);
}

void HsAnalysis::update_table(std::vector<statistic_data>statistic_data)
{
    for(int i=0;i<statistic_data.size();i++)
    {
        QTableWidgetItem *max=new QTableWidgetItem(QString::number(statistic_data[i].max));
        QTableWidgetItem *min=new QTableWidgetItem(QString::number(statistic_data[i].min));
        QTableWidgetItem *avg=new QTableWidgetItem(QString::number(statistic_data[i].average));
        QTableWidgetItem *var=new QTableWidgetItem(QString::number(statistic_data[i].variance));
        ui->tableWidget->setItem(i,0,max);
        ui->tableWidget->setItem(i,1,min);
        ui->tableWidget->setItem(i,2,avg);
        ui->tableWidget->setItem(i,3,var);
    }
}
