#include "HsMonitorConfig.h"
#include "ui_HsMonitorConfig.h"

#include "HsDataManage.h"

#include <QCheckBox>
#include <QDoubleSpinBox>


HsMonitorConfig::HsMonitorConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HsMonitorConfig)
{
    ui->setupUi(this);

    initializeView();
}

HsMonitorConfig::~HsMonitorConfig()
{
    delete ui;
}

void HsMonitorConfig::showEvent(QShowEvent *event)
{
    loadModelData();
}

void HsMonitorConfig::initializeView()
{
    this->setWindowTitle(tr("监控设置"));
    this->setWindowModality(Qt::ApplicationModal);

}

void HsMonitorConfig::loadModelData()
{

    auto &nodes = HsDataManage::instance()->getDataModel()[0].nodes;

    // 配置表格
    QStringList tableHeader;
    ui->tableWidget->setRowCount(5);
    ui->tableWidget->setColumnCount(4);
    tableHeader << "变量名" << "启用" << "上限" << "下限";
    ui->tableWidget->setHorizontalHeaderLabels(tableHeader);

    for (auto i(0); i < nodes.length(); ++i) {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(nodes[i].nodeName));

        QWidget *wcbox = new QWidget();
        QCheckBox *cbox = new QCheckBox();
        QHBoxLayout *vlayout = new QHBoxLayout(wcbox);
        vlayout->addWidget(cbox);
        vlayout->setContentsMargins(0, 0, 0, 0);
        vlayout->setAlignment(Qt::AlignCenter);
        ui->tableWidget->setCellWidget(i, 1, wcbox);

        QWidget *upSpinBoxWid = new QWidget();
        QDoubleSpinBox *upSpinBox = new QDoubleSpinBox();
        QHBoxLayout *usblayout = new QHBoxLayout(upSpinBoxWid);
        usblayout->setContentsMargins(0, 0, 0, 0);
        usblayout->addWidget(upSpinBox);
        ui->tableWidget->setCellWidget(i, 2, upSpinBoxWid);

        QWidget *loSpinBoxWid = new QWidget(this);
        QDoubleSpinBox *loSpinBox = new QDoubleSpinBox();
        QHBoxLayout *loblayout = new QHBoxLayout(loSpinBoxWid);
        loblayout->setContentsMargins(0, 0, 0, 0);
        loblayout->addWidget(loSpinBox);
        ui->tableWidget->setCellWidget(i, 3, loSpinBoxWid);
    }
}
