#include "demodulation.h"



demodulation::demodulation(MainWindow* _mainWindow):
    m_mainwindow(_mainWindow),
    all_wavelength_data(new int*[WAVNUM]),
//    MAX_Temp(0),
    threshold(1500)
{
    read_config();

    all_wavelength_data[0]=single_wave_data_1;
    all_wavelength_data[1]=single_wave_data_2;
    all_wavelength_data[2]=single_wave_data_3;
    all_wavelength_data[3]=single_wave_data_4;
    all_wavelength_data[4]=single_wave_data_5;
    all_wavelength_data[5]=single_wave_data_6;
    all_wavelength_data[6]=single_wave_data_7;
    all_wavelength_data[7]=single_wave_data_8;
    all_wavelength_data[8]=single_wave_data_9;
    all_wavelength_data[9]=single_wave_data_10;
    all_wavelength_data[10]=single_wave_data_11;
    all_wavelength_data[11]=single_wave_data_12;
    all_wavelength_data[12]=single_wave_data_13;
    all_wavelength_data[13]=single_wave_data_14;
    all_wavelength_data[14]=single_wave_data_15;
    all_wavelength_data[15]=single_wave_data_16;
    all_wavelength_data[16]=single_wave_data_17;
    all_wavelength_data[17]=single_wave_data_18;
    all_wavelength_data[18]=single_wave_data_19;
    all_wavelength_data[19]=single_wave_data_20;
    all_wavelength_data[20]=single_wave_data_21;
    all_wavelength_data[21]=single_wave_data_22;
    all_wavelength_data[22]=single_wave_data_23;
    all_wavelength_data[23]=single_wave_data_24;
    all_wavelength_data[24]=single_wave_data_25;
    all_wavelength_data[25]=single_wave_data_26;
    all_wavelength_data[26]=single_wave_data_27;
    all_wavelength_data[27]=single_wave_data_28;
    all_wavelength_data[28]=single_wave_data_29;
    all_wavelength_data[29]=single_wave_data_30;
    all_wavelength_data[30]=single_wave_data_31;
    all_wavelength_data[31]=single_wave_data_32;
//    all_wavelength_data[32]=single_wave_data_33;
//    all_wavelength_data[33]=single_wave_data_34;
//    all_wavelength_data[34]=single_wave_data_35;
//    all_wavelength_data[35]=single_wave_data_36;
//    all_wavelength_data[36]=single_wave_data_37;
//    all_wavelength_data[37]=single_wave_data_38;
//    all_wavelength_data[38]=single_wave_data_39;
//    all_wavelength_data[39]=single_wave_data_40;
//    all_wavelength_data[40]=single_wave_data_41;
//    all_wavelength_data[41]=single_wave_data_42;
//    all_wavelength_data[42]=single_wave_data_43;
//    all_wavelength_data[43]=single_wave_data_44;
//    all_wavelength_data[44]=single_wave_data_45;
//    all_wavelength_data[45]=single_wave_data_46;
//    all_wavelength_data[46]=single_wave_data_47;
//    all_wavelength_data[47]=single_wave_data_48;
//    all_wavelength_data[48]=single_wave_data_49;
//    all_wavelength_data[49]=single_wave_data_50;
//    all_wavelength_data[50]=single_wave_data_51;
//    all_wavelength_data[51]=single_wave_data_52;
//    all_wavelength_data[52]=single_wave_data_53;
//    all_wavelength_data[53]=single_wave_data_54;
//    all_wavelength_data[54]=single_wave_data_55;
//    all_wavelength_data[55]=single_wave_data_56;
//    all_wavelength_data[56]=single_wave_data_57;
//    all_wavelength_data[57]=single_wave_data_58;
//    all_wavelength_data[58]=single_wave_data_59;
//    all_wavelength_data[59]=single_wave_data_60;
//    all_wavelength_data[60]=single_wave_data_61;
//    all_wavelength_data[61]=single_wave_data_62;
//    all_wavelength_data[62]=single_wave_data_63;
//    all_wavelength_data[63]=single_wave_data_64;

    wav1_dis1_data.resize(WAVLENNUM); //波长1距离1 初始化为WAVLENNUM个0 下同
    wav1_dis2_data.resize(WAVLENNUM);
    wav1_dis3_data.resize(WAVLENNUM);
    wav1_dis4_data.resize(WAVLENNUM);
    wav1_dis5_data.resize(WAVLENNUM);
    wav1_dis6_data.resize(WAVLENNUM);
    wav1_dis7_data.resize(WAVLENNUM);
    wav1_dis8_data.resize(WAVLENNUM);
    wav1_dis9_data.resize(WAVLENNUM);
    wav1_dis10_data.resize(WAVLENNUM);
    wav1_dis11_data.resize(WAVLENNUM);
    wav1_dis12_data.resize(WAVLENNUM);
    wav1_dis13_data.resize(WAVLENNUM);
    wav1_dis14_data.resize(WAVLENNUM);
    wav1_dis15_data.resize(WAVLENNUM);
    wav1_dis16_data.resize(WAVLENNUM);
    wav1_dis17_data.resize(WAVLENNUM);
    wav1_dis18_data.resize(WAVLENNUM);
    wav1_dis19_data.resize(WAVLENNUM);
    wav1_dis20_data.resize(WAVLENNUM);
    wav1_dis21_data.resize(WAVLENNUM);
    wav1_dis22_data.resize(WAVLENNUM);
    wav1_dis23_data.resize(WAVLENNUM);
    wav1_dis24_data.resize(WAVLENNUM);
    wav1_dis25_data.resize(WAVLENNUM);
    wav1_dis26_data.resize(WAVLENNUM);
    wav1_dis27_data.resize(WAVLENNUM);
    wav1_dis28_data.resize(WAVLENNUM);
    wav1_dis29_data.resize(WAVLENNUM);
    wav1_dis30_data.resize(WAVLENNUM);
    wav1_dis31_data.resize(WAVLENNUM);
    wav1_dis32_data.resize(WAVLENNUM);

    wav2_dis1_data.resize(WAVLENNUM); //波长2距离1
    wav2_dis2_data.resize(WAVLENNUM);
    wav2_dis3_data.resize(WAVLENNUM);
    wav2_dis4_data.resize(WAVLENNUM);
    wav2_dis5_data.resize(WAVLENNUM);
    wav2_dis6_data.resize(WAVLENNUM);
    wav2_dis7_data.resize(WAVLENNUM);
    wav2_dis8_data.resize(WAVLENNUM);
    wav2_dis9_data.resize(WAVLENNUM);
    wav2_dis10_data.resize(WAVLENNUM);
    wav2_dis11_data.resize(WAVLENNUM);
    wav2_dis12_data.resize(WAVLENNUM);
    wav2_dis13_data.resize(WAVLENNUM);
    wav2_dis14_data.resize(WAVLENNUM);
    wav2_dis15_data.resize(WAVLENNUM);
    wav2_dis16_data.resize(WAVLENNUM);
    wav2_dis17_data.resize(WAVLENNUM);
    wav2_dis18_data.resize(WAVLENNUM);
    wav2_dis19_data.resize(WAVLENNUM);
    wav2_dis20_data.resize(WAVLENNUM);
    wav2_dis21_data.resize(WAVLENNUM);
    wav2_dis22_data.resize(WAVLENNUM);
    wav2_dis23_data.resize(WAVLENNUM);
    wav2_dis24_data.resize(WAVLENNUM);
    wav2_dis25_data.resize(WAVLENNUM);
    wav2_dis26_data.resize(WAVLENNUM);
    wav2_dis27_data.resize(WAVLENNUM);
    wav2_dis28_data.resize(WAVLENNUM);
    wav2_dis29_data.resize(WAVLENNUM);
    wav2_dis30_data.resize(WAVLENNUM);
    wav2_dis31_data.resize(WAVLENNUM);
    wav2_dis32_data.resize(WAVLENNUM);

    wav3_dis1_data.resize(WAVLENNUM); //波长3距离1
    wav3_dis2_data.resize(WAVLENNUM);
    wav3_dis3_data.resize(WAVLENNUM);
    wav3_dis4_data.resize(WAVLENNUM);
    wav3_dis5_data.resize(WAVLENNUM);
    wav3_dis6_data.resize(WAVLENNUM);
    wav3_dis7_data.resize(WAVLENNUM);
    wav3_dis8_data.resize(WAVLENNUM);
    wav3_dis9_data.resize(WAVLENNUM);
    wav3_dis10_data.resize(WAVLENNUM);
    wav3_dis11_data.resize(WAVLENNUM);
    wav3_dis12_data.resize(WAVLENNUM);
    wav3_dis13_data.resize(WAVLENNUM);
    wav3_dis14_data.resize(WAVLENNUM);
    wav3_dis15_data.resize(WAVLENNUM);
    wav3_dis16_data.resize(WAVLENNUM);
    wav3_dis17_data.resize(WAVLENNUM);
    wav3_dis18_data.resize(WAVLENNUM);
    wav3_dis19_data.resize(WAVLENNUM);
    wav3_dis20_data.resize(WAVLENNUM);
    wav3_dis21_data.resize(WAVLENNUM);
    wav3_dis22_data.resize(WAVLENNUM);
    wav3_dis23_data.resize(WAVLENNUM);
    wav3_dis24_data.resize(WAVLENNUM);
    wav3_dis25_data.resize(WAVLENNUM);
    wav3_dis26_data.resize(WAVLENNUM);
    wav3_dis27_data.resize(WAVLENNUM);
    wav3_dis28_data.resize(WAVLENNUM);
    wav3_dis29_data.resize(WAVLENNUM);
    wav3_dis30_data.resize(WAVLENNUM);
    wav3_dis31_data.resize(WAVLENNUM);
    wav3_dis32_data.resize(WAVLENNUM);

    wav4_dis1_data.resize(WAVLENNUM); //波长4距离1
    wav4_dis2_data.resize(WAVLENNUM);
    wav4_dis3_data.resize(WAVLENNUM);
    wav4_dis4_data.resize(WAVLENNUM);
    wav4_dis5_data.resize(WAVLENNUM);
    wav4_dis6_data.resize(WAVLENNUM);
    wav4_dis7_data.resize(WAVLENNUM);
    wav4_dis8_data.resize(WAVLENNUM);
    wav4_dis9_data.resize(WAVLENNUM);
    wav4_dis10_data.resize(WAVLENNUM);
    wav4_dis11_data.resize(WAVLENNUM);
    wav4_dis12_data.resize(WAVLENNUM);
    wav4_dis13_data.resize(WAVLENNUM);
    wav4_dis14_data.resize(WAVLENNUM);
    wav4_dis15_data.resize(WAVLENNUM);
    wav4_dis16_data.resize(WAVLENNUM);
    wav4_dis17_data.resize(WAVLENNUM);
    wav4_dis18_data.resize(WAVLENNUM);
    wav4_dis19_data.resize(WAVLENNUM);
    wav4_dis20_data.resize(WAVLENNUM);
    wav4_dis21_data.resize(WAVLENNUM);
    wav4_dis22_data.resize(WAVLENNUM);
    wav4_dis23_data.resize(WAVLENNUM);
    wav4_dis24_data.resize(WAVLENNUM);
    wav4_dis25_data.resize(WAVLENNUM);
    wav4_dis26_data.resize(WAVLENNUM);
    wav4_dis27_data.resize(WAVLENNUM);
    wav4_dis28_data.resize(WAVLENNUM);
    wav4_dis29_data.resize(WAVLENNUM);
    wav4_dis30_data.resize(WAVLENNUM);
    wav4_dis31_data.resize(WAVLENNUM);
    wav4_dis32_data.resize(WAVLENNUM);

    wav5_dis1_data.resize(WAVLENNUM); //波长5距离1
    wav5_dis2_data.resize(WAVLENNUM);
    wav5_dis3_data.resize(WAVLENNUM);
    wav5_dis4_data.resize(WAVLENNUM);
    wav5_dis5_data.resize(WAVLENNUM);
    wav5_dis6_data.resize(WAVLENNUM);
    wav5_dis7_data.resize(WAVLENNUM);
    wav5_dis8_data.resize(WAVLENNUM);
    wav5_dis9_data.resize(WAVLENNUM);
    wav5_dis10_data.resize(WAVLENNUM);
    wav5_dis11_data.resize(WAVLENNUM);
    wav5_dis12_data.resize(WAVLENNUM);
    wav5_dis13_data.resize(WAVLENNUM);
    wav5_dis14_data.resize(WAVLENNUM);
    wav5_dis15_data.resize(WAVLENNUM);
    wav5_dis16_data.resize(WAVLENNUM);
    wav5_dis17_data.resize(WAVLENNUM);
    wav5_dis18_data.resize(WAVLENNUM);
    wav5_dis19_data.resize(WAVLENNUM);
    wav5_dis20_data.resize(WAVLENNUM);
    wav5_dis21_data.resize(WAVLENNUM);
    wav5_dis22_data.resize(WAVLENNUM);
    wav5_dis23_data.resize(WAVLENNUM);
    wav5_dis24_data.resize(WAVLENNUM);
    wav5_dis25_data.resize(WAVLENNUM);
    wav5_dis26_data.resize(WAVLENNUM);
    wav5_dis27_data.resize(WAVLENNUM);
    wav5_dis28_data.resize(WAVLENNUM);
    wav5_dis29_data.resize(WAVLENNUM);
    wav5_dis30_data.resize(WAVLENNUM);
    wav5_dis31_data.resize(WAVLENNUM);
    wav5_dis32_data.resize(WAVLENNUM);

    wavelen1_data.push_back(wav1_dis1_data);
    wavelen1_data.push_back(wav1_dis2_data);
    wavelen1_data.push_back(wav1_dis3_data);
    wavelen1_data.push_back(wav1_dis4_data);
    wavelen1_data.push_back(wav1_dis5_data);
    wavelen1_data.push_back(wav1_dis6_data);
    wavelen1_data.push_back(wav1_dis7_data);
    wavelen1_data.push_back(wav1_dis8_data);
    wavelen1_data.push_back(wav1_dis9_data);
    wavelen1_data.push_back(wav1_dis10_data);
    wavelen1_data.push_back(wav1_dis11_data);
    wavelen1_data.push_back(wav1_dis12_data);
    wavelen1_data.push_back(wav1_dis13_data);
    wavelen1_data.push_back(wav1_dis14_data);
    wavelen1_data.push_back(wav1_dis15_data);
    wavelen1_data.push_back(wav1_dis16_data);
    wavelen1_data.push_back(wav1_dis17_data);
    wavelen1_data.push_back(wav1_dis18_data);
    wavelen1_data.push_back(wav1_dis19_data);
    wavelen1_data.push_back(wav1_dis20_data);
    wavelen1_data.push_back(wav1_dis21_data);
    wavelen1_data.push_back(wav1_dis22_data);
    wavelen1_data.push_back(wav1_dis23_data);
    wavelen1_data.push_back(wav1_dis24_data);
    wavelen1_data.push_back(wav1_dis25_data);
    wavelen1_data.push_back(wav1_dis26_data);
    wavelen1_data.push_back(wav1_dis27_data);
    wavelen1_data.push_back(wav1_dis28_data);
    wavelen1_data.push_back(wav1_dis29_data);
    wavelen1_data.push_back(wav1_dis30_data);
    wavelen1_data.push_back(wav1_dis31_data);
    wavelen1_data.push_back(wav1_dis32_data);

    wavelen2_data.push_back(wav2_dis1_data);
    wavelen2_data.push_back(wav2_dis2_data);
    wavelen2_data.push_back(wav2_dis3_data);
    wavelen2_data.push_back(wav2_dis4_data);
    wavelen2_data.push_back(wav2_dis5_data);
    wavelen2_data.push_back(wav2_dis6_data);
    wavelen2_data.push_back(wav2_dis7_data);
    wavelen2_data.push_back(wav2_dis8_data);
    wavelen2_data.push_back(wav2_dis9_data);
    wavelen2_data.push_back(wav2_dis10_data);
    wavelen2_data.push_back(wav2_dis11_data);
    wavelen2_data.push_back(wav2_dis12_data);
    wavelen2_data.push_back(wav2_dis13_data);
    wavelen2_data.push_back(wav2_dis14_data);
    wavelen2_data.push_back(wav2_dis15_data);
    wavelen2_data.push_back(wav2_dis16_data);
    wavelen2_data.push_back(wav2_dis17_data);
    wavelen2_data.push_back(wav2_dis18_data);
    wavelen2_data.push_back(wav2_dis19_data);
    wavelen2_data.push_back(wav2_dis20_data);
    wavelen2_data.push_back(wav2_dis21_data);
    wavelen2_data.push_back(wav2_dis22_data);
    wavelen2_data.push_back(wav2_dis23_data);
    wavelen2_data.push_back(wav2_dis24_data);
    wavelen2_data.push_back(wav2_dis25_data);
    wavelen2_data.push_back(wav2_dis26_data);
    wavelen2_data.push_back(wav2_dis27_data);
    wavelen2_data.push_back(wav2_dis28_data);
    wavelen2_data.push_back(wav2_dis29_data);
    wavelen2_data.push_back(wav2_dis30_data);
    wavelen2_data.push_back(wav2_dis31_data);
    wavelen2_data.push_back(wav2_dis32_data);

    wavelen3_data.push_back(wav3_dis1_data);
    wavelen3_data.push_back(wav3_dis2_data);
    wavelen3_data.push_back(wav3_dis3_data);
    wavelen3_data.push_back(wav3_dis4_data);
    wavelen3_data.push_back(wav3_dis5_data);
    wavelen3_data.push_back(wav3_dis6_data);
    wavelen3_data.push_back(wav3_dis7_data);
    wavelen3_data.push_back(wav3_dis8_data);
    wavelen3_data.push_back(wav3_dis9_data);
    wavelen3_data.push_back(wav3_dis10_data);
    wavelen3_data.push_back(wav3_dis11_data);
    wavelen3_data.push_back(wav3_dis12_data);
    wavelen3_data.push_back(wav3_dis13_data);
    wavelen3_data.push_back(wav3_dis14_data);
    wavelen3_data.push_back(wav3_dis15_data);
    wavelen3_data.push_back(wav3_dis16_data);
    wavelen3_data.push_back(wav3_dis17_data);
    wavelen3_data.push_back(wav3_dis18_data);
    wavelen3_data.push_back(wav3_dis19_data);
    wavelen3_data.push_back(wav3_dis20_data);
    wavelen3_data.push_back(wav3_dis21_data);
    wavelen3_data.push_back(wav3_dis22_data);
    wavelen3_data.push_back(wav3_dis23_data);
    wavelen3_data.push_back(wav3_dis24_data);
    wavelen3_data.push_back(wav3_dis25_data);
    wavelen3_data.push_back(wav3_dis26_data);
    wavelen3_data.push_back(wav3_dis27_data);
    wavelen3_data.push_back(wav3_dis28_data);
    wavelen3_data.push_back(wav3_dis29_data);
    wavelen3_data.push_back(wav3_dis30_data);
    wavelen3_data.push_back(wav3_dis31_data);
    wavelen3_data.push_back(wav3_dis32_data);

    wavelen4_data.push_back(wav4_dis1_data);
    wavelen4_data.push_back(wav4_dis2_data);
    wavelen4_data.push_back(wav4_dis3_data);
    wavelen4_data.push_back(wav4_dis4_data);
    wavelen4_data.push_back(wav4_dis5_data);
    wavelen4_data.push_back(wav4_dis6_data);
    wavelen4_data.push_back(wav4_dis7_data);
    wavelen4_data.push_back(wav4_dis8_data);
    wavelen4_data.push_back(wav4_dis9_data);
    wavelen4_data.push_back(wav4_dis10_data);
    wavelen4_data.push_back(wav4_dis11_data);
    wavelen4_data.push_back(wav4_dis12_data);
    wavelen4_data.push_back(wav4_dis13_data);
    wavelen4_data.push_back(wav4_dis14_data);
    wavelen4_data.push_back(wav4_dis15_data);
    wavelen4_data.push_back(wav4_dis16_data);
    wavelen4_data.push_back(wav4_dis17_data);
    wavelen4_data.push_back(wav4_dis18_data);
    wavelen4_data.push_back(wav4_dis19_data);
    wavelen4_data.push_back(wav4_dis20_data);
    wavelen4_data.push_back(wav4_dis21_data);
    wavelen4_data.push_back(wav4_dis22_data);
    wavelen4_data.push_back(wav4_dis23_data);
    wavelen4_data.push_back(wav4_dis24_data);
    wavelen4_data.push_back(wav4_dis25_data);
    wavelen4_data.push_back(wav4_dis26_data);
    wavelen4_data.push_back(wav4_dis27_data);
    wavelen4_data.push_back(wav4_dis28_data);
    wavelen4_data.push_back(wav4_dis29_data);
    wavelen4_data.push_back(wav4_dis30_data);
    wavelen4_data.push_back(wav4_dis31_data);
    wavelen4_data.push_back(wav4_dis32_data);

    wavelen5_data.push_back(wav5_dis1_data);
    wavelen5_data.push_back(wav5_dis2_data);
    wavelen5_data.push_back(wav5_dis3_data);
    wavelen5_data.push_back(wav5_dis4_data);
    wavelen5_data.push_back(wav5_dis5_data);
    wavelen5_data.push_back(wav5_dis6_data);
    wavelen5_data.push_back(wav5_dis7_data);
    wavelen5_data.push_back(wav5_dis8_data);
    wavelen5_data.push_back(wav5_dis9_data);
    wavelen5_data.push_back(wav5_dis10_data);
    wavelen5_data.push_back(wav5_dis11_data);
    wavelen5_data.push_back(wav5_dis12_data);
    wavelen5_data.push_back(wav5_dis13_data);
    wavelen5_data.push_back(wav5_dis14_data);
    wavelen5_data.push_back(wav5_dis15_data);
    wavelen5_data.push_back(wav5_dis16_data);
    wavelen5_data.push_back(wav5_dis17_data);
    wavelen5_data.push_back(wav5_dis18_data);
    wavelen5_data.push_back(wav5_dis19_data);
    wavelen5_data.push_back(wav5_dis20_data);
    wavelen5_data.push_back(wav5_dis21_data);
    wavelen5_data.push_back(wav5_dis22_data);
    wavelen5_data.push_back(wav5_dis23_data);
    wavelen5_data.push_back(wav5_dis24_data);
    wavelen5_data.push_back(wav5_dis25_data);
    wavelen5_data.push_back(wav5_dis26_data);
    wavelen5_data.push_back(wav5_dis27_data);
    wavelen5_data.push_back(wav5_dis28_data);
    wavelen5_data.push_back(wav5_dis29_data);
    wavelen5_data.push_back(wav5_dis30_data);
    wavelen5_data.push_back(wav5_dis31_data);
    wavelen5_data.push_back(wav5_dis32_data);

    //Temp置零
    memset(Temp,0,sizeof(int)*DISNUM*5);
    memset(Temp_1,0,sizeof(int)*DISNUM);
    memset(Temp_2,0,sizeof(int)*DISNUM);
    memset(Temp_3,0,sizeof(int)*DISNUM);
    memset(Temp_4,0,sizeof(int)*DISNUM);
    memset(Temp_5,0,sizeof(int)*DISNUM);
}

