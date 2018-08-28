#pragma once
#include "EvisionParamEntity.h"

class EvisionController
{
private:
	EvisionParamEntity * m_entity;
	QStringList ImageListL, ImageListR;//��ͼƬ�궨ʱ��Ҫ������ͼƬ
public:
	EvisionController();
	~EvisionController();
	void setDefaultCalibParamCommand();
	void CalibrateCommand();
	void setDefaultMatchParamCommand();
	void MatchCommand();
private:
	void CalibrateFromImage();
	void StereoCalib(const std::vector<std::string>& imagelist, 
					cv::Size boardSize, 
					float squareSize, 
					bool displayCorners, 
					bool useCalibrated , 
					bool showRectified );
};

