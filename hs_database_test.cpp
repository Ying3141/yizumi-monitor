#include "hs_database_test.h"
#include "ui_hs_database_test.h"

hs_DataBase_test::hs_DataBase_test(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::hs_DataBase_test)
{
    ui->setupUi(this);
}

hs_DataBase_test::~hs_DataBase_test()
{
    delete ui;
}

void hs_DataBase_test::on_pushButton_clicked()
{
    QString aFile=QFileDialog::getOpenFileName(this,"选择数据库文件","C:/Users/Ying/Desktop","SQLite数据库(*.db *.db3)");
    if(aFile.isEmpty())
    {
        return;
    }
    DB=QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName(aFile);
    if(!DB.open())
    {
        QMessageBox::warning(this,"错误","Fail",QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }
}

void hs_DataBase_test::opentable()
{


}

void hs_DataBase_test::on_pushButton_2_clicked()
{
    m_tabmodel=new QSqlTableModel(this,DB);
    m_tabmodel->setTable("testTable");
    m_tabmodel->setHeaderData(m_tabmodel->fieldIndex("Name"),Qt::Horizontal,"姓名");
    m_tabmodel->setHeaderData(m_tabmodel->fieldIndex("Age"),Qt::Horizontal,"年龄");
    m_tabmodel->setHeaderData(m_tabmodel->fieldIndex("Sex"),Qt::Horizontal,"性别");
    ui->tableView->setModel(m_tabmodel);
    QSqlRecord testRec=m_tabmodel->record(0);
    qDebug()<<testRec.value(1);
    testRec.setValue(1,444555.1);
    m_tabmodel->submitAll();
    qDebug()<<testRec.value(1);
}
