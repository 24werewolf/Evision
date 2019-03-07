#pragma once

#include <QWidget>
#include "ui_RulerView.h"
#include <core/core.hpp>
#include <QtWidgets/QGraphicsView>
/*
 * ���𽻻�ʽ�������ܵ�view
 */
class RulerView : public QWidget
{
	Q_OBJECT

public:
	RulerView(QWidget *parent = Q_NULLPTR);
	~RulerView();

private:
	Ui::RulerView ui;

	cv::Mat img;		   //ԭͼ
	cv::Mat RawDisp;	   //ԭʼ�Ӳ�ͼ
	cv::Mat Q;			   //Q����
	cv::Mat image3D;	   //
	float scaleFactor=1.0;     //��������
	cv::Mat disparityGary; //�Ҷ��Ӳ�ͼ
	bool DispIsShowing = true;
	QGraphicsScene *sceneL;
	bool started = false;
private:
	void printImgToO(cv::Mat value);
	void checkEnable();
public slots:
	void onMouseMove(int x, int y);
	void onMouseLButtonDown(int x, int y);
	void onMouseRButtonDown(int x, int y);

	void onSelectRawDispFile();
	void onSelectOriginImg();
	void onSelectCameraParamFile();
	void onStart();
	void onSwitchImageToShow();
};
