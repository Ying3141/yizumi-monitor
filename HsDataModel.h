#ifndef HSDATAMODEL_H
#define HSDATAMODEL_H

#include <QString>
#include <QList>

struct ConnectModel {
    QString connectName;
    QString connectUrl;
    int authMethod; // 0: 匿名; 1: 基本认证
    QString username;
    QString password;

};

struct NodeModel {
    QString nodeName;
    QString nodePath;
    bool enable;
    float upperLimit;
    float lowerLimit;
    QList<float> records;
};

class HsDataModel
{
public:
    HsDataModel();

    ConnectModel connect;
    QList<NodeModel> nodes;
};

#endif // HSDATAMODEL_H
