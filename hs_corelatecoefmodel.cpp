#include "hs_corelatecoefmodel.h"
#include "ui_hs_corelatecoefmodel.h"

Hs_CoRelateCOEFModel::Hs_CoRelateCOEFModel(QVector<hs_node*>*nodes,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hs_CoRelateCOEFModel)
{
    ui->setupUi(this);
    m_nodes=nodes;
    initialize();
}

Hs_CoRelateCOEFModel::~Hs_CoRelateCOEFModel()
{
    delete ui;
}

void Hs_CoRelateCOEFModel::initialize()
{
    for(auto it:*m_nodes)
    {
        ui->paraeter_select->addItem(it->get_name());
    }
}
