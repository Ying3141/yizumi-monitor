#include "HsNodeConfig.h"
#include "ui_HsNodeConfig.h"

#include "HsDataManage.h"

#include <QMessageBox>

HsNodeConfig::HsNodeConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HsNodeConfig)
{
    ui->setupUi(this);

    initializeView();
}

HsNodeConfig::~HsNodeConfig()
{
    delete ui;
}

void HsNodeConfig::initializeView()
{
    this->setWindowTitle(tr("节点配置"));
    this->setWindowModality(Qt::ApplicationModal);

    auto &dataModel = HsDataManage::instance()->getDataModel();
    auto &nodes = dataModel[0].nodes;

    for (auto i(0); i < nodes.length(); ++i) {
        ui->listWidget->addItem(nodes[i].nodeName + ": " + nodes[i].nodePath);
    }

}

void HsNodeConfig::on_addNode_clicked()
{
    if (ui->lEdt_nodeName->text().isEmpty() || ui->lEdt_nodePath->text().isEmpty()) {
        QMessageBox::information(this, tr("提示！"), tr("请填写节点信息!"));
        return;
    }

    ui->listWidget->addItem(ui->lEdt_nodeName->text() + ": " + ui->lEdt_nodePath->text());

}

void HsNodeConfig::on_delNode_clicked()
{
    const auto &selectItems = ui->listWidget->selectedItems();

    for (auto i(0); i < selectItems.length(); ++i) {
        ui->listWidget->takeItem(ui->listWidget->row(selectItems.at(i)) - i);
    }
}
