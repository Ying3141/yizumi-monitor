#ifndef HSANALYSIS_H
#define HSANALYSIS_H

#include <QWidget>

namespace Ui {
class HsAnalysis;
}

class HsAnalysis : public QWidget
{
    Q_OBJECT

public:
    explicit HsAnalysis(QWidget *parent = nullptr);
    ~HsAnalysis();

private:
    Ui::HsAnalysis *ui;
};

#endif // HSANALYSIS_H
