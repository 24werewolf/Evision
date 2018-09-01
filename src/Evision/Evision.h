#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Evision.h"
#include "ParamEntity.h"

class Evision : public QMainWindow
{
	Q_OBJECT

public:
	Evision(QWidget *parent = Q_NULLPTR);

private:
	Ui::EvisionClass ui;
	ParamEntity * m_entity;
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
	void onValueChanged_Alpha(QString value);
	void onParamChanged_Alpha();
	void onValueChanged_nBoards(QString value);
	void onParamChanged_nBoards();
	//�궨��־λֵ�����¼�
	void onClicked_FI(bool value);
	void onParamChanged_FI();
	void onClicked_UIG(bool value);
	void onParamChanged_UIG();
	void onClicked_SFL(bool value);
	void onParamChanged_SFL();
	void onClicked_FPP(bool value);
	void onParamChanged_FPP();
	void onClicked_FAR(bool value);
	void onParamChanged_FAR();
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
	void valueChanged_Levels(int value);
	void onParamChanged_Levels();
	void valueChanged_PyrScale(int value);
	void onParamChanged_PyrScale();
	void valueChanged_PolyN(int value);
	void onParamChanged_PolyN();
	void valueChanged_PolySigma(int value);
	void onParamChanged_PolySigma();
	void valueChanged_Fi(int value);
	void onParamChanged_Fi();
	void valueChanged_Lambda(int value);
	void onParamChanged_Lambda();
	//ƥ���㷨
	void onClicked_BM(bool value);
	void onParamChanged_BM();
	void onClicked_SGBM(bool value);
	void onParamChanged_SGBM();
	void onClicked_VAR(bool value);
	void onParamChanged_VAR();

	void onParamChanged_Distance();

	void onTestAlltheParam();
	/*
	 * �������µ����:
	 *	ͼƬ��ʾ����
	 *	ƥ�������textarea
	 *	����ֵ��ʾ
	 * �ú������ĳ������,���������仯��ʱ����½���
	 */
};
