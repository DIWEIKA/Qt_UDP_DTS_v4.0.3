#ifndef DEMODULATION_H
#define DEMODULATION_H

#include <QObject>
#include <mainwindow.h>
//#include <qwt3d_surfaceplot.h>
#include <algorithm>
#include <vector>

//#define WAVNUM 64 //波长数目
//#define DISNUM 128 //距离采样点点数

enum { WAVNUM = 256 }; //顺序光谱波长轴点数
enum { DISNUM = 32 }; //裁切后光谱距离轴点数
enum { WAVLENNUM = 50}; //裁切后光谱波长轴点数
//enum { SAMNUM = 32}; //距离轴点数


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
    int single_wave_data_1[WAVNUM]={'\0'};
    int single_wave_data_2[WAVNUM]={'\0'};
    int single_wave_data_3[WAVNUM]={'\0'};
    int single_wave_data_4[WAVNUM]={'\0'};
    int single_wave_data_5[WAVNUM]={'\0'};
    int single_wave_data_6[WAVNUM]={'\0'};
    int single_wave_data_7[WAVNUM]={'\0'};
    int single_wave_data_8[WAVNUM]={'\0'};
    int single_wave_data_9[WAVNUM]={'\0'};
    int single_wave_data_10[WAVNUM]={'\0'};
    int single_wave_data_11[WAVNUM]={'\0'};
    int single_wave_data_12[WAVNUM]={'\0'};
    int single_wave_data_13[WAVNUM]={'\0'};
    int single_wave_data_14[WAVNUM]={'\0'};
    int single_wave_data_15[WAVNUM]={'\0'};
    int single_wave_data_16[WAVNUM]={'\0'};
    int single_wave_data_17[WAVNUM]={'\0'};
    int single_wave_data_18[WAVNUM]={'\0'};
    int single_wave_data_19[WAVNUM]={'\0'};
    int single_wave_data_20[WAVNUM]={'\0'};
    int single_wave_data_21[WAVNUM]={'\0'};
    int single_wave_data_22[WAVNUM]={'\0'};
    int single_wave_data_23[WAVNUM]={'\0'};
    int single_wave_data_24[WAVNUM]={'\0'};
    int single_wave_data_25[WAVNUM]={'\0'};
    int single_wave_data_26[WAVNUM]={'\0'};
    int single_wave_data_27[WAVNUM]={'\0'};
    int single_wave_data_28[WAVNUM]={'\0'};
    int single_wave_data_29[WAVNUM]={'\0'};
    int single_wave_data_30[WAVNUM]={'\0'};
    int single_wave_data_31[WAVNUM]={'\0'};
    int single_wave_data_32[WAVNUM]={'\0'};
