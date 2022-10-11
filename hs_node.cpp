#include "hs_node.h"

hs_node::hs_node(QOpcUaNode *node,QString name,QString node_id,bool usable,float up_limit,float down_limit)
{
    this->m_node=node;//每个节点都直接包含opcuanode实例
    this->name=name;
    this->node_id=node_id;
    this->usable=usable;
    this->up_limit=up_limit;
    this->down_limit=down_limit;
}

void hs_node::set_name(QString name)
{
    this->name=name;
}

void hs_node::set_node_id(QString node_id)
{
    this->node_id=node_id;
}

void hs_node::set_usable(bool usable)
{
    this->usable=usable;
}

void hs_node::set_up_limit(float up_limit)
{
    this->up_limit=up_limit;
}

void hs_node::set_down_limit(float down_limit)
{
    this->down_limit=down_limit;
}

QString hs_node::get_name()
{
    return this->name;
}

QString hs_node::get_node_id()
{
    return this->node_id;
}

bool hs_node::get_usable()
{
    return this->usable;
}

float hs_node::get_up_limit()
{
    return this->up_limit;
}

float hs_node::get_down_limit()
{
    return this->down_limit;
}

QOpcUaNode* hs_node::get_m_node()
{
    return m_node;
}
