#ifndef HS_DATABASE_H
#define HS_DATABASE_H

#include <QWidget>
#include <QtSql>
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class Hs_Database;
}

class Hs_Database : public QWidget
{
    Q_OBJECT

public:
    explicit Hs_Database(QString name,QWidget *parent = nullptr);
    ~Hs_Database();

public:
    void create_new_table(QString SQL);
    void add_column(QString SQL);
    void add_record(QString tablename,int colnum,double var);

private:
    Ui::Hs_Database *ui;
    QSqlDatabase DB;
    QSqlTableModel *m_tabmodel=nullptr;
};

#endif // HS_DATABASE_H
