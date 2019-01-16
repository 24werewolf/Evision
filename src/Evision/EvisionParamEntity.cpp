#include "EvisionParamEntity.h"

//���캯����˽�е�
EvisionParamEntity::EvisionParamEntity(QObject * parent) : QObject(parent)
{ 
}

//��ȡʵ��(����ģʽ)
EvisionParamEntity * EvisionParamEntity::getInstance()
{
     static EvisionParamEntity *m_pInstance;
     if (m_pInstance == NULL) //�ж��Ƿ��һ�ε���
         m_pInstance = new EvisionParamEntity();
     return m_pInstance;
}

EvisionParamEntity::~EvisionParamEntity()
{
}

float EvisionParamEntity::getDistance()
{
	return Distance;
}
void EvisionParamEntity::setDistance(float value)
{
	Distance = value;
	emit paramChanged_distance();
}

//cv::Mat EvisionParamEntity::getImageLtoShow()
//{
//	return imgLtoShow;
//}
//void EvisionParamEntity::setImageLtoShow(cv::Mat value)
//{
//	imgLtoShow = value;
//	emit paramChanged_ImageLtoShow();
//}

//cv::Mat EvisionParamEntity::getImageRtoShow()
//{
//	return imgRtoShow;
//}
//void EvisionParamEntity::setImageRtoShow(cv::Mat value)
//{
//	imgRtoShow = value;
//	emit paramChanged_ImageRtoShow();
//}

//cv::Mat EvisionParamEntity::getImageDtoShow()
//{
//	return imgDtoShow;
//}
//
//void EvisionParamEntity::setImageDtoShow(cv::Mat value)
//{
//	imgDtoShow = value;
//	emit paramChanged_ImageDtoShow();
//}

QString EvisionParamEntity::getStatusBarText()
{
	return StatusBarText;
}
void EvisionParamEntity::setStatusBarText(QString value=QStringLiteral("����"))
{
	StatusBarText = value;
	emit paramChanged_StatusBar();
}

cv::Mat EvisionParamEntity::getDisparity()
{
	return disparity;
}

void EvisionParamEntity::setDisparity(cv::Mat value)
{
	disparity = value;
}

cv::Mat EvisionParamEntity::getXYZ()
{
	return xyz;
}

void EvisionParamEntity::setXYZ(cv::Mat value)
{
	xyz = value;
}

cv::Mat EvisionParamEntity::getQ()
{
	return Q;
}

void EvisionParamEntity::setQ(cv::Mat value)
{
	Q = value;
}
