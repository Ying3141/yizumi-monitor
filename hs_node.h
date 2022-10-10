#ifndef HS_NODE_H
#define HS_NODE_H
#include <QString>
#include <QOpcUaNode>

class hs_node
{
public:
    hs_node (QString,QString,bool);
    void    set_name(QString);
    void    set_node_id(QString);
    void    set_usable(bool);
    QString get_name();
    QString get_node_id();
    bool    get_usable();

private:
    QString name;
    QString node_id;
    bool    usable;
};

#endif // HS_NODE_H
