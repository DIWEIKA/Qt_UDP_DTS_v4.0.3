#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    //    raw_data(new double[1250100]),
    m_demodulation(new demodulation(this)),
    //    m_temp_distance_save(new Temp_distance_save(m_demodulation)),
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
    connect(Alarm_Timer,&QTimer::timeout,this,&MainWindow::start_alarm);
    //线程结束时响应
    connect(m_udp_recv,&udp_recv::finished,this,&MainWindow::FinishUdp_recvThread);
    connect(m_udp_send,&udp_send::finished,this,&MainWindow::FinishUdp_sendThread);
    connect(m_demodulation,&demodulation::finished,this,&MainWindow::FinishDemodulationThread);
    //    connect(m_temp_distance_save,&Temp_distance_save::finished,this,&MainWindow::FinishTemp_saveThread);

    start_detection();

    //    m_udp_send->start();
}

MainWindow::~MainWindow()
{
    delete ui;
    flash_cnt = 0;
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


//echarts加载数据 1s刷新一次
/**
 * JSON传数据步骤
 * 1.使用 QJonsObject 来组成一个 JSON 对象
 * 2.使用 QJsonArray 往 JSON 对象中添加一数组
 * 3.使用 QJsonDocument 来将 JSON 对象转化成字符串
 * 4.调用js的function()方法
 * 5.调用 QWebEngineView的 page()->runJavaScript("function(str)") 来运行 JS 方法
*/
void MainWindow::echarts_load_temp()
{
    /*------传递波长1的距离-温度曲线--------*/
    QJsonObject dis_temp_obj;
    QJsonArray dis_temp_json1;

    for(int i=0; i<DISNUM; ++i) {
        //如果中心波长的温度值是0 则不画出该点
        //        if(m_demodulation->Temp[i]==0) continue;

        //如果温度值太小，则不画出该点
        //            if(m_demodulation->Temp[i]<30) continue;

        //如果温度值太大，则不画出该点
        //            if(m_demodulation->Temp[i]>250) continue;

        dis_temp_json1.push_back(m_demodulation->Temp_1[i]);
    }
    dis_temp_obj.insert("dis_temp_1", dis_temp_json1);




    /*------传递波长2的距离-温度曲线--------*/
    QJsonObject dis_temp_obj2;
    QJsonArray dis_temp_json2;

    for(int i=0; i<DISNUM; ++i) {
        dis_temp_json2.push_back(m_demodulation->Temp_2[i]);
    }
    dis_temp_obj.insert("dis_temp_2", dis_temp_json2);



    /*------传递波长3的距离-温度曲线--------*/
    QJsonObject dis_temp_obj3;
    QJsonArray dis_temp_json3;

    for(int i=0; i<DISNUM; ++i) {
        dis_temp_json3.push_back(m_demodulation->Temp_3[i]);
    }
    dis_temp_obj.insert("dis_temp_3", dis_temp_json3);


    /*------传递波长4的距离-温度曲线--------*/
    QJsonObject dis_temp_obj4;
    QJsonArray dis_temp_json4;

    for(int i=0; i<DISNUM; ++i) {
        dis_temp_json4.push_back(m_demodulation->Temp_4[i]);
    }
    dis_temp_obj.insert("dis_temp_4", dis_temp_json4);


    /*------传递波长5的距离-温度曲线--------*/
    QJsonObject dis_temp_obj5;
    QJsonArray dis_temp_json5;

    for(int i=0; i<DISNUM; ++i) {
        dis_temp_json5.push_back(m_demodulation->Temp_5[i]);
    }
    dis_temp_obj.insert("dis_temp_5", dis_temp_json5);

    QString dis_temp_str = QJsonDocument(dis_temp_obj).toJson();

    QString dis_temp_js = QString("dis_temp_curve(%1)").arg(dis_temp_str);

    m_temp_distance_widget->page()->runJavaScript(dis_temp_js);


    /*-----------------传递50个温度曲线建模点（分区）----------------*/
        //初始化50个分区的温度为20度
        int Wav1_Temp_1=20,Wav2_Temp_1=20,Wav3_Temp_1=20,Wav4_Temp_1=20,Wav5_Temp_1=20,
            Wav1_Temp_2=20,Wav2_Temp_2=20,Wav3_Temp_2=20,Wav4_Temp_2=20,Wav5_Temp_2=20,
            Wav1_Temp_3=20,Wav2_Temp_3=20,Wav3_Temp_3=20,Wav4_Temp_3=20,Wav5_Temp_3=20,
            Wav1_Temp_4=20,Wav2_Temp_4=20,Wav3_Temp_4=20,Wav4_Temp_4=20,Wav5_Temp_4=20,
            Wav1_Temp_5=20,Wav2_Temp_5=20,Wav3_Temp_5=20,Wav4_Temp_5=20,Wav5_Temp_5=20,
            Wav1_Temp_6=20,Wav2_Temp_6=20,Wav3_Temp_6=20,Wav4_Temp_6=20,Wav5_Temp_6=20,
            Wav1_Temp_7=20,Wav2_Temp_7=20,Wav3_Temp_7=20,Wav4_Temp_7=20,Wav5_Temp_7=20,
            Wav1_Temp_8=20,Wav2_Temp_8=20,Wav3_Temp_8=20,Wav4_Temp_8=20,Wav5_Temp_8=20,
            Wav1_Temp_9=20,Wav2_Temp_9=20,Wav3_Temp_9=20,Wav4_Temp_9=20,Wav5_Temp_9=20,
            Wav1_Temp_A=20,Wav2_Temp_A=20,Wav3_Temp_A=20,Wav4_Temp_A=20,Wav5_Temp_A=20;

        //管理50个温度建模分区
        vector<int> Wav_Temp_all = {
                        Wav1_Temp_1,Wav2_Temp_1,Wav3_Temp_1,Wav4_Temp_1,Wav5_Temp_1,
                        Wav1_Temp_2,Wav2_Temp_2,Wav3_Temp_2,Wav4_Temp_2,Wav5_Temp_2,
                        Wav1_Temp_3,Wav2_Temp_3,Wav3_Temp_3,Wav4_Temp_3,Wav5_Temp_3,
                        Wav1_Temp_4,Wav2_Temp_4,Wav3_Temp_4,Wav4_Temp_4,Wav5_Temp_4,
                        Wav1_Temp_5,Wav2_Temp_5,Wav3_Temp_5,Wav4_Temp_5,Wav5_Temp_5,
                        Wav1_Temp_6,Wav2_Temp_6,Wav3_Temp_6,Wav4_Temp_6,Wav5_Temp_6,
                        Wav1_Temp_7,Wav2_Temp_7,Wav3_Temp_7,Wav4_Temp_7,Wav5_Temp_7,
                        Wav1_Temp_8,Wav2_Temp_8,Wav3_Temp_8,Wav4_Temp_8,Wav5_Temp_8,
                        Wav1_Temp_9,Wav2_Temp_9,Wav3_Temp_9,Wav4_Temp_9,Wav5_Temp_9,
                        Wav1_Temp_A,Wav2_Temp_A,Wav3_Temp_A,Wav4_Temp_A,Wav5_Temp_A
        };

        /**
        根据每条波长-距离曲线进行温度检测，
        若连续一个或多个点大于某一温度，则新建一点k，其横坐标为这些点距离的平均值，纵坐标为这些点温度的均值
        根据biaoding.txt里划分的分区将温度归类，替换某个分区的数据
        根据k的横坐标确定替换哪个分区，根据k的纵坐标替换那个分区的数据
         */

        //波长1

        m_demodulation->Temp_1[1] = 15; //ceshi
//        m_demodulation->Temp_1[5] = 39; //ceshi
//        m_demodulation->Temp_1[6] = 62; //ceshi


        int threshold1 = 30;
        float k_x1=0.0; //新建点k的横坐标
        int k_y1=0; //新建点k的纵坐标
        vector<float> k_x_array_1; //存放所有高温点的横坐标
        vector<int> k_y_array_1; //存放所有高温点的纵坐标
        for(int i=0; i<DISNUM;++i){

            if(m_demodulation->Temp_1[i]>threshold1){

                k_x1 = i*0.4;
                k_y1 = m_demodulation->Temp_1[i];

                for(int j=1;j<DISNUM-i;++j){
                    int tempx = m_demodulation->Temp_1[i+j];
                    if(tempx > threshold1){
                        k_x1 += (i+j)*0.4;
                        if(tempx > k_y1) k_y1 = tempx;
                    }
                    else{
                        k_x_array_1.push_back(k_x1/j);
                        k_y_array_1.push_back(k_y1);
                        i += j; //寻找下一个可能的高温点
                        break;
                    }
                    if(j == DISNUM-i-1){ //若最高温出现在曲线尾部
                        k_x_array_1.push_back(k_x1/j);
                        k_y_array_1.push_back(k_y1);
                        break;
                    }
                }
            }
        }

        //波长2

//        m_demodulation->Temp_2[15] = 50; //ceshi
//        m_demodulation->Temp_2[18] = 39; //ceshi
//        m_demodulation->Temp_2[21] = 63; //ceshi

        int threshold2 = 30;
        float k_x2=0.0;
        int k_y2=0;
        vector<float> k_x_array_2;
        vector<int> k_y_array_2;
        for(int i=0; i<DISNUM;++i){

            if(m_demodulation->Temp_2[i]>threshold2){

                k_x2 = i*0.4;
                k_y2 = m_demodulation->Temp_2[i];

                for(int j=1;j<DISNUM-i;++j){
                    int tempx = m_demodulation->Temp_2[i+j];
                    if(tempx > threshold2){
                        k_x2 += (i+j)*0.4;
                        if(tempx > k_y2) k_y2 = tempx;
                    }
                    else{
                        k_x_array_2.push_back(k_x2/j);
                        k_y_array_2.push_back(k_y2);
                        i += j; //寻找下一个可能的高温点
                        break;
                    }
                    if(j == DISNUM-i-1){ //若最高温出现在曲线尾部
                        k_x_array_2.push_back(k_x2/j);
                        k_y_array_2.push_back(k_y2);
                        break;
                    }
                }
            }
        }

        //波长3
//        m_demodulation->Temp_3[10] = 50; //ceshi
//        m_demodulation->Temp_3[21] = 39; //ceshi
//        m_demodulation->Temp_3[24] = 63; //ceshi

        int threshold3 = 30;
        float k_x3=0.0;
        int k_y3=0;
        vector<float> k_x_array_3;
        vector<int> k_y_array_3;
        for(int i=0; i<DISNUM;++i){

            if(m_demodulation->Temp_3[i]>threshold3){

                k_x3 = i*0.4;
                k_y3 = m_demodulation->Temp_3[i];

                for(int j=1;j<DISNUM-i;++j){
                    int tempx = m_demodulation->Temp_3[i+j];
                    if(tempx > threshold3){
                        k_x3 += (i+j)*0.4;
                        if(tempx > k_y3) k_y3 = tempx;
                    }
                    else{
                        k_x_array_3.push_back(k_x3/j);
                        k_y_array_3.push_back(k_y3);
                        i += j; //寻找下一个可能的高温点
                        break;
                    }
                    if(j == DISNUM-i-1){ //若最高温出现在曲线尾部
                        k_x_array_3.push_back(k_x3/j);
                        k_y_array_3.push_back(k_y3);
                        break;
                    }
                }
            }
        }

        //波长4
        int threshold4 = 30;
        float k_x4=0.0;
        int k_y4=0;
        vector<float> k_x_array_4;
        vector<int> k_y_array_4;
        for(int i=0; i<DISNUM;++i){

            if(m_demodulation->Temp_4[i]>threshold4){

                k_x4 = i*0.4;
                k_y4 = m_demodulation->Temp_4[i];

                for(int j=1;j<DISNUM-i;++j){
                    int tempx = m_demodulation->Temp_4[i+j];
                    if(tempx > threshold4){
                        k_x4 += (i+j)*0.4;
                        if(tempx > k_y4) k_y4 = tempx;
                    }
                    else{
                        k_x_array_4.push_back(k_x4/j);
                        k_y_array_4.push_back(k_y4);
                        i += j; //寻找下一个可能的高温点
                        break;
                    }
                    if(j == DISNUM-i-1){ //若最高温出现在曲线尾部
                        k_x_array_4.push_back(k_x4/j);
                        k_y_array_4.push_back(k_y4);
                        break;
                    }
                }
            }
        }

        //波长5
        int threshold5 = 30;
        float k_x5=0.0;
        int k_y5=0;
        vector<float> k_x_array_5;
        vector<int> k_y_array_5;
        for(int i=0; i<DISNUM;++i){

            if(m_demodulation->Temp_5[i]>threshold5){

                k_x5 = i*0.4;
                k_y5 = m_demodulation->Temp_5[i];

                for(int j=1;j<DISNUM-i;++j){
                    int tempx = m_demodulation->Temp_5[i+j];
                    if(tempx > threshold5){
                        k_x5 += (i+j)*0.4;
                        if(tempx > k_y5) k_y5 = tempx;
                    }
                    else{
                        k_x_array_5.push_back(k_x5/j);
                        k_y_array_5.push_back(k_y5);
                        i += j; //寻找下一个可能的高温点
                        break;
                    }
                    if(j == DISNUM-i-1){ //若最高温出现在曲线尾部
                        k_x_array_5.push_back(k_x5/j);
                        k_y_array_5.push_back(k_y5);
                        break;
                    }
                }
            }
        }



    /*-------------------50个分区，按标定位置划分-----------------*/
//       lambda11->(0,1] lambda12->(1,2] lambda13->(2,3] lambda14->(3,4] lambda15->(4,5] lambda16->(5,6] lambda17->(6,7] lambda18->(7,8] lambda19->(8,9] lambda1A->(9,A]
//       lambda11->(0.2,1.2] lambda22->(1.2,2.2] lambda23->(2.2,3.2] lambda24->(3.2,4.2] lambda25->(4.2,5.2] lambda26->(5.2,6.2] lambda27->(6.2,7.2] lambda28->(7.2,8.2] lambda29->(8.2,9.2] lambda2A->(9.2,A.2]
//       lambda11->(0.4,1.4] lambda32->(1.4,2.4] lambda33->(2.4,3.4] lambda34->(3.4,4.4] lambda35->(4.4,5.4] lambda36->(5.4,6.4] lambda37->(6.4,7.4] lambda38->(7.4,8.4] lambda39->(8.4,9.4] lambda3A->(9.4,A.4]
//       lambda11->(0.6,1.6] lambda42->(1.6,2.6] lambda43->(2.6,3.6] lambda44->(3.6,4.6] lambda45->(4.6,5.6] lambda46->(5.6,6.6] lambda47->(6.6,7.6] lambda48->(7.6,8.6] lambda49->(8.6,9.6] lambda4A->(9.6,A.6]
//       lambda11->(0.8,1.8] lambda52->(1.8,2.8] lambda53->(2.8,3.8] lambda54->(3.8,4.8] lambda55->(4.8,5.8] lambda56->(5.8,6.8] lambda57->(6.8,7.8] lambda58->(7.8,8.8] lambda59->(8.8,9.8] lambda5A->(9.8,A.8]

      //波长1
      size_t size1 = k_x_array_1.size();
      for(size_t i=0; i<size1; ++i){
          float dis = k_x_array_1[i];
          int tmp = k_y_array_1[i];
          if(dis > 0 && dis <= 1) Wav1_Temp_1 = tmp;
          if(dis > 1 && dis <= 2) Wav1_Temp_2 = tmp;
          if(dis > 2 && dis <= 3) Wav1_Temp_3 = tmp;
          if(dis > 3 && dis <= 4) Wav1_Temp_4 = tmp;
          if(dis > 4 && dis <= 5) Wav1_Temp_5= tmp;
          if(dis > 5 && dis <= 6) Wav1_Temp_6= tmp;
          if(dis > 6 && dis <= 7) Wav1_Temp_7= tmp;
          if(dis > 7 && dis <= 8) Wav1_Temp_8= tmp;
          if(dis > 8 && dis <= 9) Wav1_Temp_9= tmp;
          if(dis > 9 && dis <= 10) Wav1_Temp_A= tmp;
      }

      //波长2
      size_t size2 = k_x_array_2.size();
      for(size_t i=0; i<size2; ++i){
          float dis = k_x_array_2[i];
          int tmp = k_y_array_2[i];
          if(dis > 0.2 && dis <= 1.2) Wav2_Temp_1= tmp;
          if(dis > 1.2 && dis <= 2.2) Wav2_Temp_2= tmp;
          if(dis > 2.2 && dis <= 3.2) Wav2_Temp_3 = tmp;
          if(dis > 3.2 && dis <= 4.2) Wav2_Temp_4 = tmp;
          if(dis > 4.2 && dis <= 5.2) Wav2_Temp_5 = tmp;
          if(dis > 5.2 && dis <= 6.2) Wav2_Temp_6 = tmp;
          if(dis > 6.2 && dis <= 7.2) Wav2_Temp_7 = tmp;
          if(dis > 7.2 && dis <= 8.2) Wav2_Temp_8 = tmp;
          if(dis > 8.2 && dis <= 9.2) Wav2_Temp_9 = tmp;
          if(dis > 9.2 && dis <= 10.2) Wav2_Temp_A = tmp;
      }

      //波长3
      size_t size3 = k_x_array_3.size();
      for(size_t i=0; i<size3; ++i){
          float dis = k_x_array_3[i];
          int tmp = k_y_array_3[i];
          if(dis > 0.4 && dis <= 1.4) Wav3_Temp_1= tmp;
          if(dis > 1.4 && dis <= 2.4) Wav3_Temp_2= tmp;
          if(dis > 2.4 && dis <= 3.4) Wav3_Temp_3 = tmp;
          if(dis > 3.4 && dis <= 4.4) Wav3_Temp_4 = tmp;
          if(dis > 4.4 && dis <= 5.4) Wav3_Temp_5 = tmp;
          if(dis > 5.4 && dis <= 6.4) Wav3_Temp_6 = tmp;
          if(dis > 6.4 && dis <= 7.4) Wav3_Temp_7 = tmp;
          if(dis > 7.4 && dis <= 8.4) Wav3_Temp_8 = tmp;
          if(dis > 8.4 && dis <= 9.4) Wav3_Temp_9 = tmp;
          if(dis > 9.4 && dis <= 10.4) Wav3_Temp_A = tmp;
      }

      //波长4
      size_t size4 = k_x_array_4.size();
      for(size_t i=0; i<size4; ++i){
          float dis = k_x_array_4[i];
          int tmp = k_y_array_4[i];
          if(dis > 0.6 && dis <= 1.6) Wav4_Temp_1= tmp;
          if(dis > 1.6 && dis <= 2.6) Wav4_Temp_2= tmp;
          if(dis > 2.6 && dis <= 3.6) Wav4_Temp_3 = tmp;
          if(dis > 3.6 && dis <= 4.6) Wav4_Temp_4 = tmp;
          if(dis > 4.6 && dis <= 5.6) Wav4_Temp_5 = tmp;
          if(dis > 5.6 && dis <= 6.6) Wav4_Temp_6 = tmp;
          if(dis > 6.6 && dis <= 7.6) Wav4_Temp_7 = tmp;
          if(dis > 7.6 && dis <= 8.6) Wav4_Temp_8 = tmp;
          if(dis > 8.6 && dis <= 9.6) Wav4_Temp_9 = tmp;
          if(dis > 9.6 && dis <= 10.6) Wav4_Temp_A = tmp;
      }

      //波长5
      size_t size5 = k_x_array_5.size();
      for(size_t i=0; i<size5; ++i){
          float dis = k_x_array_5[i];
          int tmp = k_y_array_5[i];
          if(dis > 0.8 && dis <= 1.8) Wav5_Temp_1= tmp;
          if(dis > 1.8 && dis <= 2.8) Wav5_Temp_2= tmp;
          if(dis > 2.8 && dis <= 3.8) Wav5_Temp_3 = tmp;
          if(dis > 3.8 && dis <= 4.8) Wav5_Temp_4 = tmp;
          if(dis > 4.8 && dis <= 5.8) Wav5_Temp_5 = tmp;
          if(dis > 5.8 && dis <= 6.8) Wav5_Temp_6 = tmp;
          if(dis > 6.8 && dis <= 7.8) Wav5_Temp_7 = tmp;
          if(dis > 7.8 && dis <= 8.8) Wav5_Temp_8 = tmp;
          if(dis > 8.8 && dis <= 9.8) Wav5_Temp_9 = tmp;
          if(dis > 9.8 && dis <= 10.8) Wav5_Temp_A = tmp;
      }
//    Wav1_Temp_1 = m_demodulation->Temp_1[23];Wav2_Temp_1 = m_demodulation->Temp_2[23];Wav3_Temp_1 = m_demodulation->Temp_3[23];Wav4_Temp_1 = m_demodulation->Temp_4[23];Wav5_Temp_1 = m_demodulation->Temp_5[23];
//    Wav1_Temp_2 = m_demodulation->Temp_1[4];Wav2_Temp_2 = m_demodulation->Temp_2[4];Wav3_Temp_2 = m_demodulation->Temp_3[5];Wav4_Temp_2 = m_demodulation->Temp_4[5];Wav5_Temp_2 = m_demodulation->Temp_5[6];
//    Wav1_Temp_3 = m_demodulation->Temp_1[6];Wav2_Temp_3 = m_demodulation->Temp_2[7];Wav3_Temp_3 = m_demodulation->Temp_3[7];Wav4_Temp_3 = m_demodulation->Temp_4[8];Wav5_Temp_3 = m_demodulation->Temp_5[8];
//    Wav1_Temp_4 = m_demodulation->Temp_1[9];Wav2_Temp_4 = m_demodulation->Temp_2[10];Wav3_Temp_4 = m_demodulation->Temp_3[10];Wav4_Temp_4 = m_demodulation->Temp_4[10];Wav5_Temp_4 = m_demodulation->Temp_5[11];
//    Wav1_Temp_5 = m_demodulation->Temp_1[12];Wav2_Temp_5 = m_demodulation->Temp_2[12];Wav3_Temp_5 = m_demodulation->Temp_3[12];Wav4_Temp_5 = m_demodulation->Temp_4[13];Wav5_Temp_5 = m_demodulation->Temp_5[13];
//    Wav1_Temp_6 = m_demodulation->Temp_1[14];Wav2_Temp_6 = m_demodulation->Temp_2[14];Wav3_Temp_6 = m_demodulation->Temp_3[15];Wav4_Temp_6 = m_demodulation->Temp_4[15];Wav5_Temp_6 = m_demodulation->Temp_5[16];
//    Wav1_Temp_7 = m_demodulation->Temp_1[16];Wav2_Temp_7 = m_demodulation->Temp_2[17];Wav3_Temp_7 = m_demodulation->Temp_3[17];Wav4_Temp_7 = m_demodulation->Temp_4[17];Wav5_Temp_7 = m_demodulation->Temp_5[18];
//    Wav1_Temp_8 = m_demodulation->Temp_1[18];Wav2_Temp_8 = m_demodulation->Temp_2[18];Wav3_Temp_8 = m_demodulation->Temp_3[19];Wav4_Temp_8 = m_demodulation->Temp_4[20];Wav5_Temp_8 = m_demodulation->Temp_5[20];
//    Wav1_Temp_9 = m_demodulation->Temp_1[20];Wav2_Temp_9 = m_demodulation->Temp_2[21];Wav3_Temp_9 = m_demodulation->Temp_3[21];Wav4_Temp_9 = m_demodulation->Temp_4[22];Wav5_Temp_9 = m_demodulation->Temp_5[22];
//    Wav1_Temp_A = m_demodulation->Temp_1[23];Wav2_Temp_A = m_demodulation->Temp_2[23];Wav3_Temp_A = m_demodulation->Temp_3[23];Wav4_Temp_A = m_demodulation->Temp_4[25];Wav5_Temp_A = m_demodulation->Temp_5[25];


    //save history temperature
    v_his_temp11.push_back(Wav1_Temp_1);
    v_his_temp21.push_back(Wav2_Temp_1);
    v_his_temp31.push_back(Wav3_Temp_1);
    v_his_temp41.push_back(Wav4_Temp_1);
    v_his_temp51.push_back(Wav5_Temp_1);
    v_his_temp12.push_back(Wav1_Temp_2);
    v_his_temp22.push_back(Wav2_Temp_2);
    v_his_temp32.push_back(Wav3_Temp_2);
    v_his_temp42.push_back(Wav4_Temp_2);
    v_his_temp52.push_back(Wav5_Temp_2);
    v_his_temp13.push_back(Wav1_Temp_3);
    v_his_temp23.push_back(Wav2_Temp_3);
    v_his_temp33.push_back(Wav3_Temp_3);
    v_his_temp43.push_back(Wav4_Temp_3);
    v_his_temp53.push_back(Wav5_Temp_3);
    v_his_temp14.push_back(Wav1_Temp_4);
    v_his_temp24.push_back(Wav2_Temp_4);
    v_his_temp34.push_back(Wav3_Temp_4);
    v_his_temp44.push_back(Wav4_Temp_4);
    v_his_temp54.push_back(Wav5_Temp_4);
    v_his_temp15.push_back(Wav1_Temp_5);
    v_his_temp25.push_back(Wav2_Temp_5);
    v_his_temp35.push_back(Wav3_Temp_5);
    v_his_temp45.push_back(Wav4_Temp_5);
    v_his_temp55.push_back(Wav5_Temp_5);
    v_his_temp16.push_back(Wav1_Temp_6);
    v_his_temp26.push_back(Wav2_Temp_6);
    v_his_temp36.push_back(Wav3_Temp_6);
    v_his_temp46.push_back(Wav4_Temp_6);
    v_his_temp56.push_back(Wav5_Temp_6);
    v_his_temp17.push_back(Wav1_Temp_7);
    v_his_temp27.push_back(Wav2_Temp_7);
    v_his_temp37.push_back(Wav3_Temp_7);
    v_his_temp47.push_back(Wav4_Temp_7);
    v_his_temp57.push_back(Wav5_Temp_7);
    v_his_temp18.push_back(Wav1_Temp_8);
    v_his_temp28.push_back(Wav2_Temp_8);
    v_his_temp38.push_back(Wav3_Temp_8);
    v_his_temp48.push_back(Wav4_Temp_8);
    v_his_temp58.push_back(Wav5_Temp_8);
    v_his_temp19.push_back(Wav1_Temp_9);
    v_his_temp29.push_back(Wav2_Temp_9);
    v_his_temp39.push_back(Wav3_Temp_9);
    v_his_temp49.push_back(Wav4_Temp_9);
    v_his_temp59.push_back(Wav5_Temp_9);
    v_his_temp1A.push_back(Wav1_Temp_A);
    v_his_temp2A.push_back(Wav2_Temp_A);
    v_his_temp3A.push_back(Wav3_Temp_A);
    v_his_temp4A.push_back(Wav4_Temp_A);
    v_his_temp5A.push_back(Wav5_Temp_A);

    double r11,r21,r31,r41,r51,
            r12,r22,r32,r42,r52,
            r13,r23,r33,r43,r53,
            r14,r24,r34,r44,r54,
            r15,r25,r35,r45,r55,
            r16,r26,r36,r46,r56,
            r17,r27,r37,r47,r57,
            r18,r28,r38,r48,r58,
            r19,r29,r39,r49,r59,
            r1A,r2A,r3A,r4A,r5A;

    int temp_cnt = flash_cnt-10; //10s时间段的温升率
    if(temp_cnt>=0){
        r11 = 1.0*(Wav1_Temp_1-v_his_temp11[temp_cnt])/10;
        r21 = 1.0*(Wav2_Temp_1-v_his_temp21[temp_cnt])/10;
        r31 = 1.0*(Wav3_Temp_1-v_his_temp31[temp_cnt])/10;
        r41 = 1.0*(Wav4_Temp_1-v_his_temp41[temp_cnt])/10;
        r51 = 1.0*(Wav5_Temp_1-v_his_temp51[temp_cnt])/10;
        r12 = 1.0*(Wav1_Temp_2-v_his_temp12[temp_cnt])/10;
        r22 = 1.0*(Wav2_Temp_2-v_his_temp22[temp_cnt])/10;
        r32 = 1.0*(Wav3_Temp_2-v_his_temp32[temp_cnt])/10;
        r42 = 1.0*(Wav4_Temp_2-v_his_temp42[temp_cnt])/10;
        r52 = 1.0*(Wav5_Temp_2-v_his_temp52[temp_cnt])/10;
        r13 = 1.0*(Wav1_Temp_3-v_his_temp13[temp_cnt])/10;
        r23 = 1.0*(Wav2_Temp_3-v_his_temp23[temp_cnt])/10;
        r33 = 1.0*(Wav3_Temp_3-v_his_temp33[temp_cnt])/10;
        r43 = 1.0*(Wav4_Temp_3-v_his_temp43[temp_cnt])/10;
        r53 = 1.0*(Wav5_Temp_3-v_his_temp53[temp_cnt])/10;
        r14 = 1.0*(Wav1_Temp_4-v_his_temp14[temp_cnt])/10;
        r24 = 1.0*(Wav2_Temp_4-v_his_temp24[temp_cnt])/10;
        r34 = 1.0*(Wav3_Temp_4-v_his_temp34[temp_cnt])/10;
        r44 = 1.0*(Wav4_Temp_4-v_his_temp44[temp_cnt])/10;
        r54 = 1.0*(Wav5_Temp_4-v_his_temp54[temp_cnt])/10;
        r15 = 1.0*(Wav1_Temp_5-v_his_temp15[temp_cnt])/10;
        r25 = 1.0*(Wav2_Temp_5-v_his_temp25[temp_cnt])/10;
        r35 = 1.0*(Wav3_Temp_5-v_his_temp35[temp_cnt])/10;
        r45 = 1.0*(Wav4_Temp_5-v_his_temp45[temp_cnt])/10;
        r55 = 1.0*(Wav5_Temp_5-v_his_temp55[temp_cnt])/10;
        r16 = 1.0*(Wav1_Temp_6-v_his_temp16[temp_cnt])/10;
        r26 = 1.0*(Wav2_Temp_6-v_his_temp26[temp_cnt])/10;
        r36 = 1.0*(Wav3_Temp_6-v_his_temp36[temp_cnt])/10;
        r46 = 1.0*(Wav4_Temp_6-v_his_temp46[temp_cnt])/10;
        r56 = 1.0*(Wav5_Temp_6-v_his_temp56[temp_cnt])/10;
        r17 = 1.0*(Wav1_Temp_7-v_his_temp17[temp_cnt])/10;
        r27 = 1.0*(Wav2_Temp_7-v_his_temp27[temp_cnt])/10;
        r37 = 1.0*(Wav3_Temp_7-v_his_temp37[temp_cnt])/10;
        r47 = 1.0*(Wav4_Temp_7-v_his_temp47[temp_cnt])/10;
        r57 = 1.0*(Wav5_Temp_7-v_his_temp57[temp_cnt])/10;
        r18 = 1.0*(Wav1_Temp_8-v_his_temp18[temp_cnt])/10;
        r28 = 1.0*(Wav2_Temp_8-v_his_temp28[temp_cnt])/10;
        r38 = 1.0*(Wav3_Temp_8-v_his_temp38[temp_cnt])/10;
        r48 = 1.0*(Wav4_Temp_8-v_his_temp48[temp_cnt])/10;
        r58 = 1.0*(Wav5_Temp_8-v_his_temp58[temp_cnt])/10;
        r19 = 1.0*(Wav1_Temp_9-v_his_temp19[temp_cnt])/10;
        r29 = 1.0*(Wav2_Temp_9-v_his_temp29[temp_cnt])/10;
        r39 = 1.0*(Wav3_Temp_9-v_his_temp39[temp_cnt])/10;
        r49 = 1.0*(Wav4_Temp_9-v_his_temp49[temp_cnt])/10;
        r59 = 1.0*(Wav5_Temp_9-v_his_temp59[temp_cnt])/10;
        r1A = 1.0*(Wav1_Temp_A-v_his_temp1A[temp_cnt])/10;
        r2A = 1.0*(Wav2_Temp_A-v_his_temp2A[temp_cnt])/10;
        r3A = 1.0*(Wav3_Temp_A-v_his_temp3A[temp_cnt])/10;
        r4A = 1.0*(Wav4_Temp_A-v_his_temp4A[temp_cnt])/10;
        r5A = 1.0*(Wav5_Temp_A-v_his_temp5A[temp_cnt])/10;
    }

    else {
         r11=0,r21=0,r31=0,r41=0,r51=0,
         r12=0,r22=0,r32=0,r42=0,r52=0,
         r13=0,r23=0,r33=0,r43=0,r53=0,
         r14=0,r24=0,r34=0,r44=0,r54=0,
         r15=0,r25=0,r35=0,r45=0,r55=0,
         r16=0,r26=0,r36=0,r46=0,r56=0,
         r17=0,r27=0,r37=0,r47=0,r57=0,
         r18=0,r28=0,r38=0,r48=0,r58=0,
         r19=0,r29=0,r39=0,r49=0,r59=0,
         r1A=0,r2A=0,r3A=0,r4A=0,r5A=0;
    }

    //    qDebug()<<"r2 = "<<r2<<endl;

    //save temp rise ratio
    temp_rise_ratio11.push_back(r11);
    temp_rise_ratio21.push_back(r21);
    temp_rise_ratio31.push_back(r31);
    temp_rise_ratio41.push_back(r41);
    temp_rise_ratio51.push_back(r51);
    temp_rise_ratio12.push_back(r12);
    temp_rise_ratio22.push_back(r22);
    temp_rise_ratio32.push_back(r32);
    temp_rise_ratio42.push_back(r42);
    temp_rise_ratio52.push_back(r52);
    temp_rise_ratio13.push_back(r13);
    temp_rise_ratio23.push_back(r23);
    temp_rise_ratio33.push_back(r33);
    temp_rise_ratio43.push_back(r43);
    temp_rise_ratio53.push_back(r53);
    temp_rise_ratio14.push_back(r14);
    temp_rise_ratio24.push_back(r24);
    temp_rise_ratio34.push_back(r34);
    temp_rise_ratio44.push_back(r44);
    temp_rise_ratio54.push_back(r54);
    temp_rise_ratio15.push_back(r15);
    temp_rise_ratio25.push_back(r25);
    temp_rise_ratio35.push_back(r35);
    temp_rise_ratio45.push_back(r45);
    temp_rise_ratio55.push_back(r55);
    temp_rise_ratio16.push_back(r16);
    temp_rise_ratio26.push_back(r26);
    temp_rise_ratio36.push_back(r36);
    temp_rise_ratio46.push_back(r46);
    temp_rise_ratio56.push_back(r56);
    temp_rise_ratio17.push_back(r17);
    temp_rise_ratio27.push_back(r27);
    temp_rise_ratio37.push_back(r37);
    temp_rise_ratio47.push_back(r47);
    temp_rise_ratio57.push_back(r57);
    temp_rise_ratio18.push_back(r18);
    temp_rise_ratio28.push_back(r28);
    temp_rise_ratio38.push_back(r38);
    temp_rise_ratio48.push_back(r48);
    temp_rise_ratio58.push_back(r58);
    temp_rise_ratio19.push_back(r19);
    temp_rise_ratio29.push_back(r29);
    temp_rise_ratio39.push_back(r39);
    temp_rise_ratio49.push_back(r49);
    temp_rise_ratio59.push_back(r59);
    temp_rise_ratio1A.push_back(r1A);
    temp_rise_ratio2A.push_back(r2A);
    temp_rise_ratio3A.push_back(r3A);
    temp_rise_ratio4A.push_back(r4A);
    temp_rise_ratio5A.push_back(r5A);

    /*--------传递Temp_Ratio-------*/
    QJsonObject template_temp_obj;
    QJsonArray  ratio_json11, ratio_json21, ratio_json31, ratio_json41, ratio_json51,
                ratio_json12, ratio_json22, ratio_json32, ratio_json42, ratio_json52,
                ratio_json13, ratio_json23, ratio_json33, ratio_json43, ratio_json53,
                ratio_json14, ratio_json24, ratio_json34, ratio_json44, ratio_json54,
                ratio_json15, ratio_json25, ratio_json35, ratio_json45, ratio_json55,
                ratio_json16, ratio_json26, ratio_json36, ratio_json46, ratio_json56,
                ratio_json17, ratio_json27, ratio_json37, ratio_json47, ratio_json57,
                ratio_json18, ratio_json28, ratio_json38, ratio_json48, ratio_json58,
                ratio_json19, ratio_json29, ratio_json39, ratio_json49, ratio_json59,
                ratio_json1A, ratio_json2A, ratio_json3A, ratio_json4A, ratio_json5A;


    ratio_json11.push_back(r11);
    ratio_json21.push_back(r21);
    ratio_json31.push_back(r31);
    ratio_json41.push_back(r41);
    ratio_json51.push_back(r51);
    ratio_json12.push_back(r12);
    ratio_json22.push_back(r22);
    ratio_json32.push_back(r32);
    ratio_json42.push_back(r42);
    ratio_json52.push_back(r52);
    ratio_json13.push_back(r13);
    ratio_json23.push_back(r23);
    ratio_json33.push_back(r33);
    ratio_json43.push_back(r43);
    ratio_json53.push_back(r53);
    ratio_json14.push_back(r14);
    ratio_json24.push_back(r24);
    ratio_json34.push_back(r34);
    ratio_json44.push_back(r44);
    ratio_json54.push_back(r54);
    ratio_json15.push_back(r15);
    ratio_json25.push_back(r25);
    ratio_json35.push_back(r35);
    ratio_json45.push_back(r45);
    ratio_json55.push_back(r55);
    ratio_json16.push_back(r16);
    ratio_json26.push_back(r26);
    ratio_json36.push_back(r36);
    ratio_json46.push_back(r46);
    ratio_json56.push_back(r56);
    ratio_json17.push_back(r17);
    ratio_json27.push_back(r27);
    ratio_json37.push_back(r37);
    ratio_json47.push_back(r47);
    ratio_json57.push_back(r57);
    ratio_json18.push_back(r18);
    ratio_json28.push_back(r28);
    ratio_json38.push_back(r38);
    ratio_json48.push_back(r48);
    ratio_json58.push_back(r58);
    ratio_json19.push_back(r19);
    ratio_json29.push_back(r29);
    ratio_json39.push_back(r39);
    ratio_json49.push_back(r49);
    ratio_json59.push_back(r59);
    ratio_json1A.push_back(r1A);
    ratio_json2A.push_back(r2A);
    ratio_json3A.push_back(r3A);
    ratio_json4A.push_back(r4A);
    ratio_json5A.push_back(r5A);

    template_temp_obj.insert("temp_ratio11", ratio_json11);
    template_temp_obj.insert("temp_ratio21", ratio_json21);
    template_temp_obj.insert("temp_ratio31", ratio_json31);
    template_temp_obj.insert("temp_ratio41", ratio_json41);
    template_temp_obj.insert("temp_ratio51", ratio_json51);
    template_temp_obj.insert("temp_ratio12", ratio_json12);
    template_temp_obj.insert("temp_ratio22", ratio_json22);
    template_temp_obj.insert("temp_ratio32", ratio_json32);
    template_temp_obj.insert("temp_ratio42", ratio_json42);
    template_temp_obj.insert("temp_ratio52", ratio_json52);
    template_temp_obj.insert("temp_ratio13", ratio_json13);
    template_temp_obj.insert("temp_ratio23", ratio_json23);
    template_temp_obj.insert("temp_ratio33", ratio_json33);
    template_temp_obj.insert("temp_ratio43", ratio_json43);
    template_temp_obj.insert("temp_ratio53", ratio_json53);
    template_temp_obj.insert("temp_ratio14", ratio_json14);
    template_temp_obj.insert("temp_ratio24", ratio_json24);
    template_temp_obj.insert("temp_ratio34", ratio_json34);
    template_temp_obj.insert("temp_ratio44", ratio_json44);
    template_temp_obj.insert("temp_ratio54", ratio_json54);
    template_temp_obj.insert("temp_ratio15", ratio_json15);
    template_temp_obj.insert("temp_ratio25", ratio_json25);
    template_temp_obj.insert("temp_ratio35", ratio_json35);
    template_temp_obj.insert("temp_ratio45", ratio_json45);
    template_temp_obj.insert("temp_ratio55", ratio_json55);
    template_temp_obj.insert("temp_ratio16", ratio_json16);
    template_temp_obj.insert("temp_ratio26", ratio_json26);
    template_temp_obj.insert("temp_ratio36", ratio_json36);
    template_temp_obj.insert("temp_ratio46", ratio_json46);
    template_temp_obj.insert("temp_ratio56", ratio_json56);
    template_temp_obj.insert("temp_ratio17", ratio_json17);
    template_temp_obj.insert("temp_ratio27", ratio_json27);
    template_temp_obj.insert("temp_ratio37", ratio_json37);
    template_temp_obj.insert("temp_ratio47", ratio_json47);
    template_temp_obj.insert("temp_ratio57", ratio_json57);
    template_temp_obj.insert("temp_ratio18", ratio_json18);
    template_temp_obj.insert("temp_ratio28", ratio_json28);
    template_temp_obj.insert("temp_ratio38", ratio_json38);
    template_temp_obj.insert("temp_ratio48", ratio_json48);
    template_temp_obj.insert("temp_ratio58", ratio_json58);
    template_temp_obj.insert("temp_ratio19", ratio_json19);
    template_temp_obj.insert("temp_ratio29", ratio_json29);
    template_temp_obj.insert("temp_ratio39", ratio_json39);
    template_temp_obj.insert("temp_ratio49", ratio_json49);
    template_temp_obj.insert("temp_ratio59", ratio_json59);
    template_temp_obj.insert("temp_ratio1A", ratio_json1A);
    template_temp_obj.insert("temp_ratio2A", ratio_json2A);
    template_temp_obj.insert("temp_ratio3A", ratio_json3A);
    template_temp_obj.insert("temp_ratio4A", ratio_json4A);
    template_temp_obj.insert("temp_ratio5A", ratio_json5A);

    //    //get the max of Temp, the region of the max Temp
    //    Temp_Max= Temp_1;

    vector<int>Wav1_Temp_v{Wav1_Temp_1,Wav1_Temp_2,Wav1_Temp_3,Wav1_Temp_4,Wav1_Temp_5};
    vector<int>Temp_Max_v{Temp_Max_1,Temp_Max_2,Temp_Max_3,Temp_Max_4,Temp_Max_5};

    //get the demo MAX_Temp of wavelength
    Temp_Max_1 = m_demodulation->MAX_Temp_1;
    Temp_Max_2 = m_demodulation->MAX_Temp_2;
    Temp_Max_3 = m_demodulation->MAX_Temp_3;
    Temp_Max_4 = m_demodulation->MAX_Temp_4;
    Temp_Max_5 = m_demodulation->MAX_Temp_5;
    Temp_Max = *max_element(Temp_Max_v.begin(),Temp_Max_v.end());

    //region detection by the difference of Temp and MAX_Temp (bug)
    vector<int> diff_Temp;
    for(int p=0;p<5;++p){
        diff_Temp.push_back(abs(Temp_Max_1-Wav1_Temp_v[p]));
    }

    max_region = min_element(diff_Temp.begin(),diff_Temp.end())-diff_Temp.begin() + 1;

    /*--------传递MAX_Temp-------*/
    QJsonObject temp_Obj; //存放“temperature”"region"两个键
    QJsonArray temp_json;

    temp_json.push_back(Temp_Max);

    temp_Obj.insert("temperature", temp_json);

    /*-------传递template_temp温度建模-------*/

    QJsonArray template_temp_json11, template_temp_json21, template_temp_json31,template_temp_json41, template_temp_json51,
            template_temp_json12, template_temp_json22, template_temp_json32,template_temp_json42, template_temp_json52,
            template_temp_json13, template_temp_json23, template_temp_json33,template_temp_json43, template_temp_json53,
            template_temp_json14, template_temp_json24, template_temp_json34,template_temp_json44, template_temp_json54,
            template_temp_json15, template_temp_json25, template_temp_json35,template_temp_json45, template_temp_json55,
            template_temp_json16, template_temp_json26, template_temp_json36,template_temp_json46, template_temp_json56,
            template_temp_json17, template_temp_json27, template_temp_json37,template_temp_json47, template_temp_json57,
            template_temp_json18, template_temp_json28, template_temp_json38,template_temp_json48, template_temp_json58,
            template_temp_json19, template_temp_json29, template_temp_json39,template_temp_json49, template_temp_json59,
            template_temp_json1A, template_temp_json2A, template_temp_json3A,template_temp_json4A, template_temp_json5A;


    template_temp_json11.push_back(Wav1_Temp_1);
    template_temp_json21.push_back(Wav2_Temp_1);
    template_temp_json31.push_back(Wav3_Temp_1);
    template_temp_json41.push_back(Wav4_Temp_1);
    template_temp_json51.push_back(Wav5_Temp_1);
    template_temp_json12.push_back(Wav1_Temp_2);
    template_temp_json22.push_back(Wav2_Temp_2);
    template_temp_json32.push_back(Wav3_Temp_2);
    template_temp_json42.push_back(Wav4_Temp_2);
    template_temp_json52.push_back(Wav5_Temp_2);
    template_temp_json13.push_back(Wav1_Temp_3);
    template_temp_json23.push_back(Wav2_Temp_3);
    template_temp_json33.push_back(Wav3_Temp_3);
    template_temp_json43.push_back(Wav4_Temp_3);
    template_temp_json53.push_back(Wav5_Temp_3);
    template_temp_json14.push_back(Wav1_Temp_4);
    template_temp_json24.push_back(Wav2_Temp_4);
    template_temp_json34.push_back(Wav3_Temp_4);
    template_temp_json44.push_back(Wav4_Temp_4);
    template_temp_json54.push_back(Wav5_Temp_4);
    template_temp_json15.push_back(Wav1_Temp_5);
    template_temp_json25.push_back(Wav2_Temp_5);
    template_temp_json35.push_back(Wav3_Temp_5);
    template_temp_json45.push_back(Wav4_Temp_5);
    template_temp_json55.push_back(Wav5_Temp_5);
    template_temp_json16.push_back(Wav1_Temp_6);
    template_temp_json26.push_back(Wav2_Temp_6);
    template_temp_json36.push_back(Wav3_Temp_6);
    template_temp_json46.push_back(Wav4_Temp_6);
    template_temp_json56.push_back(Wav5_Temp_6);
    template_temp_json17.push_back(Wav1_Temp_7);
    template_temp_json27.push_back(Wav2_Temp_7);
    template_temp_json37.push_back(Wav3_Temp_7);
    template_temp_json47.push_back(Wav4_Temp_7);
    template_temp_json57.push_back(Wav5_Temp_7);
    template_temp_json18.push_back(Wav1_Temp_8);
    template_temp_json28.push_back(Wav2_Temp_8);
    template_temp_json38.push_back(Wav3_Temp_8);
    template_temp_json48.push_back(Wav4_Temp_8);
    template_temp_json58.push_back(Wav5_Temp_8);
    template_temp_json19.push_back(Wav1_Temp_9);
    template_temp_json29.push_back(Wav2_Temp_9);
    template_temp_json39.push_back(Wav3_Temp_9);
    template_temp_json49.push_back(Wav4_Temp_9);
    template_temp_json59.push_back(Wav5_Temp_9);
    template_temp_json1A.push_back(Wav1_Temp_A);
    template_temp_json2A.push_back(Wav2_Temp_A);
    template_temp_json3A.push_back(Wav3_Temp_A);
    template_temp_json4A.push_back(Wav4_Temp_A);
    template_temp_json5A.push_back(Wav5_Temp_A);

    template_temp_obj.insert("lambda11", template_temp_json11);
    template_temp_obj.insert("lambda21", template_temp_json21);
    template_temp_obj.insert("lambda31", template_temp_json31);
    template_temp_obj.insert("lambda41", template_temp_json41);
    template_temp_obj.insert("lambda51", template_temp_json51);
    template_temp_obj.insert("lambda12", template_temp_json12);
    template_temp_obj.insert("lambda22", template_temp_json22);
    template_temp_obj.insert("lambda32", template_temp_json32);
    template_temp_obj.insert("lambda42", template_temp_json42);
    template_temp_obj.insert("lambda52", template_temp_json52);
    template_temp_obj.insert("lambda13", template_temp_json13);
    template_temp_obj.insert("lambda23", template_temp_json23);
    template_temp_obj.insert("lambda33", template_temp_json33);
    template_temp_obj.insert("lambda43", template_temp_json43);
    template_temp_obj.insert("lambda53", template_temp_json53);
    template_temp_obj.insert("lambda14", template_temp_json14);
    template_temp_obj.insert("lambda24", template_temp_json24);
    template_temp_obj.insert("lambda34", template_temp_json34);
    template_temp_obj.insert("lambda44", template_temp_json44);
    template_temp_obj.insert("lambda54", template_temp_json54);
    template_temp_obj.insert("lambda15", template_temp_json15);
    template_temp_obj.insert("lambda25", template_temp_json25);
    template_temp_obj.insert("lambda35", template_temp_json35);
    template_temp_obj.insert("lambda45", template_temp_json45);
    template_temp_obj.insert("lambda55", template_temp_json55);
    template_temp_obj.insert("lambda16", template_temp_json16);
    template_temp_obj.insert("lambda26", template_temp_json26);
    template_temp_obj.insert("lambda36", template_temp_json36);
    template_temp_obj.insert("lambda46", template_temp_json46);
    template_temp_obj.insert("lambda56", template_temp_json56);
    template_temp_obj.insert("lambda17", template_temp_json17);
    template_temp_obj.insert("lambda27", template_temp_json27);
    template_temp_obj.insert("lambda37", template_temp_json37);
    template_temp_obj.insert("lambda47", template_temp_json47);
    template_temp_obj.insert("lambda57", template_temp_json57);
    template_temp_obj.insert("lambda18", template_temp_json18);
    template_temp_obj.insert("lambda28", template_temp_json28);
    template_temp_obj.insert("lambda38", template_temp_json38);
    template_temp_obj.insert("lambda48", template_temp_json48);
    template_temp_obj.insert("lambda58", template_temp_json58);
    template_temp_obj.insert("lambda19", template_temp_json19);
    template_temp_obj.insert("lambda29", template_temp_json29);
    template_temp_obj.insert("lambda39", template_temp_json39);
    template_temp_obj.insert("lambda49", template_temp_json49);
    template_temp_obj.insert("lambda59", template_temp_json59);
    template_temp_obj.insert("lambda1A", template_temp_json1A);
    template_temp_obj.insert("lambda2A", template_temp_json2A);
    template_temp_obj.insert("lambda3A", template_temp_json3A);
    template_temp_obj.insert("lambda4A", template_temp_json4A);
    template_temp_obj.insert("lambda5A", template_temp_json5A);

    QString optionStr3 = QJsonDocument(template_temp_obj).toJson();

    QString js3 = QString("template(%1)").arg(optionStr3);

    m_temp_distance_widget->page()->runJavaScript(js3);

    /*-------传递MAX_Region-------*/
    QJsonArray region_json;

    region_json.push_back(max_region);

    temp_Obj.insert("region", region_json);

    QString optionStr2 = QJsonDocument(temp_Obj).toJson();

    QString js2 = QString("highTemp(%1)").arg(optionStr2);

    m_temp_distance_widget->page()->runJavaScript(js2);

    ++flash_cnt;
}


//过热报警功能
void MainWindow::start_alarm()
{
    /*------告警：消警状态下，若温度高于154°开始计数，若3s后，温度仍大于，则开始报警------*/

    if(reset_flag==1 /*&& red_flag==0*/ && /*m_demodulation->MAX_Temp*/Temp_Max_1>=154){
        ++red_count;

        if(red_count>=3){
            red_flag = 1;
            reset_flag = 0;
        }
    }

    /*-------------消警：报警状态下，若温度小于85°开始计数，若3秒后，温度仍小于，则消警----------------*/

    else if(red_flag==1 /*&& reset_flag==0*/ && /*m_demodulation->MAX_Temp*/Temp_Max_1<85){

        ++reset_count;

        if(reset_count>=3){
            reset_flag = 1;
            red_flag = 0;
        }
    }

    /*-------------其他：清零报警和消警计数器----------------*/
    else{
        red_count = 0;
        reset_count = 0;
    }

    /*--------传递flag-------*/
    QJsonObject flag_Obj;
    QJsonArray flag_json1,flag_json2;

    //    red_flag = 1;
    //    reset_flag = 0;
    flag_json1.push_back(red_flag);
    flag_json2.push_back(reset_flag);

    flag_Obj.insert("red_flag", flag_json1);
    flag_Obj.insert("reset_flag", flag_json2);


    QString optionStr2 = QJsonDocument(flag_Obj).toJson();

    QString js_alarm = QString("baojing(%1)").arg(optionStr2);

    m_temp_distance_widget->page()->runJavaScript(js_alarm);
}

//开始接收数据并检测
void MainWindow::start_detection()
{
    //开始接收数据线程
    m_udp_recv->start();

    //开始解调数据线程
    m_demodulation->start();

    //定时器控制echarts_load_temp()显示 ms
    if(!Temp_Display_Timer->isActive()) Temp_Display_Timer->start(1000);

    //定时器控制start_alarm()显示 ms
    if(!Alarm_Timer->isActive()) Alarm_Timer->start(1000);
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

//void MainWindow::FinishTemp_saveThread()
//{
//    m_temp_distance_save->quit();
//    m_temp_distance_save->wait();
//}

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

