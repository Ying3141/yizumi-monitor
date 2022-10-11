#include "hs_thread2.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MyThread_2::MyThread_2(QOpcUaNode *node,QObject *parent)
{
    this->m_node=node;
    m_parent = static_cast<MainWindow*>(parent);
    node->readAttributes(QOpcUa::NodeAttribute::Value);
}

void MyThread_2::run()
{
    m_node=m_parent->analyse->get_m_client()->m_client->node("ns=4;s=APPL.Injection1.sv_rScrewPositionAbs");
}
