#ifndef HSDATABASE_H
#define HSDATABASE_H

#include <QWidget>
#include <QtSql>
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class HsDataBase;
}

class HsDataBase : public QWidget
{
    Q_OBJECT

public:
    explicit HsDataBase(QString name,QWidget *parent = nullptr);
    ~HsDataBase();

public:
    void create_new_table(QString SQL);
    void add_column(QString SQL);
    void add_record(QString tablename,int colnum,double var);

private:
    Ui::HsDataBase *ui;
    QSqlDatabase DB;
    QSqlTableModel *m_tabmodel=nullptr;
};


#endif // HSDATABASE_H





