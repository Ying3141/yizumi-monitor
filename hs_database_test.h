#ifndef HS_DATABASE_TEST_H
#define HS_DATABASE_TEST_H

#include <QWidget>
#include <QtSql>
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class hs_DataBase_test;
}

class hs_DataBase_test : public QWidget
{
    Q_OBJECT

public:
    explicit hs_DataBase_test(QWidget *parent = nullptr);
    ~hs_DataBase_test();
    void opentable();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::hs_DataBase_test *ui;
    QSqlDatabase DB;
    QSqlTableModel *m_tabmodel=nullptr;
};

#endif // HS_DATABASE_TEST_H
