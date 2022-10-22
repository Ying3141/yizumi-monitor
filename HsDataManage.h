#ifndef HSDATAMANAGE_H
#define HSDATAMANAGE_H

#include <QObject>
#include <QHash>

#include "HsDataModel.h"

class HsDataManage
{
public:
    HsDataManage();
    ~HsDataManage();

public:
    static HsDataManage *instance();
    QHash<int, HsDataModel> &getDataModel();

private:
    void initialize();

private:
    static HsDataManage *ins;
    QHash<int, HsDataModel> dataModel;
};

#endif // HSDATAMANAGE_H
