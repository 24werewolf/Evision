#include "RulerView.h"
#include "EvisionUtils.h"
#include "QGraphicsScene"
#include "PointCloudUtils.h"
#include <QFileDialog>
#include "StereoMatch.h"
#include <QMessageBox>

//ֱ��������ͼ,�����ò���
RulerView::RulerView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.checkBox_leftOK->setEnabled(false);
	ui.checkBox_dispOK->setEnabled(false);
	ui.checkBox_pointcloudOK->setEnabled(false);
	ui.pushButton_start->setEnabled(false);
}

//�ⲿ���ò���,��������ͼ
RulerView::RulerView(cv::Mat img, cv::Mat disp, cv::Mat xyz, QWidget* parent) : QWidget(parent)
{
	ui.setupUi(this);
	this->img  = img;
	this->disp = disp;
	this->xyz  = xyz;

	std::vector<cv::Mat> xyzSet;
	split(xyz, xyzSet);
	xyzSet[2].copyTo(depth);

	std::vector<PointCloudUtils::ObjectInfo> objectInfos;
	PointCloudUtils pointCloudAnalyzer;
	if (pointCloudAnalyzer.detectNearObject(disp, xyz, objectInfos) == 0)
	{
		//ʧ�ܴ���
		return;
	}
	pointCloudAnalyzer.showObjectInfo(objectInfos, img);//������ͼ�����������ʶ��Ŀ�

	printImgToD(disp);
	printImgToO(img);
}

RulerView::~RulerView()
{
}
//��O���ڻ�ͼ
void RulerView::printImgToO(cv::Mat value)
{
	QImage QImage = EvisionUtils::cvMat2QImage(value);
	QGraphicsScene *sceneL = new QGraphicsScene;
	sceneL->addPixmap(QPixmap::fromImage(QImage));
	ui.customGraphicsView_O->setScene(sceneL);
	ui.customGraphicsView_O->setMinimumSize(QImage.width(), QImage.height());
	ui.customGraphicsView_O->setMaximumSize(QImage.width(), QImage.height());
	ui.customGraphicsView_O->show();
	ui.customGraphicsView_O->update();
}
//��D���ڻ�ͼ
void RulerView::printImgToD(cv::Mat value)
{
	QImage QImage = EvisionUtils::cvMat2QImage(value);
	QGraphicsScene *sceneL = new QGraphicsScene;
	sceneL->addPixmap(QPixmap::fromImage(QImage));
	ui.customGraphicsView_D->setScene(sceneL);
	ui.customGraphicsView_D->setMinimumSize(QImage.width(), QImage.height());
	ui.customGraphicsView_D->setMaximumSize(QImage.width(), QImage.height());
	ui.customGraphicsView_D->show();
	ui.customGraphicsView_D->update();
}

void RulerView::checkEnable()
{
	if(ui.checkBox_leftOK->isChecked()&&ui.checkBox_dispOK->isChecked()&&ui.checkBox_pointcloudOK->isChecked())
	{
		ui.pushButton_start->setEnabled(true);
	}
}

//��Ӧ����ƶ�
void RulerView::onMouseMove(int x, int y)
{
	ui.lineEdit_ImgX->setText(QString::fromStdString(std::to_string(x)));
	ui.lineEdit_ImgY->setText(QString::fromStdString(std::to_string(y)));

}
//��Ӧ����������
void RulerView::onMouseLButtonDown(int x, int y)
{
	if (started)
	{
		m_ObjectDistance = 16 * depth.at<float>(y, x);
		ui.lineEdit_Res->setText(QString::fromStdString(std::to_string(m_ObjectDistance)));
	}
}
//��Ӧ����Ҽ�����
void RulerView::onMouseRButtonDown(int x, int y)
{

}

void RulerView::onSelectDisparityMap()
{
	QFileDialog * fileDialog = new QFileDialog();
	fileDialog->setWindowTitle(QStringLiteral("��ѡ���Ӳ�ͼ"));
	fileDialog->setNameFilter(QStringLiteral("ͼƬ�ļ�(*.jpg *.png *.jpeg)"));
	fileDialog->setFileMode(QFileDialog::ExistingFile);
	if (fileDialog->exec() == QDialog::Accepted)
	{
		this->disp = cv::imread(fileDialog->selectedFiles().at(0).toStdString());
		ui.checkBox_dispOK->setChecked(true);
		checkEnable();
	}
}

void RulerView::onSelectleftMap()
{
	QFileDialog * fileDialog = new QFileDialog();
	fileDialog->setWindowTitle(QStringLiteral("��ѡ�����������ѡ�Ӳ�ͼ������ͼ"));
	fileDialog->setNameFilter(QStringLiteral("ͼƬ�ļ�(*.jpg *.png *.jpeg)"));
	fileDialog->setFileMode(QFileDialog::ExistingFile);
	if (fileDialog->exec() == QDialog::Accepted)
	{
		this->img = cv::imread(fileDialog->selectedFiles().at(0).toStdString());
		ui.checkBox_leftOK->setChecked(true);
		checkEnable();
	}
}

void RulerView::onSelectPointcloudFile()
{
	QFileDialog * fileDialog = new QFileDialog();
	fileDialog->setWindowTitle(QStringLiteral("��ѡ������ļ�"));
	fileDialog->setNameFilter(QStringLiteral("�����ļ�(*.xml *.yml *.yaml)"));
	fileDialog->setFileMode(QFileDialog::ExistingFile);
	if (fileDialog->exec() == QDialog::Accepted)
	{
		if (EvisionUtils::read_PointCloud(fileDialog->selectedFiles().at(0).toStdString(), &xyz))
		{
			ui.checkBox_pointcloudOK->setChecked(true);
			checkEnable();
		}
		else
		{
			QMessageBox::information(NULL, QStringLiteral("����"), QStringLiteral("���ƶ�ȡʧ��!"));
		}

	}
}

void RulerView::onStart()
{

	std::vector<cv::Mat> xyzSet;
	split(xyz, xyzSet);
	xyzSet[2].copyTo(depth);

	//std::vector<PointCloudUtils::ObjectInfo> objectInfos;
	//PointCloudUtils pointCloudAnalyzer;
	//if (pointCloudAnalyzer.detectNearObject(disp, xyz, objectInfos) == 0)
	//{
	//	//ʧ�ܴ���
	//	return;
	//}
	//pointCloudAnalyzer.showObjectInfo(objectInfos, img);//������ͼ�����������ʶ��Ŀ�
	//cv::imwrite("F:\\disp.jpg", disp);
	//cv::imwrite("F:\\xyz.jpg", xyz);
	//cv::imwrite("F:\\depth,jpg", depth);

	printImgToD(disp);
	printImgToO(img);
	ui.pushButton_selectDisp->setEnabled(false);
	ui.pushButton_selectLeft->setEnabled(false);
	ui.pushButton_selectPointCloud->setEnabled(false);
	started = true;
}
