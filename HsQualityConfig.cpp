#include "HsQualityConfig.h"
#include "ui_HsQualityConfig.h"
#include "HsDataManage.h"
#include <QMessageBox>

HsQualityConfig::HsQualityConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HsQualityConfig)
{
    ui->setupUi(this);
    initializeView();
}

HsQualityConfig::~HsQualityConfig()
{
    delete ui;
}

void HsQualityConfig::initializeView()
{
    this->setWindowTitle(tr("指标配置"));
    this->setWindowModality(Qt::ApplicationModal);

    auto &dataModel = HsDataManage::instance()->getDataModel();
    auto &qualitys = dataModel[0].qualitys;

    for (auto i(0); i < qualitys.length(); ++i) {
        ui->listWidget->addItem(qualitys[i].QualityName);
    }

}

void HsQualityConfig::on_addNode_clicked()
{
    if (ui->lEdt_nodeName->text().isEmpty()) {
        QMessageBox::information(this, tr("提示！"), tr("请填写节点信息!"));
        return;
    }

    ui->listWidget->addItem(ui->lEdt_nodeName->text());

}

void HsQualityConfig::on_delNode_clicked()
{
    const auto &selectItems = ui->listWidget->selectedItems();

    for (auto i(0); i < selectItems.length(); ++i) {
        ui->listWidget->takeItem(ui->listWidget->row(selectItems.at(i)) - i);
    }
}

void HsQualityConfig::on_confirm_clicked()
{
    // 更新node信息
    auto &dataModel = HsDataManage::instance()->getDataModel();
    auto &qualitys = dataModel[0].qualitys;
    qualitys.clear();

    for (auto i(0); i < ui->listWidget->count(); ++i) {
        auto item = ui->listWidget->item(i)->text();
        QString viewNode = item;
        QualityModel quality;
        quality.QualityName = item;
        quality.enable = true;
        qualitys.push_back(quality);
    }

    emit updateView();

    this->close();
}

void HsQualityConfig::on_cancel_clicked()
{
    this->close();
}
