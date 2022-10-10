#ifndef HS_ANALYSE_H
#define HS_ANALYSE_H

#include <QWidget>
#include <QTableWidget>

namespace Ui {
class Hs_analyse;
}

class Hs_analyse : public QWidget
{
    Q_OBJECT

public:
    explicit Hs_analyse(QWidget *parent = nullptr);
    ~Hs_analyse();

private:
    Ui::Hs_analyse *ui;
    QTableWidget *table;
};

#endif // HS_ANALYSE_H
