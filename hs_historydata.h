#ifndef HS_HISTORYDATA_H
#define HS_HISTORYDATA_H

#include <QWidget>
#include <QtCharts>
#include <QChartView>
#include <QSplineSeries>
#include <QtSql>
#include <QLayout>
QT_CHARTS_USE_NAMESPACE

namespace Ui {
class Hs_HistoryData;
}

class Hs_HistoryData : public QWidget
{
    Q_OBJECT

public:
    explicit Hs_HistoryData(QWidget *parent = nullptr);
    ~Hs_HistoryData();

    void add_checkbox(QString name);
    void remove_checkbox();
    void update_widget();

private slots:
    void on_data_select_combobox_currentIndexChanged(const QString &arg1);
    void on_checkbox_checked(int);

private:
    Ui::Hs_HistoryData      *ui;
    QChart                  *m_Chart=nullptr;
    QChartView              *m_chartview=nullptr;
    QSqlDatabase            m_DB;
    QSqlTableModel          *m_model=nullptr;
    QVector<QCheckBox*>     m_checkbox_vector;
    QVBoxLayout             *m_vlayout=nullptr;
    QMap<QCheckBox*,int>    m_map;

private:
    void initialize();
    void initializeCombobox();
};

#endif // HS_HISTORYDATA_H
