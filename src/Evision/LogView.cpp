#include "LogView.h"

LogView::LogView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowFlags(this->windowFlags() &~Qt::WindowMinMaxButtonsHint);//��ֹ������С��
	this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
}

LogView::~LogView()
{
}
