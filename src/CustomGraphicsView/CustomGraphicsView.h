#pragma once

#include <QtWidgets/QGraphicsView>
#include <QtUiPlugin/QDesignerExportWidget>
/*
 * �Զ����Designer���,ʹ��release�汾����ɹ���,���ڽű��������Զ����ע��
 * ע��ű��ڽ�������ļ���/Scripts��
 * ʹ��debug����,���ᴥ��ע��
 * ע��:ע��ű���ȷִ�е�ǰ����QtDesigner�Ѿ��ر�
 * 
 * �źŲ۵İ󶨿�����Desinger�����
 * 
 * QDESIGNER_WIDGET_EXPORT�����������ǰѴ��������lib��,����������,lib�о�û������Զ�����
 * ������ȻҲ����designer��ʹ�ò��,�ڴ���������Ҳ����,����ȴ�޷�����.
 * ֢״�������ӵ����Զ�����Ĺ��캯��ʱ,�ᷢ���ⲿ���Ŵ���,link error 2019
 */

class QDESIGNER_WIDGET_EXPORT CustomGraphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	CustomGraphicsView(QWidget *parent = Q_NULLPTR);
protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
signals:
	void mouseMove(int x, int y);
	void mouseLDown(int x, int y);
	void mouseRDown(int x, int y);
};
