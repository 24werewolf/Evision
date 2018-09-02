#include "RFScene.h"
#include "QMouseEvent"
RFScene::RFScene(QWidget  *parent)
	: QGraphicsView(parent)
{
}

RFScene::~RFScene()
{
}
//�������¼�
void RFScene::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::MouseButton::LeftButton)
	{
		emit mouseLDown(event->pos().x(), event->pos().y());
	}
	if (event->button() == Qt::MouseButton::RightButton)
	{
		emit mouseRDown(event->pos().x(), event->pos().y());
	}	
}

//����ƶ��¼�
void RFScene::mouseMoveEvent(QMouseEvent* event)
{
	emit mouseMove(event->pos().x(), event->pos().y());
}

