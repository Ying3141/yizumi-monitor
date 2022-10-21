#include "HsAnalysis.h"
#include "ui_HsAnalysis.h"

HsAnalysis::HsAnalysis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HsAnalysis)
{
    ui->setupUi(this);
}

HsAnalysis::~HsAnalysis()
{
    delete ui;
}
