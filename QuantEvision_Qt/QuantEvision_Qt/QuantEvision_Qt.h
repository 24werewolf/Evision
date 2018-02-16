#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QuantEvision_Qt.h"

class QuantEvision_Qt : public QMainWindow
{
	Q_OBJECT

public:
	QuantEvision_Qt(QWidget *parent = Q_NULLPTR);

private:
	Ui::QuantEvision_QtClass ui;
public slots:
	void RangeGuide();		//����/�رղ����
	void ShowCalibrate();	//�����궨����
	void ShowMatch();		//����ƥ�����
	void ShowReconstruct();	//������ά�ؽ�����
	void ShowRange();		//����������

};
