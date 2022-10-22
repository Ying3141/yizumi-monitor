#ifndef HSDATANODE_H
#define HSDATANODE_H

#include <QWidget>

namespace Ui {
class HsNodeConfig;
}

class HsNodeConfig : public QWidget
{
    Q_OBJECT

public:
    explicit HsNodeConfig(QWidget *parent = nullptr);
    ~HsNodeConfig();

private slots:
    void on_addNode_clicked();

    void on_delNode_clicked();

private:
    void initializeView();

private:
    Ui::HsNodeConfig *ui;
};

#endif // HSDATANODE_H
