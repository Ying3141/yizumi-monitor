#include "HsDataManage.h"


HsDataManage *HsDataManage::ins = nullptr;

HsDataManage::HsDataManage()
{
    initialize();
}

HsDataManage::~HsDataManage()
{
    delete ins;
}

HsDataManage *HsDataManage::instance()
{
    if (!ins) {
        ins = new HsDataManage;
    }
    return ins;
}

QHash<int, HsDataModel> &HsDataManage::getDataModel()
{
    return dataModel;
}

void HsDataManage::initialize()
{
    // 默认添加一个测试数据
    dataModel[0] = HsDataModel();

    // 单个机器的数据配置模型
    auto &configModel = dataModel[0];

    auto &connect = configModel.connect;
    connect.connectName = "machine1";
    connect.connectUrl = "opc.tcp://192.168.23.43:4842";
//    connect.connectUrl = "opc.tcp://127.0.0.1:49320";
    connect.authMethod = 0;
    connect.username = "";
    connect.password = "";

    auto &nodes = configModel.nodes;
    NodeModel node;
    node.nodeName = "螺杆位置";
    node.nodePath = "ns=4;s=APPL.Injection1.sv_rScrewPositionAbs";
    node.enable = true;
    nodes.push_back(node);
}
