#include "HsDataBase.h"
#include "ui_HsDataBase.h"

HsDataBase::HsDataBase(QString name,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HsDataBase)
{
    this->setAttribute(Qt::WA_TransparentForMouseEvents,true);

    DB=QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName(name);
    if(!DB.open())
    {
        QMessageBox::warning(this,"错误","数据库创建/打开失败",QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }
}

HsDataBase::~HsDataBase()
{
    delete ui;
}

void HsDataBase::create_new_table(QString SQL)
{
    QSqlQuery sql_query;

    if(!sql_query.exec(SQL))
        {
            qDebug() << "Error: Fail to create table." << sql_query.lastError();
        }
        else
        {
            qDebug() << "Table created!";
        }
}

void HsDataBase::add_column(QString SQL)
{
    QSqlQuery sql_query;

    if(!sql_query.exec(SQL))
        {
            qDebug() << "Error: Fail to add column." << sql_query.lastError();
        }
        else
        {
            qDebug() << "Column added!";
        }
}

void HsDataBase::add_record(int colnum,QVariant var)
{
    m_tabmodel->setData(m_tabmodel->index(m_tabmodel->rowCount()-1,colnum),var);
}

void HsDataBase::submitAll()
{
    m_tabmodel->submitAll();
}

void HsDataBase::add_row(QString tablename)
{
    m_tabmodel=new QSqlTableModel(this,DB);
    m_tabmodel->setTable (tablename);
//    m_tabmodel->setSort(m_tabmodel->fieldIndex("MoldCount"),Qt::AscendingOrder);
    m_tabmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_tabmodel->select();
    m_tabmodel->insertRows(m_tabmodel->rowCount(),1);
}
