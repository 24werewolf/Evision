#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Evision.h"
#include "EvisionParamEntity.h"
#include "EvisionController.h"

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
	//��ť
	void setDefaultCalibParam();
	void doCalib();
	void setDefaultMatchParam();
	void doMatch();
	void getDistance();
	void getGap();
	//ֵ�����¼�,��ӦUIԪ�صı仯
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
	//ƥ�����
	void valueChanged_MinDisp(int value);
	void onParamChanged_MinDisp();
	void valueChanged_uniradio(int value);
	void onParamChanged_uniradio();
	void valueChanged_specwinsz(int value);
	void onParamChanged_specwinsz();
	void valueChanged_MaxDisp(int value);
	void onParamChanged_MaxDisp();
	void valueChanged_Specrange(int value);
	void onParamChanged_Specrange();
	void valueChanged_Prefilcap(int value);
	void onParamChanged_Prefilcap();
	void valueChanged_SadWinSize(int value);
	void onParamChanged_SadWinSize();
	void valueChanged_TextThread(int value);
	void onParamChanged_TextThread();
	void valueChanged_MaxDifdisp2(int value);
	void onParamChanged_MaxDifdisp2();

	//ƥ���㷨
	void onClicked_BM(bool value);
	void onParamChanged_BM();
	void onClicked_SGBM(bool value);
	void onParamChanged_SGBM();
	void onClicked_VAR(bool value);
	void onParamChanged_VAR();

	void onParamChanged_Distance();
	//��������ͼ������ͼ
	void onParamChanged_imgLtoShow();
	void onParamChanged_imgRtoShow();
	void onParamChanged_imgDtoShow();

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
