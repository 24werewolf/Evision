#pragma once
#include "EvisionParamEntity.h"
#include <qstringlist.h>

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
};

