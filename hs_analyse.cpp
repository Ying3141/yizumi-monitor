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

void Hs_analyse::connect_to_server()//打开链接机台窗口
{
    if(!m_connect_to_server)
    {
        m_connect_to_server=new Hs_connect_to_server();
        connect(m_connect_to_server,SIGNAL(sendclient(Hs_OpcUAClient*)),this,SLOT(receive_client(Hs_OpcUAClient*)));
    }
    m_connect_to_server->show();
}

//接受返回的机台连接
void Hs_analyse::receive_client(Hs_OpcUAClient *m_client)
{
    this->m_client=m_client;
}

void Hs_analyse::node_select()//打开节点添加窗口，并初始化对机台周期参数的node，用于后续监控一模结束
{
//    if(!m_client)
//    {
//        QMessageBox::warning(this,"错误","未连接服务器",QMessageBox::Ok,QMessageBox::NoButton);
//        return;
//    }

    if(!m_node_select)
    {
        m_node_select=new Hs_collect_setting(m_client,m_nodes);
    }

    m_node_select->show();

//    m_shotcountNode=this->m_client->m_client->node("ns=4;s=APPL.system.sv_iShotCounterAct");
//    m_shotcountNode->enableMonitoring(QOpcUa::NodeAttribute::Value,QOpcUaMonitoringParameters());//对周期参数进行监视

    is_first_mold=true;

    //关闭节点添加窗口时，自动创建表格，自动添加分析
    connect(m_node_select,&Hs_collect_setting::ui_closed,this,&Hs_analyse::create_analyse);
    connect(m_node_select,&Hs_collect_setting::ui_closed,this,&Hs_analyse::create_cov_window);
}

void Hs_analyse::create_analyse()//在主界面的下半部分创建一个表格
{
//    if(!m_client)
//    {
//        QMessageBox::warning(this,"错误","未连接服务器",QMessageBox::Ok,QMessageBox::NoButton);
//        return;
//    }

//    if(!m_node_select)
//    {
//        QMessageBox::warning(this,"错误","未选择节点",QMessageBox::Ok,QMessageBox::NoButton);
//        return;
//    }

    if(m_table)
    {
        if(QMessageBox::question(this,"创建新表格","创建新表将删除旧表所有数据，确定吗？")==QMessageBox::Yes)
        {
            m_parent->m_DownLeftLay->removeWidget(m_table);
        }
        else
        {
            return;
        }
    }

    m_table=new QTableWidget(6,5,this);

    QTableWidgetItem *headerItem;
    headerItem=new QTableWidgetItem("产品重量");
    m_table->setVerticalHeaderItem(0,headerItem);
    headerItem=new QTableWidgetItem("最大值");
    m_table->setHorizontalHeaderItem(0,headerItem);
    headerItem=new QTableWidgetItem("最小值");
    m_table->setHorizontalHeaderItem(1,headerItem);
    headerItem=new QTableWidgetItem("平均值");
    m_table->setHorizontalHeaderItem(2,headerItem);
    headerItem=new QTableWidgetItem("相关系数");
    m_table->setHorizontalHeaderItem(3,headerItem);

    QTableWidgetItem *InitItem;

    for(int i=0;i<m_table->rowCount();i++)
    {
        for(int j=0;j<4;j++)
        {
            InitItem=new QTableWidgetItem("0");
            m_table->setItem(i,j,InitItem);
        }
    }

    for(int i=0;i<m_nodes.size();i++)
    {
        headerItem=new QTableWidgetItem(m_nodes.at(i)->get_name());
        m_table->setVerticalHeaderItem(i+1,headerItem);
    }

    m_parent->m_DownLeftLay->addWidget(m_table);
    //在数据库中创建对应的表
    create_database_table();
}

void Hs_analyse::on_new_mold_detected()
{
    m_table->insertColumn(4);

    qDebug()<<"on_new_mold_detected works";

    if(is_first_mold)//在节点初始化时/第一模是初始化所有connect链接
    {
        for(int i=0;i<m_nodes.size();i++)
        {
            m_nodes[i]->get_m_node()->disconnect();
            connect(m_nodes[i]->get_m_node(),&QOpcUaNode::attributeRead,this,&Hs_analyse::write_to_table);
        }
        is_first_mold=false;
    }

    for(int i=0;i<m_nodes.size();i++)//对所有的node节点进行一次读操作
    {
        m_nodes[i]->get_m_node()->readAttributes(QOpcUa::NodeAttribute::Value);
    }

}

