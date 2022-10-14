#include "hs_corelatecof.h"
#include "ui_hs_corelatecof.h"

Hs_CorelateCOF::Hs_CorelateCOF(QVector<hs_node*>&nodes,QTableWidget *table,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hs_CorelateCOF)
{
    ui->setupUi(this);
    m_nodes=&nodes;
    setStyleSheet("QWidget{background: white;}");
}

Hs_CorelateCOF::~Hs_CorelateCOF()
{
    delete ui;
}

double Hs_CorelateCOF::cal_COEF(QVector<double> &data_series_A, QVector<double> &data_series_B)
{
    if(data_series_A.size()!=data_series_B.size())
    {
        return 0;
    }

    double sumA(0.0), sumB(0.0), aveA(0.0), aveB(0.0);
    int Length=data_series_A.size();
    //求和
    sumA = std::accumulate(data_series_A.begin(), data_series_A.end(), 0.0);
    sumB = std::accumulate(data_series_B.begin(), data_series_B.end(), 0.0);

    //求平均值
    aveA = sumA / double(Length);
    aveB = sumB / double(Length);

    //计算相关系数
    double R1(0), R2(0), R3(0);
    for (long i = 0; i < Length; i++)
    {
        R1 += (data_series_A[i] - aveA) * (data_series_B[i] - aveB);
        R2 += pow((data_series_A[i] - aveA), 2);
        R3 += pow((data_series_B[i] - aveB), 2);
    }

    return (R1 / sqrt(R2*R3));
}

void Hs_CorelateCOF::add_display_part()
{
    if(m_models.size()>=4)
        return;
    Hs_CoRelateCOEFModel *model1=new Hs_CoRelateCOEFModel(m_nodes);
    Hs_CoRelateCOEFModel *model2=new Hs_CoRelateCOEFModel(m_nodes);
    Hs_CoRelateCOEFModel *model3=new Hs_CoRelateCOEFModel(m_nodes);
    Hs_CoRelateCOEFModel *model4=new Hs_CoRelateCOEFModel(m_nodes);
    m_models.push_back(model1);
    m_models.push_back(model2);
    m_models.push_back(model3);
    m_models.push_back(model4);
    ui->verticalLayout->insertWidget(1,model1);
    ui->verticalLayout->insertWidget(2,model2);
    ui->verticalLayout->insertWidget(3,model3);
    ui->verticalLayout->insertWidget(4,model4);
}

