#pragma once

#include <QWidget>
#include "ui_Calibrater.h"
#include "CalibrateParamEntity.h"
#include "CalibrateController.h"
/*
 * �궨:view
 */
class Calibrater : public QWidget
{
	Q_OBJECT

public:
	Calibrater(QWidget *parent = Q_NULLPTR);
	~Calibrater();

private:
	Ui::Calibrater ui;
	CalibrateParamEntity * m_calib_entity;
	CalibrateController * m_calib_controller;
public slots:
	void setDefaultCalibParam();
	void doCalib();
	//�궨����ֵ�����¼�
	void onValueChanged_BoardWidth(QString value);
	void onParamChanged_BoardWidth() const;

	void onValueChanged_BoardHeight(QString value);
	void onParamChanged_BoardHeight();

	void onValueChanged_SquareSize(QString value);
	void onParamChanged_SquareSize();
	//�궨��־λֵ�����¼�
	void onClicked_showRectified(bool value);
	void onParamChanged_showRectified();

	//�궨�㷨
	void onClicked_Bouguet(bool value);
	void onParamChanged_Bouguet();

	void onClicked_Hartley(bool value);
	void onParamChanged_Hartley();

	void onParamChanged_imgLtoShow();//��������ͼ
	void onParamChanged_imgRtoShow();//��������ͼ

	void onParamChanged_msgBuffer();//��Ϣ�������
};