//    int single_wave_data_33[DISNUM]={'\0'};
//    int single_wave_data_34[DISNUM]={'\0'};
//    int single_wave_data_35[DISNUM]={'\0'};
//    int single_wave_data_36[DISNUM]={'\0'};
//    int single_wave_data_37[DISNUM]={'\0'};
//    int single_wave_data_38[DISNUM]={'\0'};
//    int single_wave_data_39[DISNUM]={'\0'};
//    int single_wave_data_40[DISNUM]={'\0'};
//    int single_wave_data_41[DISNUM]={'\0'};
//    int single_wave_data_42[DISNUM]={'\0'};
//    int single_wave_data_43[DISNUM]={'\0'};
//    int single_wave_data_44[DISNUM]={'\0'};
//    int single_wave_data_45[DISNUM]={'\0'};
//    int single_wave_data_46[DISNUM]={'\0'};
//    int single_wave_data_47[DISNUM]={'\0'};
//    int single_wave_data_48[DISNUM]={'\0'};
//    int single_wave_data_49[DISNUM]={'\0'};
//    int single_wave_data_50[DISNUM]={'\0'};
//    int single_wave_data_51[DISNUM]={'\0'};
//    int single_wave_data_52[DISNUM]={'\0'};
//    int single_wave_data_53[DISNUM]={'\0'};
//    int single_wave_data_54[DISNUM]={'\0'};
//    int single_wave_data_55[DISNUM]={'\0'};
//    int single_wave_data_56[DISNUM]={'\0'};
//    int single_wave_data_57[DISNUM]={'\0'};
//    int single_wave_data_58[DISNUM]={'\0'};
//    int single_wave_data_59[DISNUM]={'\0'};
//    int single_wave_data_60[DISNUM]={'\0'};
//    int single_wave_data_61[DISNUM]={'\0'};
//    int single_wave_data_62[DISNUM]={'\0'};
//    int single_wave_data_63[DISNUM]={'\0'};
//    int single_wave_data_64[DISNUM]={'\0'};

    vector<vector<int>> wavelen1_data; //存放波长1裁切的光谱数据，DISNUM*WAVLENNUM个点
    vector<int> wav1_dis1_data; //波长1距离1
    vector<int> wav1_dis2_data;
    vector<int> wav1_dis3_data;
    vector<int> wav1_dis4_data;
    vector<int> wav1_dis5_data;
    vector<int> wav1_dis6_data;
    vector<int> wav1_dis7_data;
    vector<int> wav1_dis8_data;
    vector<int> wav1_dis9_data;
    vector<int> wav1_dis10_data;
    vector<int> wav1_dis11_data;
    vector<int> wav1_dis12_data;
    vector<int> wav1_dis13_data;
    vector<int> wav1_dis14_data;
    vector<int> wav1_dis15_data;
    vector<int> wav1_dis16_data;
    vector<int> wav1_dis17_data;
    vector<int> wav1_dis18_data;
    vector<int> wav1_dis19_data;
    vector<int> wav1_dis20_data;
    vector<int> wav1_dis21_data;
    vector<int> wav1_dis22_data;
    vector<int> wav1_dis23_data;
    vector<int> wav1_dis24_data;
    vector<int> wav1_dis25_data;
    vector<int> wav1_dis26_data;
    vector<int> wav1_dis27_data;
    vector<int> wav1_dis28_data;
    vector<int> wav1_dis29_data;
    vector<int> wav1_dis30_data;
    vector<int> wav1_dis31_data;
    vector<int> wav1_dis32_data;

    vector<vector<int>> wavelen2_data; //存放波长2裁切的光谱数据
    vector<int> wav2_dis1_data; //波长2距离1
    vector<int> wav2_dis2_data;
    vector<int> wav2_dis3_data;
    vector<int> wav2_dis4_data;
    vector<int> wav2_dis5_data;
    vector<int> wav2_dis6_data;
    vector<int> wav2_dis7_data;
    vector<int> wav2_dis8_data;
    vector<int> wav2_dis9_data;
    vector<int> wav2_dis10_data;
    vector<int> wav2_dis11_data;
    vector<int> wav2_dis12_data;
    vector<int> wav2_dis13_data;
    vector<int> wav2_dis14_data;
    vector<int> wav2_dis15_data;
    vector<int> wav2_dis16_data;
    vector<int> wav2_dis17_data;
    vector<int> wav2_dis18_data;
    vector<int> wav2_dis19_data;
    vector<int> wav2_dis20_data;
    vector<int> wav2_dis21_data;
    vector<int> wav2_dis22_data;
    vector<int> wav2_dis23_data;
    vector<int> wav2_dis24_data;
    vector<int> wav2_dis25_data;
    vector<int> wav2_dis26_data;
    vector<int> wav2_dis27_data;
    vector<int> wav2_dis28_data;
    vector<int> wav2_dis29_data;
    vector<int> wav2_dis30_data;
    vector<int> wav2_dis31_data;
    vector<int> wav2_dis32_data;

    vector<vector<int>> wavelen3_data; //存放波长3裁切的光谱数据
    vector<int> wav3_dis1_data; //波长3距离1
    vector<int> wav3_dis2_data;
    vector<int> wav3_dis3_data;
    vector<int> wav3_dis4_data;
    vector<int> wav3_dis5_data;
    vector<int> wav3_dis6_data;
    vector<int> wav3_dis7_data;
    vector<int> wav3_dis8_data;
    vector<int> wav3_dis9_data;
    vector<int> wav3_dis10_data;
    vector<int> wav3_dis11_data;
    vector<int> wav3_dis12_data;
    vector<int> wav3_dis13_data;
    vector<int> wav3_dis14_data;
    vector<int> wav3_dis15_data;
    vector<int> wav3_dis16_data;
    vector<int> wav3_dis17_data;
    vector<int> wav3_dis18_data;
    vector<int> wav3_dis19_data;
    vector<int> wav3_dis20_data;
    vector<int> wav3_dis21_data;
    vector<int> wav3_dis22_data;
    vector<int> wav3_dis23_data;
    vector<int> wav3_dis24_data;
    vector<int> wav3_dis25_data;
    vector<int> wav3_dis26_data;
    vector<int> wav3_dis27_data;
    vector<int> wav3_dis28_data;
    vector<int> wav3_dis29_data;
    vector<int> wav3_dis30_data;
    vector<int> wav3_dis31_data;
    vector<int> wav3_dis32_data;

    vector<vector<int>> wavelen4_data; //存放波长4裁切的光谱数据，DISNUM*WAVLENNUM个点
    vector<int> wav4_dis1_data; //波长4距离1
    vector<int> wav4_dis2_data;
    vector<int> wav4_dis3_data;
    vector<int> wav4_dis4_data;
    vector<int> wav4_dis5_data;
    vector<int> wav4_dis6_data;
    vector<int> wav4_dis7_data;
    vector<int> wav4_dis8_data;
    vector<int> wav4_dis9_data;
    vector<int> wav4_dis10_data;
    vector<int> wav4_dis11_data;
    vector<int> wav4_dis12_data;
    vector<int> wav4_dis13_data;
    vector<int> wav4_dis14_data;
    vector<int> wav4_dis15_data;
    vector<int> wav4_dis16_data;
    vector<int> wav4_dis17_data;
    vector<int> wav4_dis18_data;
    vector<int> wav4_dis19_data;
    vector<int> wav4_dis20_data;
    vector<int> wav4_dis21_data;
    vector<int> wav4_dis22_data;
    vector<int> wav4_dis23_data;
    vector<int> wav4_dis24_data;
    vector<int> wav4_dis25_data;
    vector<int> wav4_dis26_data;
    vector<int> wav4_dis27_data;
    vector<int> wav4_dis28_data;
    vector<int> wav4_dis29_data;
    vector<int> wav4_dis30_data;
    vector<int> wav4_dis31_data;
    vector<int> wav4_dis32_data;

    vector<vector<int>> wavelen5_data; //存放波长5裁切的光谱数据
    vector<int> wav5_dis1_data; //波长5距离1
    vector<int> wav5_dis2_data;
    vector<int> wav5_dis3_data;
    vector<int> wav5_dis4_data;
    vector<int> wav5_dis5_data;
    vector<int> wav5_dis6_data;
    vector<int> wav5_dis7_data;
    vector<int> wav5_dis8_data;
    vector<int> wav5_dis9_data;
    vector<int> wav5_dis10_data;
    vector<int> wav5_dis11_data;
    vector<int> wav5_dis12_data;
    vector<int> wav5_dis13_data;
    vector<int> wav5_dis14_data;
    vector<int> wav5_dis15_data;
    vector<int> wav5_dis16_data;
    vector<int> wav5_dis17_data;
    vector<int> wav5_dis18_data;
    vector<int> wav5_dis19_data;
    vector<int> wav5_dis20_data;
    vector<int> wav5_dis21_data;
    vector<int> wav5_dis22_data;
    vector<int> wav5_dis23_data;
    vector<int> wav5_dis24_data;
    vector<int> wav5_dis25_data;
    vector<int> wav5_dis26_data;
    vector<int> wav5_dis27_data;
    vector<int> wav5_dis28_data;
    vector<int> wav5_dis29_data;
    vector<int> wav5_dis30_data;
    vector<int> wav5_dis31_data;
    vector<int> wav5_dis32_data;

    vector<vector<int>> wavelen_all_data; //存放160*50的光谱数据

    int Temp[DISNUM*5]; //五个波长的温度
    int Temp_1[DISNUM]; //波长1的温度
    int Temp_2[DISNUM]; //波长2的温度
    int Temp_3[DISNUM]; //波长3的温度
    int Temp_4[DISNUM]; //波长4的温度
    int Temp_5[DISNUM]; //波长5的温度
    int MAX_Temp_1; //波长1最大温度值
    int MAX_Temp_2; //波长2最大温度值
    int MAX_Temp_3; //波长3最大温度值
    int MAX_Temp_4; //波长4最大温度值
    int MAX_Temp_5; //波长5最大温度值
    int threshold; //定义寻峰阈值

    void run();

signals:

};

#endif // DEMODULATION_H
