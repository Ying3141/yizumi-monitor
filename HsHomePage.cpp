#include "HsHomePage.h"
#include "ui_HsHomePage.h"

HsHomePage::HsHomePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HsHomePage)
{
    ui->setupUi(this);
}

HsHomePage::~HsHomePage()
{
    delete ui;
}
