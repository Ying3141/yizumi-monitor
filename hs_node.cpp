#include "hs_node.h"

hs_node::hs_node(QString name,QString node_id,bool usable)
{
    this->name=name;
    this->node_id=node_id;
    this->usable=usable;
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
