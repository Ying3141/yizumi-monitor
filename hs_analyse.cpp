#include "hs_analyse.h"
#include "ui_hs_analyse.h"

//#include "mainwindow.h"
//#include "ui_mainwindow.h"

Hs_analyse::Hs_analyse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hs_analyse)
{
    ui->setupUi(this);
    //m_parent = static_cast<MainWindow*>(parent);
}

Hs_analyse::~Hs_analyse()
{
    delete ui;
}

void Hs_analyse::connect_to_server()
{
    m_connect_to_server=new Hs_connect_to_server();
    connect(m_connect_to_server,SIGNAL(sendclient(Hs_OpcUAClient*)),this,SLOT(receive_client(Hs_OpcUAClient*)));
    m_connect_to_server->show();
}

void Hs_analyse::receive_client(Hs_OpcUAClient *m_client)
{
    this->m_client=m_client;
}

void Hs_analyse::node_select()
{
    m_node_select=new Hs_collect_setting(m_nodes);
    m_node_select->show();
}

void Hs_analyse::node_setting()
{
    m_node_setting=new Hs_Node_setting(m_nodes);
    m_node_setting->show();
}

//void Hs_analyse::create_analyse()
//{
//    if(m_parent->m_table)
//    {
//        m_parent->m_DownLay->removeWidget(m_parent->m_table);
//    }

//    m_parent->m_table=new QTableWidget(m_parent->analyse->get_m_nodes().size()+1,1,this);

//    QTableWidgetItem *headerItem;
//    headerItem=new QTableWidgetItem("产品重量");
//    m_parent->m_table->setVerticalHeaderItem(0,headerItem);

//    for(int i=0;i<m_parent->analyse->get_m_nodes().size();i++)
//    {
//        headerItem=new QTableWidgetItem(m_parent->analyse->get_m_nodes().at(i)->get_name());
//        m_parent->m_table->setVerticalHeaderItem(i+1,headerItem);
//    }
//    m_parent->m_DownLay->addWidget(m_parent->m_table);
//}

//void Hs_analyse::update_data()
//{

//}

void Hs_analyse::test1()
{

}

void Hs_analyse::test2()
{

}

QVector<hs_node*> Hs_analyse::get_m_nodes()
{
    return m_nodes;
}

Hs_OpcUAClient* Hs_analyse::get_m_client()
{
    return m_client;
}
