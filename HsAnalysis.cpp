#include "HsAnalysis.h"
#include "ui_HsAnalysis.h"

#include "mainwindow.h"
#include "HsDataManage.h"
#include "HsConnectConfig.h"
#include "HsNodeConfig.h"
#include "HsMonitorConfig.h"

HsAnalysis::HsAnalysis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HsAnalysis)
{
    ui->setupUi(this);

    initializeView();
    initialize_slots();
}

HsAnalysis::~HsAnalysis()
{
    delete ui;
}

void HsAnalysis::on_statistic_data_receive(std::vector<statistic_data>statistic_data)
{
    update_table(statistic_data);
}

void HsAnalysis::on_newMold_signal_receive()
{
    ui->qualityindex->insertColumn(0);
}

void HsAnalysis::initializeView()
{
    auto &actionMap = MainWindow::getActionMap();

    // 质量指标配置界面
    m_qualityConfig = new HsQualityConfig;
    connect(actionMap["Quality"], &QAction::triggered, this, [&]{
       m_qualityConfig->show();
    });
    loadModelData();
}

void HsAnalysis::loadModelData()
{
    // 配置统计值表格
    auto &nodes = HsDataManage::instance()->getDataModel()[0].nodes;
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

    // 配置质量指标表格
    auto &qualitys=HsDataManage::instance()->getDataModel()[0].qualitys;
    //根据节点数添加行数
    ui->qualityindex->setRowCount(qualitys.size());
    vertical_tableHeader.clear();
    for (auto i(0); i < qualitys.length(); ++i)
        vertical_tableHeader.append(qualitys[i].QualityName);
        //ui->tableWidget->setItem(i, 0, new QTableWidgetItem(nodes[i].nodeName));
    ui->qualityindex->setVerticalHeaderLabels(vertical_tableHeader);
}

void HsAnalysis::updateModelData()
{
    auto &qualitys = HsDataManage::instance()->getDataModel()[0].qualitys;
    ui->qualityindex->setRowCount(qualitys.size());
    QStringList vertical_tableHeader;
    for (auto i(0); i < qualitys.length(); ++i)
        vertical_tableHeader.append(qualitys[i].QualityName);
    ui->qualityindex->setVerticalHeaderLabels(vertical_tableHeader);

    //更新节点信息后清除所有保存的数据。
    for(auto it:qualitys)
    {
        it.records.clear();
    }
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

void HsAnalysis::initialize_slots()
{
    connect(m_qualityConfig,&HsQualityConfig::updateView,this,&HsAnalysis::updateModelData);
}

void HsAnalysis::on_pushButton_clicked()
{
    auto &qualitys=HsDataManage::instance()->getDataModel()[0].qualitys[0].records;
}

float HsAnalysis::cal_coef(QList<float>recordsA,QList<float> recordsB)
{
    if(recordsA.size()!=recordsB.size())
    {
        return 0;
    }

    double sumA(0.0), sumB(0.0), aveA(0.0), aveB(0.0);
    int Length=recordsA.size();
    //求和
    sumA = std::accumulate(recordsA.begin(), recordsA.end(), 0.0);
    sumB = std::accumulate(recordsB.begin(), recordsB.end(), 0.0);

    //求平均值
    aveA = sumA / double(Length);
    aveB = sumB / double(Length);

    //计算相关系数
    double R1(0), R2(0), R3(0);
    for (long i = 0; i < Length; i++)
    {
        R1 += (recordsA[i] - aveA) * (recordsB[i] - aveB);
        R2 += pow((recordsA[i] - aveA), 2);
        R3 += pow((recordsB[i] - aveB), 2);
    }

    return (R1 / sqrt(R2*R3));
}
