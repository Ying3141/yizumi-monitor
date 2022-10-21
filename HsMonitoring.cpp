#include "HsMonitoring.h"
#include "ui_HsMonitoring.h"

HsMonitoring::HsMonitoring(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HsMonitoring)
{
    ui->setupUi(this);
}

HsMonitoring::~HsMonitoring()
{
    delete ui;
}
