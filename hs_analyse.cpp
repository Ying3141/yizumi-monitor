#include "hs_analyse.h"
#include "ui_hs_analyse.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

Hs_analyse::Hs_analyse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hs_analyse)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TransparentForMouseEvents,true);
    m_parent = static_cast<MainWindow*>(parent);
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
    m_node_select=new Hs_collect_setting(m_client,m_nodes);
    m_node_select->show();
}

void Hs_analyse::node_setting()
{
    m_node_setting=new Hs_Node_setting(m_nodes);
    m_node_setting->show();
}

void Hs_analyse::create_analyse()
{
    if(m_parent->m_table)
    {
        m_parent->m_DownLay->removeWidget(m_parent->m_table);
    }

    m_parent->m_table=new QTableWidget(m_parent->analyse->get_m_nodes().size()+1,1,this);

    QTableWidgetItem *headerItem;
    headerItem=new QTableWidgetItem("产品重量");
    m_parent->m_table->setVerticalHeaderItem(0,headerItem);

    for(int i=0;i<m_parent->analyse->get_m_nodes().size();i++)
    {
        headerItem=new QTableWidgetItem(m_parent->analyse->get_m_nodes().at(i)->get_name());
        m_parent->m_table->setVerticalHeaderItem(i+1,headerItem);
    }
    m_parent->m_DownLay->addWidget(m_parent->m_table);
}

void Hs_analyse::update_data()
{

//    m_shotcountNode=m_client->m_client->node("ns=4;s=APPL.system.sv_iShotCounterAct");//连接到周期参数，备用
//    m_shotcountNode->enableMonitoring(QOpcUa::NodeAttribute::Value,QOpcUaMonitoringParameters(100));//对周期参数进行监视
//    connect(m_shotcountNode,&QOpcUaNode::dataChangeOccurred,this,&Hs_analyse::test2);

    int curCol=m_parent->m_table->columnCount();
    m_parent->m_table->insertColumn(curCol);

    qDebug()<<"works";

    for(int i=0;i<m_nodes.size();i++)
    {
        m_nodes[i]->get_m_node()->disconnect();
        connect(m_nodes[i]->get_m_node(),&QOpcUaNode::attributeRead,this,&Hs_analyse::test2);
        m_nodes[i]->get_m_node()->readAttributes(QOpcUa::NodeAttribute::Value);
    }

}

void Hs_analyse::test1()//测试写
{
    testnode=m_parent->analyse->get_m_client()->m_client->node("ns=4;s=APPL.Injection1.sv_InjectProfVis.Profile.Points[1].rPressure");
    QOpcUa::NodeAttribute attribute ;
    attribute = QOpcUa::NodeAttribute::Value;
    QVariant var=130;
    testnode->writeAttribute(attribute,var,QOpcUa::Types::Float);
    qDebug()<<"works1";

}

void Hs_analyse::test2()//测试接受数据变化信号
{
    qDebug()<<"works2";
    QOpcUaNode *node=(QOpcUaNode*)sender();
    qDebug()<<node->valueAttribute().value<float>();

    //根据发送者，找到他在表格中应该的位置（行数）。
    if(m_map.count(node))
    {
        QTableWidgetItem *headerItem;
        headerItem=new QTableWidgetItem(QString::number(node->valueAttribute().value<float>()));
        m_parent->m_table->setItem(m_map[node]+1,m_parent->m_table->columnCount()-1,headerItem);
    }
    m_map.insert(node,index);
    QTableWidgetItem *headerItem;
    headerItem=new QTableWidgetItem(QString::number(node->valueAttribute().value<float>()));
    m_parent->m_table->setItem(index+1,m_parent->m_table->columnCount()-1,headerItem);
    index++;

}

QVector<hs_node*> Hs_analyse::get_m_nodes()
{
    return m_nodes;
}

Hs_OpcUAClient* Hs_analyse::get_m_client()
{
    return m_client;
}
