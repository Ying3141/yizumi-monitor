#include "hs_collect_setting.h"
#include "ui_hs_collect_setting.h"

Hs_collect_setting::Hs_collect_setting(Hs_OpcUAClient *client,QVector<hs_node*>&m_nodes,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hs_collect_setting)
{
    ui->setupUi(this);
    this->m_nodes=&m_nodes;
    this->m_client=client;
    initialize();
}

Hs_collect_setting::~Hs_collect_setting()
{
    delete ui;
}

void Hs_collect_setting::on_pushButton_clicked()
{
    hs_node *new_node=new hs_node(nullptr,ui->ch_input->text(),ui->node_input->text(),true);//直接实例化opcuanode
    m_nodes->push_back(new_node);
    ui->node_input->clear();
    ui->ch_input->clear();
    ui->nodename_comboBox->addItem(new_node->get_name());
}

void Hs_collect_setting::initialize()
{
    ui->nodename_comboBox->clear();

    for(int i=0;i<m_nodes->size();i++)
    {
        ui->nodename_comboBox->addItem(m_nodes->at(i)->get_name());
    }
}

void Hs_collect_setting::closeEvent(QCloseEvent * event)
{
    ui_closed();
    qDebug() << "closeEvent ";
}

void Hs_collect_setting::on_nodename_comboBox_currentIndexChanged(int index)
{
    ui->uplimit_doubleSpinBox->setValue(m_nodes->at(index)->get_up_limit());
    ui->downlimit_doubleSpinBox->setValue(m_nodes->at(index)->get_down_limit());
}

void Hs_collect_setting::on_uplimit_doubleSpinBox_valueChanged(double arg1)
{
    m_nodes->at(ui->nodename_comboBox->currentIndex())->set_up_limit(ui->uplimit_doubleSpinBox->value());
}

void Hs_collect_setting::on_downlimit_doubleSpinBox_valueChanged(double arg1)
{
    m_nodes->at(ui->nodename_comboBox->currentIndex())->set_down_limit(ui->downlimit_doubleSpinBox->value());
}
