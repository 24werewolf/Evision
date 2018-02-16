#include "QuantEvision_Qt.h"
#include "Calibration.h"
#include "Match.h"
#include "Reconstruction.h"
#include "Measurement.h"

QuantEvision_Qt::QuantEvision_Qt(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//Ĭ�����ز����
	ui.dockWidget_RangeGuide->setHidden(true);
}
//����/�رղ����
void QuantEvision_Qt::RangeGuide()
{
	if (ui.dockWidget_RangeGuide->isHidden())
	{
		ui.dockWidget_RangeGuide->setHidden(false);
		//������Ѿ���ʾ,��ʼ����๦��
	}
	else
	{
		ui.dockWidget_RangeGuide->setHidden(true);
		//������Ѿ�����,ע����๦��
	}
}
//�����궨����
void QuantEvision_Qt::ShowCalibrate()
{
	Calibration * _Calibration = new Calibration();
	ui.mdiArea->addSubWindow(_Calibration);
	_Calibration->show();
}
//����ƥ�����
void QuantEvision_Qt::ShowMatch()
{
	Match * _Match = new Match();
	ui.mdiArea->addSubWindow(_Match);
	_Match->show();
}
//������ά�ؽ�����
void QuantEvision_Qt::ShowReconstruct()
{
	Reconstruction * _Reconstruction = new Reconstruction();
	ui.mdiArea->addSubWindow(_Reconstruction);
	_Reconstruction->show();
}
//����������
void QuantEvision_Qt::ShowRange()
{
	Measurement * _Measurement = new Measurement();
	ui.mdiArea->addSubWindow(_Measurement);
	_Measurement->show();
}
