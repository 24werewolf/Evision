#pragma once

#include <QWidget>
#include "ui_Calibration.h"
#include <core/affine.hpp>
#include "Calibrater.h"
#include <QMetaType>
#include <core/core.hpp>

class Calibration : public QWidget
{
	Q_OBJECT

public:
	Calibration(QWidget *parent = Q_NULLPTR);
	~Calibration();

private:
	Ui::Calibration ui;
private:
	//Calibrater * m_stereoCalibrator;//�궨��ҵ���߼�
	QStringList ImageListL, ImageListR;//��ͼƬ�궨ʱ��Ҫ������ͼƬ
	void ShowImage(cv::Mat imgL, cv::Mat imgR);//��ʾMat��������
	QString WorkPath=".\\";
	cv::Mat imgLtoShow, imgRtoShow;
signals:
	void IsTimeToShowImages();
public slots:
	void OnShowImages();					//��Ӧ��ʾͼƬ���ź�
	void OnDefaultBoardParams();            //�궨��Ĭ�ϲ���
	void OnChecked_Bouguet();				//���"Bouguet"ѡ��
	void OnChecked_Hartley();				//���"Hartley"ѡ��
	void OnChecked_Fi();					//���"Fi"ѡ��
	void OnChecked_Uig();					//���"Uig"ѡ��
	void OnChecked_Sfl();					//���"SFI"ѡ��
	void OnChecked_FPP();					//���"FPPѡ��"
	void OnChecked_Far();					//���"FAR"ѡ��
	void OnChooseImages();					//ѡ��궨ͼƬ
	void OnCalibrateFromImage();			//��ͼƬ�궨
	void OnChanged_LCameraComboBox();		//���������ͷ
	void OnChanged_RChangeComboBox();		//���������ͷ
	void OnChanged_ResolutionComboBox();	//����ֱ���
	void OnRefreshCameras();				//ˢ������ͷ
	void OnCamerasPowerOn();				//����/�ر�����ͷ
	void OnCalibrateFromCameras();			//������ͷ�궨
	void OnChooseCalibrateFile();			//ѡ��궨�ļ�
	void OnCalibrateFromFile();				//���ļ��궨

	void OnShowImg();						//����:��ʾͼƬ
};
