#include "hs_analyse.h"
#include "ui_hs_analyse.h"

Hs_analyse::Hs_analyse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hs_analyse)
{
    ui->setupUi(this);
    table=new QTableWidget(3,3,this);
}

Hs_analyse::~Hs_analyse()
{
    delete ui;
}
