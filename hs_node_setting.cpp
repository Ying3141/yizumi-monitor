#include "hs_node_setting.h"
#include "ui_hs_node_setting.h"

Hs_Node_setting::Hs_Node_setting(QVector<hs_node*>&m_nodes,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hs_Node_setting)
{
    ui->setupUi(this);
    this->m_nodes=&m_nodes;
    initialize();
}

Hs_Node_setting::~Hs_Node_setting()
{
    delete ui;
}

void Hs_Node_setting::initialize()
{
    ui->nodename_comboBox->clear();

    for(auto it:*m_nodes)
    {
        ui->nodename_comboBox->addItem(it->get_name());
    }
}

void Hs_Node_setting::on_nodename_comboBox_currentIndexChanged(int index)
{
    ui->uplimit_doubleSpinBox->setValue(m_nodes->at(index)->get_up_limit());
    ui->downlimit_doubleSpinBox->setValue(m_nodes->at(index)->get_down_limit());
}

void Hs_Node_setting::on_uplimit_doubleSpinBox_valueChanged(double arg1)
{
    m_nodes->at(ui->nodename_comboBox->currentIndex())->set_up_limit(ui->uplimit_doubleSpinBox->value());
}

void Hs_Node_setting::on_downlimit_doubleSpinBox_valueChanged(double arg1)
{
    m_nodes->at(ui->nodename_comboBox->currentIndex())->set_down_limit(ui->downlimit_doubleSpinBox->value());
}
