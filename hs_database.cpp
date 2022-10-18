#include "hs_database.h"
#include "ui_hs_database.h"

Hs_Database::Hs_Database(QString name,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hs_Database)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TransparentForMouseEvents,true);

    DB=QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName(name);
    if(!DB.open())
    {
        QMessageBox::warning(this,"错误","数据库创建/打开失败",QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }
}

Hs_Database::~Hs_Database()
{
    delete ui;
}

void Hs_Database::create_new_table(QString SQL)
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

void Hs_Database::add_column(QString SQL)
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

void Hs_Database::add_record(QString tablename,int colnum,double var)
{
    m_tabmodel=new QSqlTableModel(this,DB);
    m_tabmodel->setTable (tablename);
    m_tabmodel->setSort(m_tabmodel->fieldIndex("MoldCount"),Qt::AscendingOrder);
    m_tabmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_tabmodel->select();

    m_tabmodel->insertRows(m_tabmodel->rowCount(),1);
    m_tabmodel->setData(m_tabmodel->index(m_tabmodel->rowCount()-1,colnum),var);
    m_tabmodel->submitAll();
}
