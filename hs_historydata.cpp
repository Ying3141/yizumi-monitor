#include "hs_historydata.h"
#include "ui_hs_historydata.h"

Hs_HistoryData::Hs_HistoryData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hs_HistoryData)
{
    ui->setupUi(this);
    initialize();
    initializeCombobox();
}

Hs_HistoryData::~Hs_HistoryData()
{
    delete ui;
}

void Hs_HistoryData::initialize()
{
    //初始化表格
    m_Chart = new QChart();

    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0,200);  //设置X坐标范围
    axisX->setTitleText("模次"); //设置X坐标名字

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(-50,50);  //设置Y坐标范围
    axisY->setTitleText("值");  //设置Y坐标名字

    m_Chart->addAxis(axisX, Qt::AlignBottom);  //并且XY轴的位置是上和右
    m_Chart->addAxis(axisY, Qt::AlignLeft);
    ui->graphicsView->setChart(m_Chart);

    m_vlayout=new QVBoxLayout(ui->select_widget);
    m_vlayout->addStretch();

    //初始化数据库
    m_DB = QSqlDatabase::addDatabase("QSQLITE");
    m_DB.setDatabaseName("./yizumi..db3");
    if(!m_DB.open())
    {
        QMessageBox::warning(this,"错误","数据库创建/打开失败",QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }
}

void Hs_HistoryData::initializeCombobox()
{
    //根据数据库中表格，初始化选择框
    QStringList tables = m_DB.tables();
    ui->data_select_combobox->addItems(tables);
}

void Hs_HistoryData::on_data_select_combobox_currentIndexChanged(const QString &arg1)
{
    m_model=new QSqlTableModel(this,m_DB);
    m_model->setTable(arg1);
    QSqlRecord testRec=m_model->record();
    remove_checkbox();
    for(int i=1;i<testRec.count();i++)
    {
        qDebug()<<testRec.fieldName(i);
        add_checkbox(testRec.fieldName(i));
    }
}

void Hs_HistoryData::add_checkbox(QString name)
{
    QCheckBox *checkbox=new QCheckBox(ui->select_widget);
    checkbox->setText(name);
    m_checkbox_vector.push_back(checkbox);
    m_map.insert(checkbox,m_map.size());
    m_vlayout->insertWidget(m_checkbox_vector.size()-1,checkbox);
    connect(checkbox,SIGNAL(stateChanged(int)),this,SLOT(on_checkbox_checked(int)));
}

void Hs_HistoryData::remove_checkbox()
{
    //释放所有checkbox
    while(m_map.size()!=0)
    {
        m_checkbox_vector[0]->setParent(NULL);
        m_checkbox_vector[0]=nullptr;
        m_checkbox_vector.remove(0);
        m_map.clear();
    }
}

void Hs_HistoryData::on_checkbox_checked(int i)
{
    QCheckBox *sender_checkbox=dynamic_cast<QCheckBox*>(sender());
    int index=m_map[sender_checkbox];

    QString name = m_model->data(m_model->index(2,1)).toString();
          qDebug()<<"name +"<<name;

    QLineSeries *series = new QLineSeries();//实例化一个QLineSeries对象
    //设置线条名称
    series->setName(QString("line " + QString::number(1)));

    //设置线条颜色，如果不设置会给默认颜色
    series->setColor(QColor(255,0,255));

    //设置是否线条可视
    series->setVisible(true);

    //点标签是否可视
    series->setPointLabelsVisible(true);

    //点标签颜色
    series->setPointLabelsColor(QColor(255,255,255));

    //点标签字体
    series->setPointLabelsFont(QFont("微软雅黑"));

    //设置点标签显示格式
    series->setPointLabelsFormat("(@xPoint,@yPoint)");

    //是否切割边缘点标签，默认为true
    series->setPointLabelsClipping(false);

    //设置点标签是否可视
    series->setPointsVisible(true);
    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);
    m_Chart->addSeries(series);
    ui->graphicsView->setChart(m_Chart);
}
