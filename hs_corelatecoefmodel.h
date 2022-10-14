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

private:
    void initialize();

private:
    Ui::Hs_CoRelateCOEFModel *ui;
    QVector<hs_node*>   *m_nodes;
};

#endif // HS_CORELATECOEFMODEL_H
