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
    hs_node *new_node=new hs_node(m_client->m_client->node(ui->node_input->text()),ui->ch_input->text(),ui->node_input->text(),true);
    m_nodes->push_back(new_node);
    ui->chinese_names->appendPlainText(m_nodes->back()->get_name());
    ui->node_names->appendPlainText(m_nodes->back()->get_node_id());
    ui->node_input->clear();
    ui->ch_input->clear();
}

void Hs_collect_setting::initialize()
{
    for(auto it:*m_nodes)
    {
        ui->chinese_names->appendPlainText(it->get_name());
        ui->node_names->appendPlainText(it->get_node_id());
    }

    ui->ch_input->setMinimumHeight(20);
    ui->node_input->setMinimumHeight(20);
    ui->chinese_name->setMinimumHeight(10);
    ui->node_name->setMinimumHeight(10);

    m_GridLayout=new QGridLayout();
    m_GridLayout->addWidget(ui->chinese_name,0,0,1,2);
    m_GridLayout->addWidget(ui->ch_input,0,2,1,8);
    m_GridLayout->addWidget(ui->node_name,1,0,1,2);
    m_GridLayout->addWidget(ui->node_input,1,2,1,8);
    m_GridLayout->addWidget(ui->pushButton,2,0,1,10);
    m_GridLayout->addWidget(ui->chinese_names,3,0,6,4);
    m_GridLayout->addWidget(ui->node_names,3,6,6,4);
    m_GridLayout->addWidget(ui->pushButton_2,9,0,2,10);

    setLayout(m_GridLayout);

}
