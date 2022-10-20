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
    ui->create_analyse->resize(60,80);
    ui->start_collecting->resize(60,80);
    ui->cov_analyse->resize(60,80);
    ui->test1->resize(60,80);
    ui->test2->resize(60,80);

    ui->create_analyse->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Minimum);
    ui->start_collecting->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Minimum);
    ui->cov_analyse->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Minimum);
    ui->test1->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Minimum);
    ui->test2->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Minimum);

    ui->create_analyse->setText("创建\n分析");
    ui->start_collecting->setText("未在\n采集");
    ui->cov_analyse->setText("相关\n分析");
    ui->test1->setText("测试\n1");
    ui->test2->setText("测试\n2");\

    ui->start_collecting->setCheckable(true);
    ui->start_collecting->setStyleSheet("background-color:rgb(255,99,71)");

    t_time = new QTimer(this);
    t_time->start(1000);//设置时间间隔为1秒

}

void Hs_Analyse_Action::initialize_slots()
{
    connect(t_time, SIGNAL(timeout()), this, SLOT(time_out()));
}

void Hs_Analyse_Action::on_create_analyse_clicked()
{
    m_analyse->create_analyse();
}

void Hs_Analyse_Action::on_cov_analyse_clicked()
{
    m_analyse->create_cov_window();
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

//窗口时间展示
void Hs_Analyse_Action::time_out()
{
    QDateTime t_time = QDateTime::currentDateTime();
    QString t_str = t_time.toString("ddd yyyy-MM-dd hh:mm:ss");
    ui->time->setText(t_str);
}
//窗口当前机台展示
void Hs_Analyse_Action::on_machine_changed(QString url)
{
    ui->curmachine->setText("当前机台:"+url);
}
