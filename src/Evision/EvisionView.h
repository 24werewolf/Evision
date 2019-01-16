#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Evision.h"
#include "EvisionParamEntity.h"
#include "EvisionController.h"
#include <QLabel>

class EvisionView : public QMainWindow
{
	Q_OBJECT

public:
	EvisionView(QWidget *parent = Q_NULLPTR);

private:
	Ui::EvisionClass ui;
	EvisionParamEntity * m_entity;
	EvisionController * m_controller;
	QLabel *msgLabel;
public slots:
	void getDistance();//��ť

	//�˵�
	void onCamera();
	void onStereoCamera();
	void onShowPointCloud();//��ʾ����

	void on_action_calibrate_view();//�����궨��ͼ
	void on_action_stereoMatch_view();//����ƥ����ͼ
	void on_action_Measure_view();//������������

	void onTestAlltheParam();
	//״̬��
	void onParamChanged_StatusBarText();
	
	/*
	 * �������µ����:
	 *	ͼƬ��ʾ����
	 *	ƥ�������textarea
	 *	����ֵ��ʾ
	 * �ú������ĳ������,���������仯��ʱ����½���
	 */
};
