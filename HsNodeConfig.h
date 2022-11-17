#ifndef HSDATANODE_H
#define HSDATANODE_H

#include <QWidget>
#include <HsDataBase.h>

namespace Ui {
class HsNodeConfig;
}

class HsNodeConfig : public QWidget
{
    Q_OBJECT

public:
    explicit HsNodeConfig(QWidget *parent = nullptr);
    ~HsNodeConfig();

    HsDataBase *getDataBase();
    QString getTableName();

private slots:
    void on_addNode_clicked();
    void on_delNode_clicked();
    void on_confirm_clicked();
    void on_cancel_clicked();

private:
    void initializeView();
    void CreateDataBase();

signals:
    void updateView();

private:
    Ui::HsNodeConfig *ui;

    HsDataBase *DB;
    QString m_tablename;
};

#endif // HSDATANODE_H
