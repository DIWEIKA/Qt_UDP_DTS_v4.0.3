#ifndef DEMODULATION_H
#define DEMODULATION_H

#include <QObject>
#include <mainwindow.h>
//#include <qwt3d_surfaceplot.h>
#include <algorithm>

//#define WAVNUM 64 //波长数目
//#define DISNUM 128 //距离采样点点数

enum { WAVNUM = 64 }; //波长数目
enum { DISNUM = 128 }; //距离采样点点数

class MainWindow;

class demodulation : public QThread
{
    Q_OBJECT
public:
    explicit demodulation(MainWindow* _mainWindow);
    ~demodulation();

    MainWindow* m_mainwindow;

    void read_config();

    int** all_wavelength_data;
    int single_wave_data_1[DISNUM]={'\0'};
    int single_wave_data_2[DISNUM]={'\0'};
    int single_wave_data_3[DISNUM]={'\0'};
    int single_wave_data_4[DISNUM]={'\0'};
    int single_wave_data_5[DISNUM]={'\0'};
    int single_wave_data_6[DISNUM]={'\0'};
    int single_wave_data_7[DISNUM]={'\0'};
    int single_wave_data_8[DISNUM]={'\0'};
    int single_wave_data_9[DISNUM]={'\0'};
    int single_wave_data_10[DISNUM]={'\0'};
    int single_wave_data_11[DISNUM]={'\0'};
    int single_wave_data_12[DISNUM]={'\0'};
    int single_wave_data_13[DISNUM]={'\0'};
    int single_wave_data_14[DISNUM]={'\0'};
    int single_wave_data_15[DISNUM]={'\0'};
    int single_wave_data_16[DISNUM]={'\0'};
    int single_wave_data_17[DISNUM]={'\0'};
    int single_wave_data_18[DISNUM]={'\0'};
    int single_wave_data_19[DISNUM]={'\0'};
    int single_wave_data_20[DISNUM]={'\0'};
    int single_wave_data_21[DISNUM]={'\0'};
    int single_wave_data_22[DISNUM]={'\0'};
    int single_wave_data_23[DISNUM]={'\0'};
    int single_wave_data_24[DISNUM]={'\0'};
    int single_wave_data_25[DISNUM]={'\0'};
    int single_wave_data_26[DISNUM]={'\0'};
    int single_wave_data_27[DISNUM]={'\0'};
    int single_wave_data_28[DISNUM]={'\0'};
    int single_wave_data_29[DISNUM]={'\0'};
    int single_wave_data_30[DISNUM]={'\0'};
    int single_wave_data_31[DISNUM]={'\0'};
    int single_wave_data_32[DISNUM]={'\0'};
    int single_wave_data_33[DISNUM]={'\0'};
    int single_wave_data_34[DISNUM]={'\0'};
    int single_wave_data_35[DISNUM]={'\0'};
    int single_wave_data_36[DISNUM]={'\0'};
    int single_wave_data_37[DISNUM]={'\0'};
    int single_wave_data_38[DISNUM]={'\0'};
    int single_wave_data_39[DISNUM]={'\0'};
    int single_wave_data_40[DISNUM]={'\0'};
    int single_wave_data_41[DISNUM]={'\0'};
    int single_wave_data_42[DISNUM]={'\0'};
    int single_wave_data_43[DISNUM]={'\0'};
    int single_wave_data_44[DISNUM]={'\0'};
    int single_wave_data_45[DISNUM]={'\0'};
    int single_wave_data_46[DISNUM]={'\0'};
    int single_wave_data_47[DISNUM]={'\0'};
    int single_wave_data_48[DISNUM]={'\0'};
    int single_wave_data_49[DISNUM]={'\0'};
    int single_wave_data_50[DISNUM]={'\0'};
    int single_wave_data_51[DISNUM]={'\0'};
    int single_wave_data_52[DISNUM]={'\0'};
    int single_wave_data_53[DISNUM]={'\0'};
    int single_wave_data_54[DISNUM]={'\0'};
    int single_wave_data_55[DISNUM]={'\0'};
    int single_wave_data_56[DISNUM]={'\0'};
    int single_wave_data_57[DISNUM]={'\0'};
    int single_wave_data_58[DISNUM]={'\0'};
    int single_wave_data_59[DISNUM]={'\0'};
    int single_wave_data_60[DISNUM]={'\0'};
    int single_wave_data_61[DISNUM]={'\0'};
    int single_wave_data_62[DISNUM]={'\0'};
    int single_wave_data_63[DISNUM]={'\0'};
    int single_wave_data_64[DISNUM]={'\0'};

    int Temp[DISNUM]={'\0'};
    int MAX_Temp; //定义最大温度值
    int threshold; //定义寻峰阈值

    void run();

signals:

};

#endif // DEMODULATION_H
