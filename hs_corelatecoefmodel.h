#ifndef HS_CORELATECOEFMODEL_H
#define HS_CORELATECOEFMODEL_H

#include <QWidget>
#include "hs_node.h"

namespace Ui {
class Hs_CoRelateCOEFModel;
}

class Hs_CoRelateCOEFModel : public QWidget
{
    Q_OBJECT

public:
    explicit Hs_CoRelateCOEFModel(QVector<hs_node*>*nodes,QWidget *parent = nullptr);
    ~Hs_CoRelateCOEFModel();
    void setLineedit(double);

private:
    void initialize();

private:
    Ui::Hs_CoRelateCOEFModel *ui;
    QVector<hs_node*>   *m_nodes;

signals:
    void index_changed(int);
private slots:
    void on_paraeter_select_currentIndexChanged(int index);
};

#endif // HS_CORELATECOEFMODEL_H
