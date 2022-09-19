#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
//    raw_data(new double[1250100]),
    m_demodulation(new demodulation(this)),
    m_temp_distance_save(new Temp_distance_save(m_demodulation)),
    m_udp_recv(new udp_recv(this)),
    m_udp_send(new udp_send(this))
//    m_hextodec(new HEXtoDEC(m_udp_recv))
{
    ui->setupUi(this);

    read_config();

//    set_style_sheet();

//    set_background_image();

    setWindowTitle(APP_TITLE);

    init_widget_temp_distance();
//    init_widget_max_temp();

    //定义定时器
    Temp_Display_Timer = new QTimer(); // 温度-距离波形图显示计时器
    Temp_Display_Timer->setTimerType(Qt::PreciseTimer);
    Temp_save_Timer = new QTimer(); // 温度-距离波形图存储计时器
    Temp_save_Timer->setTimerType(Qt::PreciseTimer);
    Alarm_Timer = new QTimer();//温度过热报警计时器
    Alarm_Timer->setTimerType(Qt::PreciseTimer);

    //计时器定时响应
    connect(Temp_Display_Timer,&QTimer::timeout,this,&MainWindow::echarts_load_temp);
//    connect(Temp_save_Timer,&QTimer::timeout,this,&MainWindow::Open_Temp_Save_Thread);
//    connect(Alarm_Timer,&QTimer::timeout,this,&MainWindow::start_alarm);
    //线程结束时响应
    connect(m_udp_recv,&udp_recv::finished,this,&MainWindow::FinishUdp_recvThread);
    connect(m_udp_send,&udp_send::finished,this,&MainWindow::FinishUdp_sendThread);
    connect(m_demodulation,&demodulation::finished,this,&MainWindow::FinishDemodulationThread);
    connect(m_temp_distance_save,&Temp_distance_save::finished,this,&MainWindow::FinishTemp_saveThread);

    start_detection();

//    m_udp_send->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::paintEvent(QPaintEvent *){
//    label->resize(this->size());
//}

//读取配置文件
void MainWindow::read_config()
{
    QSettings *settings = new QSettings("C:/Qt_UDP_DTS/config.ini",QSettings::IniFormat);

    //Read
    settings->beginGroup("MAIN");
    int APP_TITLE = settings->value("APP_TITLE","").toInt();
    qDebug()<<"APP_TITLE = "<<APP_TITLE<<endl;
    settings->endGroup();

    settings->beginGroup("RESOURCE");
//    BGD_IMAGE = settings->value("BGD_IMAGE","").toString();
//    qDebug()<<"BGD_IMAGE = "<<BGD_IMAGE<<endl;
    TEMP_DIST_HTML = settings->value("TEMP_DIST_HTML","").toString();
    qDebug()<<"TEMP_DIST_HTML = "<<TEMP_DIST_HTML<<endl;
    STYLE_SHEET = settings->value("STYLE_SHEET","").toString();
    qDebug()<<"STYLE_SHEET = "<<STYLE_SHEET<<endl;
    settings->endGroup();

    settings->beginGroup("DETECTION");
    int ALM_TEMP_THR = settings->value("ALM_TEMP_THR",-1).toInt();
    qDebug()<<"ALM_TEMP_THR = "<<ALM_TEMP_THR<<endl;
    settings->endGroup();

}

//设置qt样式表
void MainWindow::set_style_sheet()
{
    qDebug()<<QDir::currentPath()<<endl;
    QFile file(STYLE_SHEET);
    file.open(QFile::ReadOnly);
    QString styleSheet = tr(file.readAll());
    qApp->setStyleSheet(styleSheet);
}

//设置背景图
//void MainWindow::set_background_image()
//{
//    QPixmap Images(BGD_IMAGE);
//    label = new QLabel(this);
//    label->setScaledContents(true);
//    label->setPixmap(Images);
//    label->lower();
//}



//初始化html
void MainWindow::init_widget_temp_distance()
{
    /*--关联WebEngineView与html文件--*/
    m_temp_distance_widget = ui->temp_distance_widget;
    m_temp_distance_widget->setContextMenuPolicy(Qt::NoContextMenu);
    m_temp_distance_widget->load(QUrl::fromLocalFile(/*QDir::currentPath()+*/TEMP_DIST_HTML));

    //QWebEngineView 在 load 完一个页面后会发出一个已完成的信号,依据 QWebEngineView 的大小来设置 EChart 的大小的
    connect(m_temp_distance_widget,&QWebEngineView::loadFinished,this,&MainWindow::onResizeEcharts5);
}


//echarts加载数据
void MainWindow::echarts_load_temp()
{
    /*------传递Temp[]--------*/
    //1.使用 QJonsObject 来组成一个 JSON 对象
    QJsonObject seriesData;

    //2.使用 QJsonArray 往 JSON 对象中添加一数组
    QJsonArray amplitude;
    for(int i=4; i<128; i++) {
        //如果中心波长的温度值是0 则不画出该点
//        if(m_demodulation->Temp[i]==0) continue;

        //如果温度值太小，则不画出该点
//        if(m_demodulation->Temp[i]<-120) continue;

         //如果温度值>300，则不画出该点
        if(m_demodulation->Temp[i]>250) continue;

        amplitude.push_back(m_demodulation->Temp[i]);
    }
    seriesData.insert("amplitude", amplitude);

    //3.使用 QJsonDocument 来将 JSON 对象转化成字符串
    QString optionStr = QJsonDocument(seriesData).toJson();

    //4.调用js的init2()方法
    QString js = QString("init2(%1)").arg(optionStr);

    //5.调用 QWebEngineView的 page()->runJavaScript("function(str)") 来运行 JS 方法
    m_temp_distance_widget->page()->runJavaScript(js);

    /*--------传递MAX_Temp-------*/
    //1.使用 QJonsObject 来组成一个 JSON 对象
    QJsonObject temp_Obj;

    //2.使用 QJsonArray 往 JSON 对象中添加一数组
    QJsonArray temp_json;
    temp_json.push_back(m_demodulation->MAX_Temp);

    temp_Obj.insert("temperature", temp_json);

    //3.使用 QJsonDocument 来将 JSON 对象转化成字符串
    QString optionStr2 = QJsonDocument(temp_Obj).toJson();

    //4.调用js的load2()方法
    QString js2 = QString("load2(%1)").arg(optionStr2);

    //5.调用 QWebEngineView的 page()->runJavaScript("function(str)") 来运行 JS 方法
    m_temp_distance_widget->page()->runJavaScript(js2);

    /*-------传递template_temp-------*/
    //1.使用 QJonsObject 来组成一个 JSON 对象
    QJsonObject template_temp_obj;

    //2.使用 QJsonArray 往 JSON 对象中添加一数组
    QJsonArray template_temp_json1, template_temp_json2, template_temp_json3,
            template_temp_json4, template_temp_json5;

//    for(int j=2; j<14;j+=3){
//        template_temp_json.push_back(m_demodulation->Temp[j]);
//    }
    template_temp_json1.push_back(m_demodulation->Temp[28]);
    template_temp_json2.push_back(m_demodulation->Temp[3]);
    template_temp_json3.push_back(m_demodulation->Temp[30]);
    template_temp_json4.push_back(m_demodulation->Temp[32]);
    template_temp_json5.push_back(m_demodulation->Temp[8]);

    template_temp_obj.insert("template_temp1", template_temp_json1);
    template_temp_obj.insert("template_temp2", template_temp_json2);
    template_temp_obj.insert("template_temp3", template_temp_json3);
    template_temp_obj.insert("template_temp4", template_temp_json4);
    template_temp_obj.insert("template_temp5", template_temp_json5);

    //3.使用 QJsonDocument 来将 JSON 对象转化成字符串
    QString optionStr3 = QJsonDocument(template_temp_obj).toJson();

    //4.调用js的load3()方法
    QString js3 = QString("load3(%1)").arg(optionStr3);

    //5.调用 QWebEngineView的 page()->runJavaScript("function(str)") 来运行 JS 方法
    m_temp_distance_widget->page()->runJavaScript(js3);

//    //温度过热报警计时
//    if(m_demodulation->MAX_Temp >= ALARM_TEMP_THRESHOLD) start_alarm();
//    else {
//        if(Alarm_Timer->isActive()) Alarm_Timer->stop();
//        alarm_count = 0;
//    }
////    ui->lcd_alarm->display(QString("%1").arg(alarm_count));
}

void MainWindow::Open_Temp_Save_Thread()
{
//    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Start Saving Data! ")+"\n");

    m_temp_distance_save->start();
}

void MainWindow::start_alarm()
{
    alarm_count++;
    //    ui->lcd_alarm->display(QString("%1").arg(alarm_count));
}

//开始接收数据并检测
void MainWindow::start_detection()
{
    //开始接收数据线程
    m_udp_recv->start();

//    QThread::msleep(1000); //延迟ms

//    m_hextodec->start();

//    QThread::msleep(1000); //延迟ms

    //开始解调数据线程
    m_demodulation->start();

    //定时器控制echarts_load_temp()显示 ms
    if(!Temp_Display_Timer->isActive()) Temp_Display_Timer->start(1000);
}


void MainWindow::FinishUdp_recvThread()
{
    m_udp_recv->quit();
    m_udp_recv->wait();
}

void MainWindow::FinishUdp_sendThread()
{
    m_udp_send->quit();
    m_udp_send->wait();
}


void MainWindow::FinishDemodulationThread()
{
    m_demodulation->quit();
    m_demodulation->wait();
}

void MainWindow::FinishTemp_saveThread()
{
    m_temp_distance_save->quit();
    m_temp_distance_save->wait();
}

//自适应窗口变化
void MainWindow::onResizeEcharts5()
{
    isLoaded5 = true;
    QJsonObject sizeData;
    sizeData.insert("width", m_temp_distance_widget->width() - 20);
    sizeData.insert("height", m_temp_distance_widget->height() - 20);
    QString sizeStr = QJsonDocument(sizeData).toJson();
    QString js = QString("setSize(%1)").arg(sizeStr);
    m_temp_distance_widget->page()->runJavaScript(js);
}


//因为我们实现在窗口改变大小时 ECharts 也跟着变化，所以我们要在 resizeEvent 时设置也要设置大小
void MainWindow::resizeEvent(QResizeEvent *event)
{
    if(isLoaded5) onResizeEcharts5();

}

//点击设定最大值法寻峰阈值
//void MainWindow::on_btn_threshold_clicked()
//{
//    m_demodulation->threshold = ui->edit_threshold->text().toInt();

//    QMessageBox::about(this,tr("Attention"),tr("Threshold Set Succeeded!"));
//}

