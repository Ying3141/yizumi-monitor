#include "hs_thrread.h"

MyThread::MyThread(QOpcUaNode *node,QObject *parent)
{
    this->m_node=node;
    node->readAttributes(QOpcUa::NodeAttribute::Value);
}

void MyThread::run()
{
    m_node->readAttributes(QOpcUa::NodeAttribute::Value);
}



