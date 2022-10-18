#ifndef HS_NODE_H
#define HS_NODE_H
#include <QString>
#include <QOpcUaNode>

//节点类，包括节点中文名，node名，上下限，是否启用
class hs_node
{
public:
    hs_node (QOpcUaNode *node,QString name,QString node_id,bool usable,float up_limit=0.0,float down_limit=0.0);//每个节点都直接包含opcuanode实例
    void    set_name(QString);
    void    set_node_id(QString);
    void    set_usable(bool);
    void    set_up_limit(float);
    void    set_down_limit(float);
    QString get_name();
    QString get_node_id();
    bool    get_usable();
    float   get_up_limit();
    float   get_down_limit();
    QOpcUaNode* get_m_node();

private:
    QString name;
    QString node_id;
    bool    usable;
    float   up_limit;
    float   down_limit;
    QOpcUaNode *m_node=nullptr;
};

#endif // HS_NODE_H
