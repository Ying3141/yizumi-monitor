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

HsDataBase* HsNodeConfig::getDataBase()
{
    return DB;
}

QString HsNodeConfig::getTableName()
{
    return m_tablename;
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

void HsNodeConfig::on_confirm_clicked()
{
    // 更新node信息
    auto &dataModel = HsDataManage::instance()->getDataModel();
    auto &nodes = dataModel[0].nodes;
    nodes.clear();

    for (auto i(0); i < ui->listWidget->count(); ++i) {
        auto item = ui->listWidget->item(i)->text();
        QStringList viewNode = item.split(": ");
        NodeModel node;
        node.nodeName = viewNode[0];
        node.nodePath = viewNode[1];
        node.enable = true;
        nodes.push_back(node);
    }

    emit updateView();

    CreateDataBase();

    this->close();
}

void HsNodeConfig::CreateDataBase()
{
    auto &dataModel = HsDataManage::instance()->getDataModel();
    auto &nodes = dataModel[0].nodes;
    auto &connect=dataModel[0].connect;
    //创建数据库
    DB=new HsDataBase("./yizumi..db3");

    //根据当前时间命名表格
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy_MM_dd_hh_mm_ss");
    m_tablename=connect.connectName+"_"+current_date;
    DB->create_new_table("create table "+m_tablename+"(id int primary key)");


    //根据节点情况在数据库中添加列
    QString add_col;
    for(auto it : nodes)
    {
        add_col="alter table "+m_tablename+" add column "+it.nodeName+" double;";
        DB->add_column(add_col);
    }
}

void HsNodeConfig::on_cancel_clicked()
{
    this->close();
}
