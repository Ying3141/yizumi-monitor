#ifndef HSQUALITYCONFIG_H
#define HSQUALITYCONFIG_H

#include <QWidget>

namespace Ui {
class HsQualityConfig;
}

class HsQualityConfig : public QWidget
{
    Q_OBJECT

public:
    explicit HsQualityConfig(QWidget *parent = nullptr);
    ~HsQualityConfig();

private slots:
    void on_addNode_clicked();
    void on_delNode_clicked();
    void on_confirm_clicked();
    void on_cancel_clicked();

private:
    void initializeView();

signals:
    void updateView();

private:
    Ui::HsQualityConfig *ui;
};

#endif // HSQUALITYCONFIG_H





