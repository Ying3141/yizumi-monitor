#include "hs_analyse_action.h"
#include "ui_hs_analyse_action.h"

Hs_Analyse_Action::Hs_Analyse_Action(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hs_Analyse_Action)
{
    ui->setupUi(this);
    initialize();
    initialize_slots();
}

Hs_Analyse_Action::~Hs_Analyse_Action()
{
    delete ui;
}

void Hs_Analyse_Action::bindWidget(QWidget *widget)
{
    m_analyse = dynamic_cast<Hs_analyse *>(widget);
}

void Hs_Analyse_Action::initialize()
{
    ui->connect_to_server->setFixedSize(60,80);
    ui->node_select->setFixedSize(60,80);
    ui->node_setting->setFixedSize(60,80);
    ui->create_analyse->setFixedSize(60,80);
    ui->update_data->setFixedSize(60,80);
    ui->test1->setFixedSize(60,80);
    ui->test2->setFixedSize(60,80);

    ui->connect_to_server->setText("连接\n设备");
    ui->node_select->setText("节点\n选择");
    ui->node_setting->setText("节点\n设置");
    ui->create_analyse->setText("创建\n分析");
    ui->update_data->setText("更新\n数据");
    ui->test1->setText("测试\n1");
    ui->test2->setText("测试\n2");
}

void Hs_Analyse_Action::initialize_slots()
{
    //connect(ui->connect_to_server,SIGNAL(clicked()),this,SLOT(on_connect_to_server_clicked()));
    //connect(ui->node_setting,SIGNAL(clicked()),this,SLOT(on_node_setting_clicked()));
    //connect(ui->create_analyse,SIGNAL(clicked()),this,SLOT(on_create_analyse_clicked()));
    //connect(ui->update_data,SIGNAL(clicked()),this,SLOT(on_update_data_clicked()));
    connect(ui->test1,SIGNAL(clicked()),this,SLOT(on_test1_clicked()));
    connect(ui->test2,SIGNAL(clicked()),this,SLOT(on_test2_clicked()));
}

void Hs_Analyse_Action::on_connect_to_server_clicked()
{
    m_analyse->connect_to_server();
}

void Hs_Analyse_Action::on_node_select_clicked()
{
    m_analyse->node_select();
}

void Hs_Analyse_Action::on_node_setting_clicked()
{
    m_analyse->node_setting();
}

void Hs_Analyse_Action::on_create_analyse_clicked()
{
    m_analyse->create_analyse();
}

void Hs_Analyse_Action::on_update_data_clicked()
{
    m_analyse->update_data();
}

void Hs_Analyse_Action::on_test1_clicked()
{
    m_analyse->test1();
}

void Hs_Analyse_Action::on_test2_clicked()
{
    m_analyse->test2();
}
