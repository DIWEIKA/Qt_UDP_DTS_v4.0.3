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
#include "Temp_distance_save.h"
#include <QtWebEngineWidgets>
#include <QtWebChannel>
//#include "webclass.h"
#include <QResizeEvent>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace std;

class demodulation;
class Temp_distance_save;
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
    Temp_distance_save* m_temp_distance_save;
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

//    QLabel *label;
//    void paintEvent(QPaintEvent*) override;
    int alarm_count=0; //±¨¾¯¼ÆÊ±

    QString APP_TITLE;
//    QString BGD_IMAGE;
    QString TEMP_DIST_HTML;
    QString STYLE_SHEET;
    int ALARM_TEMP_THRESHOLD;

    bool yellow_flag = 0;
    int yellow_count = 0;
    bool red_flag = 0;
    int reset_count = 0;
    bool reset_flag = 1;

    void set_style_sheet();
//    void set_background_image();
    void read_config();
    void init_widget_temp_distance();

    //    void init_widget_max_temp();

    void echarts_load_temp();
    void Open_Temp_Save_Thread();
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
    void FinishTemp_saveThread();

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