void Hs_analyse::start_collecting()
{
    connect(m_shotcountNode,&QOpcUaNode::dataChangeOccurred,this,&Hs_analyse::on_new_mold_detected);
}

void Hs_analyse::stop_collecting()
{
    m_shotcountNode->disconnect();
}

void Hs_analyse::write_test()//测试写
{
    testnode=m_parent->analyse->get_m_client()->m_client->node("ns=4;s=APPL.Injection1.sv_InjectProfVis.Profile.Points[1].rPressure");
    QOpcUa::NodeAttribute attribute ;
    attribute = QOpcUa::NodeAttribute::Value;
    QVariant var=130;
    testnode->writeAttribute(attribute,var,QOpcUa::Types::Float);
}

void Hs_analyse::create_database_table()
{
    //创建数据库
    m_DB=new Hs_Database("./yizumi..db3");

    //根据当前时间命名表格
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy_MM_dd_hh_mm_ss");
    m_cur_active_DBTable="yizumi_"+current_date;
    m_DB->create_new_table("create table "+m_cur_active_DBTable+"(MoldCount int primary key)");

    //根据节点情况在数据库中添加列
    QString add_col;
    for(int i=0;i<m_nodes.size();i++)
    {
        add_col="alter table "+m_cur_active_DBTable+" add column "+m_nodes[i]->get_name()+" double;";
        m_DB->add_column(add_col);
    }
}

void Hs_analyse::create_cov_window()
{
    if(!m_coef)
    {
        m_coef=new Hs_CorelateCOF(m_nodes,m_table,this);
        m_DownRightLay=new QHBoxLayout();
        m_parent->m_mainGLay->addLayout(m_DownRightLay,0,8,8,1);
        m_DownRightLay->addWidget(m_coef);
        m_coef->add_display_part();
    }
    else if(m_coef->isHidden())
    {
        m_parent->m_mainGLay->addLayout(m_DownRightLay,0,8,8,1);
        m_coef->show();
        m_coef->update_combobox();
    }
    else
    {
        m_coef->update_combobox();
    }
}

void Hs_analyse::test1()
{
    m_table->insertColumn(4);
}

void Hs_analyse::create_historydata_window()
{
    if(!m_history)
    {
        m_history=new Hs_HistoryData();
        m_history->show();
    }
    else {
        m_history->show();
    }
}

void Hs_analyse::test2()
{

}

void Hs_analyse::write_to_table()
{
    QOpcUaNode *node=dynamic_cast<QOpcUaNode*>(sender());
    double curvalue=node->valueAttribute().value<double>();
    QTableWidgetItem *Item=Item=new QTableWidgetItem(QString::number(curvalue));

    //根据发送者，找到他在表格中应该的位置（行数）。
    //由于触发write_to_table函数的顺序就是m_nodes容器内nodeid的顺序，可以使用map记录nodeid名和下标的关系
    //利用nodeid可以找到对应的下标
    if(!m_map.count(node))
    {
        m_map.insert(node,index);
        index++;
    }
    //判断是否在上下限之内
    if(curvalue>m_nodes[m_map[node]]->get_up_limit()||curvalue<m_nodes[m_map[node]]->get_down_limit())
    {
        Item->setBackgroundColor(Qt::red);
    }
    m_table->setItem(m_map[node]+1,4,Item);

    //判断是否超过最大值，更新最大值
    if(curvalue>m_table->item(m_map[node]+1,0)->text().toDouble())
        m_table->item(m_map[node]+1,0)->setText(QString::number(curvalue));
    //判断是否超过最小值，更新最小值
    if(curvalue<m_table->item(m_map[node]+1,1)->text().toDouble())
        m_table->item(m_map[node]+1,1)->setText(QString::number(curvalue));
    //更新平均值
    double sum=0;
    for(int i=4;i<m_table->columnCount()-1;i++)
        sum+=m_table->item(m_map[node]+1,i)->text().toDouble();
    m_table->item(m_map[node]+1,2)->setText(QString::number(sum/(m_table->columnCount()-5)));

    //根据节点的下标在数据库中找到对应的列,在数据库添加记录
    m_DB->add_record(m_cur_active_DBTable,m_map[node]+1,curvalue);
}


Hs_OpcUAClient* Hs_analyse::get_m_client()
{
    return m_client;
}

Hs_connect_to_server* Hs_analyse::get_m_connect_to_server()
{
    return m_connect_to_server;
}
