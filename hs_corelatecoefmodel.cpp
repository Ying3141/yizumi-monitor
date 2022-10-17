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
    ui->paraeter_select->clear();
    for(auto it:*m_nodes)
    {
        ui->paraeter_select->addItem(it->get_name());
    }
    ui->paraeter_select->setCurrentIndex(-1);
    ui->COEF_show->clear();
}

void Hs_CoRelateCOEFModel::on_paraeter_select_currentIndexChanged(int index)
{
    index_changed(index);
}

void Hs_CoRelateCOEFModel::setLineedit(double var)
{
    ui->COEF_show->setText(QString::number(var,'g', 2));
}

