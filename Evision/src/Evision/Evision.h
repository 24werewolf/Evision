#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Evision.h"

class Evision : public QMainWindow
{
	Q_OBJECT

public:
	Evision(QWidget *parent = Q_NULLPTR);

private:
	Ui::EvisionClass ui;
public slots:
	//��ť
	void setDefaultCalibParam();
	void doCalib();
	void setDefaultMatchParam();
	void doMatch();
	void getDistance();
	void getGap();
	//ֵ�����¼�
	void onValueChanged_BoardWidth(QString value);
	void onValueChanged_BoardHeight(QString value);
	void onValueChanged_SquareSize(QString value);
	void onValueChanged_Alpha(QString value);
	void onValueChanged_nBoards(QString value);
	
		
		
};
