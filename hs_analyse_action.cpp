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
    ui->start_collecting->setFixedSize(60,80);
    ui->test1->setFixedSize(60,80);
    ui->test2->setFixedSize(60,80);

    ui->connect_to_server->setText("连接\n设备");
    ui->node_select->setText("节点\n选择");
    ui->node_setting->setText("节点\n设置");
    ui->create_analyse->setText("创建\n分析");
    ui->start_collecting->setText("开始\n采集");
    ui->test1->setText("测试\n1");
    ui->test2->setText("测试\n2");

    ui->start_collecting->setCheckable(true);
}

void Hs_Analyse_Action::initialize_slots()
{

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

void Hs_Analyse_Action::on_test1_clicked()
{
    m_analyse->test1();
}

void Hs_Analyse_Action::on_test2_clicked()
{
    m_analyse->test2();
}

void Hs_Analyse_Action::on_start_collecting_toggled(bool checked)
{

    if(checked)
    {
        ui->start_collecting->setStyleSheet("background-color:rgb(173,255,47)");
        ui->start_collecting->setText("正在\n采集");
        m_analyse->start_collecting();
    }

    if(!checked)
    {
        ui->start_collecting->setStyleSheet("background-color:rgb(255,99,71)");
        ui->start_collecting->setText("未在\n采集");
        m_analyse->stop_collecting();
    }
}
