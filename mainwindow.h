#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "CirQueue.h"
#include "udp_recv.h"
#include "udp_send.h"
//#include "HEXtoDEC.h"
#include <QMainWindow>
#include <QThread>
#include <demodulation.h>
#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include <fstream>
#include <sstream>
//#include "Temp_distance_save.h"
#include <QtWebEngineWidgets>
#include <QtWebChannel>
//#include "webclass.h"
#include <QResizeEvent>
#include <algorithm>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace std;

class demodulation;
//class Temp_distance_save;
class udp_recv;
class udp_send;
class HEXtoDEC;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Ui::MainWindow *ui;
    //    double* raw_data;
    demodulation* m_demodulation;
//    Temp_distance_save* m_temp_distance_save;
    udp_recv* m_udp_recv;
    udp_send* m_udp_send;
    HEXtoDEC* m_hextodec;

//    QString send_data;

    QWebEngineView* m_temp_distance_widget;
    QWebEngineView* m_max_temp_widget;

    bool isStartRecv = false;

    QTimer* Temp_Display_Timer;
    QTimer* Temp_save_Timer;
    QTimer* Alarm_Timer;

    int flash_cnt = 0; //刷新次数计数

    int alarm_count=0; //报警计时

     int Temp_Max_1 = 0; //波长1最大温度值
     int Temp_Max_2 = 0;
     int Temp_Max_3 = 0;
     int Temp_Max_4 = 0;
     int Temp_Max_5 = 0;
     int Temp_Max = 0; //整段光纤的最高温度
     int max_region = 1; //最大温度的区域

     vector<int> v_his_temp11; //history temperature 11 第一个值是波长索引，第二个是距离索引
     vector<int> v_his_temp21;
     vector<int> v_his_temp31;
     vector<int> v_his_temp41;
     vector<int> v_his_temp51;
     vector<int> v_his_temp12;
     vector<int> v_his_temp22;
     vector<int> v_his_temp32;
     vector<int> v_his_temp42;
     vector<int> v_his_temp52;
     vector<int> v_his_temp13;
     vector<int> v_his_temp23;
     vector<int> v_his_temp33;
     vector<int> v_his_temp43;
     vector<int> v_his_temp53;
     vector<int> v_his_temp14;
     vector<int> v_his_temp24;
     vector<int> v_his_temp34;
     vector<int> v_his_temp44;
     vector<int> v_his_temp54;
     vector<int> v_his_temp15;
     vector<int> v_his_temp25;
     vector<int> v_his_temp35;
     vector<int> v_his_temp45;
     vector<int> v_his_temp55;
     vector<int> v_his_temp16;
     vector<int> v_his_temp26;
     vector<int> v_his_temp36;
     vector<int> v_his_temp46;
     vector<int> v_his_temp56;
     vector<int> v_his_temp17;
     vector<int> v_his_temp27;
     vector<int> v_his_temp37;
     vector<int> v_his_temp47;
     vector<int> v_his_temp57;
     vector<int> v_his_temp18;
     vector<int> v_his_temp28;
     vector<int> v_his_temp38;
     vector<int> v_his_temp48;
     vector<int> v_his_temp58;
     vector<int> v_his_temp19;
     vector<int> v_his_temp29;
     vector<int> v_his_temp39;
     vector<int> v_his_temp49;
     vector<int> v_his_temp59;
     vector<int> v_his_temp1A;
     vector<int> v_his_temp2A;
     vector<int> v_his_temp3A;
     vector<int> v_his_temp4A;
     vector<int> v_his_temp5A;



     vector<double> temp_rise_ratio11; //temperature rise ratio
     vector<double> temp_rise_ratio21;
     vector<double> temp_rise_ratio31;
     vector<double> temp_rise_ratio41;
     vector<double> temp_rise_ratio51;
     vector<double> temp_rise_ratio12;
     vector<double> temp_rise_ratio22;
     vector<double> temp_rise_ratio32;
     vector<double> temp_rise_ratio42;
     vector<double> temp_rise_ratio52;
     vector<double> temp_rise_ratio13;
     vector<double> temp_rise_ratio23;
     vector<double> temp_rise_ratio33;
     vector<double> temp_rise_ratio43;
     vector<double> temp_rise_ratio53;
     vector<double> temp_rise_ratio14;
     vector<double> temp_rise_ratio24;
     vector<double> temp_rise_ratio34;
     vector<double> temp_rise_ratio44;
     vector<double> temp_rise_ratio54;
     vector<double> temp_rise_ratio15;
     vector<double> temp_rise_ratio25;
     vector<double> temp_rise_ratio35;
     vector<double> temp_rise_ratio45;
     vector<double> temp_rise_ratio55;
     vector<double> temp_rise_ratio16;
     vector<double> temp_rise_ratio26;
     vector<double> temp_rise_ratio36;
     vector<double> temp_rise_ratio46;
     vector<double> temp_rise_ratio56;
     vector<double> temp_rise_ratio17;
     vector<double> temp_rise_ratio27;
     vector<double> temp_rise_ratio37;
     vector<double> temp_rise_ratio47;
     vector<double> temp_rise_ratio57;
     vector<double> temp_rise_ratio18;
     vector<double> temp_rise_ratio28;
     vector<double> temp_rise_ratio38;
     vector<double> temp_rise_ratio48;
     vector<double> temp_rise_ratio58;
     vector<double> temp_rise_ratio19;
     vector<double> temp_rise_ratio29;
     vector<double> temp_rise_ratio39;
     vector<double> temp_rise_ratio49;
     vector<double> temp_rise_ratio59;
     vector<double> temp_rise_ratio1A;
     vector<double> temp_rise_ratio2A;
     vector<double> temp_rise_ratio3A;
     vector<double> temp_rise_ratio4A;
     vector<double> temp_rise_ratio5A;

    QString APP_TITLE;
//    QString BGD_IMAGE;
    QString TEMP_DIST_HTML;
    QString STYLE_SHEET;
    int ALARM_TEMP_THRESHOLD;

    int red_count = 0;
    int red_flag = 0;
    int reset_count = 0;
    int reset_flag = 1;

    void set_style_sheet();
//    void set_background_image();
    void read_config();
    void init_widget_temp_distance();

    //    void init_widget_max_temp();

    void echarts_load_temp();

    void start_alarm();
    void start_detection();

signals:
    void sendToRaw_wave_widget(double* _senddata);


private slots:
    //    void on_btn_demodulation_clicked();

    //    void on_btn_save_temp_clicked();

    void FinishUdp_recvThread();
    void FinishUdp_sendThread();
    void FinishDemodulationThread();
//    void FinishTemp_saveThread();

    void onResizeEcharts5();

    //    void on_btn_recv_clicked();

    //    void on_m_send_clicked();

    //    void on_btn_threshold_clicked();

public slots:

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    bool isLoaded5 = false;
    bool isLoaded6 = false;

};
#endif // MAINWINDOW_H
