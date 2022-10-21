#include "HsBasicInfo.h"
#include "ui_HsBasicInfo.h"

HsBasicInfo::HsBasicInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HsBasicInfo)
{
    ui->setupUi(this);
}

HsBasicInfo::~HsBasicInfo()
{
    delete ui;
}
