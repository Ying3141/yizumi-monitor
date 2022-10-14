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
    DB.setDatabaseName("test..db3");
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
    m_tabmodel->setTable ("testTable");
    m_tabmodel->setSort(m_tabmodel->fieldIndex("Name"),Qt::AscendingOrder);
    m_tabmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_tabmodel->select();
    m_tabmodel->setHeaderData(m_tabmodel->fieldIndex("Name"),Qt::Horizontal,"姓名");
    m_tabmodel->setHeaderData(m_tabmodel->fieldIndex("Age"),Qt::Horizontal,"年龄");
    m_tabmodel->setHeaderData(m_tabmodel->fieldIndex("Sex"),Qt::Horizontal,"性别");
    ui->tableView->setModel(m_tabmodel);
    QSqlRecord testRec=m_tabmodel->record(0);
    qDebug()<<testRec.value("Age").toInt();

}

void hs_DataBase_test::on_pushButton_3_clicked()
{
    QSqlRecord testRec=m_tabmodel->record(0);
    QVariant var(QVariant::Int);
    var.setValue(55);
    testRec.setValue("Age",var);
    m_tabmodel->setRecord(0,testRec);
}


void hs_DataBase_test::on_pushButton_4_clicked()
{
    m_tabmodel->insertRows(m_tabmodel->rowCount(),1);
    m_tabmodel->setData(m_tabmodel->index(m_tabmodel->rowCount()-1,0),"nnmmaaee");
    m_tabmodel->setData(m_tabmodel->index(m_tabmodel->rowCount()-1,1),144);
    m_tabmodel->setData(m_tabmodel->index(m_tabmodel->rowCount()-1,2),166);
}

void hs_DataBase_test::on_pushButton_5_clicked()
{
    m_tabmodel->submitAll();
}
