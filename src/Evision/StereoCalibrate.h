#pragma once
#include <QThread>
#include <core/mat.hpp>
#include "EvisionParamEntity.h"
#include "CalibrateParamEntity.h"

class StereoCalibrate:public QThread
{
	Q_OBJECT
private:
	std::vector<std::string>* imagelist;
	std::vector<std::string>* imagelistL;
	std::vector<std::string>* imagelistR;
	cv::Size boardSize;
	float squareSize;
	bool useCalibrated; //true=ʹ��BOUGUET��������,false=ʹ��HARTLEY��������
	bool showRectified; //�Ƿ���ʾ�궨ͼƬ�Ľ������

	std::string intrFilename;
	std::string extrFilename;
	CalibrateParamEntity * m_entity;
public:
	//�����б�
	StereoCalibrate(std::vector<std::string>* imagelist,
		cv::Size boardSize,
		float squareSize,
		bool useCalibrated,
		bool showRectified,
		QObject *parent = 0);
	//���������б�
	StereoCalibrate(std::vector<std::string>* imagelistL,
		std::vector<std::string>* imagelistR,
		cv::Size boardSize,
		float squareSize,
		bool useCalibrated,
		bool showRectified,
		QObject *parent = 0);

	~StereoCalibrate();
	void run_old() ;
	void run();
signals:
	void openMessageBox(QString, QString);
};

