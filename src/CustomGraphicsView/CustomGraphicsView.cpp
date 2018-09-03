#include "CustomGraphicsView.h"
#include "QMouseEvent"
CustomGraphicsView::CustomGraphicsView(QWidget *parent)
	: QGraphicsView(parent)
{
}
//�������¼�
void CustomGraphicsView::mousePressEvent(QMouseEvent* event)
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
void CustomGraphicsView::mouseMoveEvent(QMouseEvent* event)
{
	emit mouseMove(event->pos().x(), event->pos().y());
}