demodulation::~demodulation()
{
    delete[] all_wavelength_data;
}

void demodulation::read_config()
{
    QSettings *settings = new QSettings("C:/Qt_UDP_DTS/config.ini",QSettings::IniFormat);

    //Read
    settings->beginGroup("DETECTION");
    threshold = settings->value("ALG_THRESHOLD",-1).toInt();
    qDebug()<<"threshold= "<<threshold<<endl;
    settings->endGroup();

    delete settings;
}


void demodulation::run()
{

    while(1){
        /*--------------------------顺序光谱------------------------------*/
        /*------------------------5波长波分复用----------------------------*/
        /*-------------------每8192个数据执行一次解调-----------------------*/
        /*------每32个数据为一段，共256段数据，将数据重排成32*256的数组形式------*/
//        for(int i=0; i<DISNUM; ++i){
//            for(int j=0; j<WAVNUM; ++j){

//                while(m_mainwindow->m_udp_recv->CHdata2->isEmpty()){
//                    QThread::msleep(1);
//                }

//                all_wavelength_data[i][j]=m_mainwindow->m_udp_recv->CHdata2->pop();
//            }
//        }

        for(int j=0; j<WAVNUM; ++j){
            for(int i=0; i<DISNUM; ++i){

                while(m_mainwindow->m_udp_recv->CHdata2->isEmpty()){
                    QThread::msleep(1);
                }

                all_wavelength_data[i][j]=m_mainwindow->m_udp_recv->CHdata2->pop();
            }
        }

        qDebug()<<"Resort Recived CHdata Finished ! "<<endl;

        /*---单波长解调，按光源扫描波长整理数据----*/
        /*raw_data中波长顺序:  λ32、λ33 ... λ64、λ1、λ2 ... λ31*/
        /*实际UDP通信解调数据时按λ1、λ2 ... λ64的顺序来*/
//        for(int i=0;i<WAVNUM;i++){
//            for(int j=0;j<DISNUM;j++){

//                while(m_mainwindow->m_udp_recv->CHdata2->isEmpty()){
//                    QThread::msleep(1);
//                }

//                all_wavelength_data[i][j]=m_mainwindow->m_udp_recv->CHdata2->pop();
//            }
//        }

        /*------------------------------裁切光谱----------------------------*/
                    /*------长度为256的序列的1~50为波长1-------*/
                    /*------长度为256的序列的51~100为波长2-------*/
                    /*------长度为256的序列的101~150为波长3-------*/
                    /*------长度为256的序列的151~200为波长4-------*/
                    /*------长度为256的序列的201~250为波长5-------*/
                    /*------三个容器的容量均为32*50-------*/
        for(int m=0; m<DISNUM; ++m){
            //wave1 distance m
            copy(all_wavelength_data[m],all_wavelength_data[m]+WAVLENNUM,wavelen1_data[m].begin());
            //wave2 distance m
            copy(all_wavelength_data[m]+1+WAVLENNUM,all_wavelength_data[m]+2*WAVLENNUM,wavelen2_data[m].begin());
            //wave3 distance m
            copy(all_wavelength_data[m]+1+2*WAVLENNUM,all_wavelength_data[m]+3*WAVLENNUM,wavelen3_data[m].begin());
            //wave4 distance m
            copy(all_wavelength_data[m]+1+3*WAVLENNUM,all_wavelength_data[m]+4*WAVLENNUM,wavelen4_data[m].begin());
            //wave5 distance m
            copy(all_wavelength_data[m]+1+4*WAVLENNUM,all_wavelength_data[m]+5*WAVLENNUM,wavelen5_data[m].begin());
        }



        /*----------------------------温度判断算法---------------------------*/


        //定义阈值mean
        int mean1 = 0;
        int mean2 = 0;
        int mean3 = 0;
        int mean4 = 0;
        int mean5 = 0;

        //最大温度
        MAX_Temp_1 = 0;
        MAX_Temp_2 = 0;
        MAX_Temp_3 = 0;
        MAX_Temp_4 = 0;
        MAX_Temp_5 = 0;

        //波长1
        //第一个距离的波长值取平均后加一个阈值
        for(int n=0; n<WAVLENNUM; n++)
            mean1 += wavelen1_data[0][n];
        mean1 = mean1/WAVLENNUM + threshold;

        for(int a=1;a<DISNUM;a++){
            for(int b=0; b<WAVLENNUM; b++){
                if(wavelen1_data[a][b]>mean1 )
                    Temp_1[a] = (1549.5+0.08*b-1549.9-0.26)/0.01; //根据公式计算出温度值(校准)
            }
            //将最大温度置于MAX_Temp里
            if(Temp_1[a]>MAX_Temp_1) MAX_Temp_1 = Temp_1[a];
        }

        //波长2
        //第一个距离的波长值取平均后加一个阈值
        for(int n=0; n<WAVLENNUM; n++)
            mean2 += wavelen2_data[0][n];
        mean2 = mean2/WAVLENNUM + threshold;

        for(int a=1;a<DISNUM;a++){
            for(int b=0; b<WAVLENNUM; b++){
                if(wavelen2_data[a][b]>mean1 )
                    Temp_2[a] = (1549.5+0.08*b-1549.9-0.1)/0.01;  //根据公式计算出温度值(校准)
            }
            //将最大温度置于MAX_Temp里
            if(Temp_2[a]>MAX_Temp_2) MAX_Temp_2 = Temp_2[a];
        }

        //波长3
        //第一个距离的波长值取平均后加一个阈值
        for(int n=0; n<WAVLENNUM; n++)
            mean3 += wavelen3_data[0][n];
        mean3 = mean3/WAVLENNUM + threshold;

        for(int a=1;a<DISNUM;a++){
            for(int b=0; b<WAVLENNUM ; b++){
                if(wavelen3_data[a][b]>mean1 )
                    Temp_3[a] = (1549.5+0.08*b-1549.9-0.02)/0.01;  //根据公式计算出温度值(校准)
            }
            //将最大温度置于MAX_Temp里
            if(Temp_3[a]>MAX_Temp_3) MAX_Temp_3 = Temp_3[a];
        }

        //波长4
        //第一个距离的波长值取平均后加一个阈值
        for(int n=0; n<WAVLENNUM; n++)
            mean4 += wavelen4_data[0][n];
        mean4 = mean4/WAVLENNUM + threshold;

        for(int a=1;a<DISNUM;a++){
            for(int b=0; b<WAVLENNUM ; b++){
                if(wavelen4_data[a][b]>mean1 )
                    Temp_4[a] = (1549.5+0.08*b-1549.9+0.05)/0.01;  //根据公式计算出温度值(校准)
            }
            //将最大温度置于MAX_Temp里
            if(Temp_4[a]>MAX_Temp_4) MAX_Temp_4 = Temp_4[a];
        }

        //波长5
        //第一个距离的波长值取平均后加一个阈值
        for(int n=0; n<WAVLENNUM; n++)
            mean5 += wavelen5_data[0][n];
        mean5 = mean5/WAVLENNUM + threshold;

        for(int a=1;a<DISNUM;a++){
            for(int b=0; b<WAVLENNUM ; b++){
                if(wavelen5_data[a][b]>mean1 )
                    Temp_5[a] = (1549.5+0.08*b-1549.9+0.05)/0.01; //根据公式计算出温度值(校准)
            }
            //将最大温度置于MAX_Temp里
            if(Temp_5[a]>MAX_Temp_5) MAX_Temp_5 = Temp_5[a];
        }

        qDebug()<<"Temp Distance finished ! "<<endl;
    }

}

