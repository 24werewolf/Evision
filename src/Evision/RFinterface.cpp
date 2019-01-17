#include "RFinterface.h"
#include "EvisionUtils.h"
#include "QGraphicsScene"
#include "PointCloudUtils.h"
#include <QFileDialog>
#include "StereoMatch.h"

//ֱ��������ͼ,�����ò���
RFinterface::RFinterface(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.checkBox_leftOK->setEnabled(false);
	ui.checkBox_dispOK->setEnabled(false);
	ui.checkBox_pointcloudOK->setEnabled(false);
	ui.pushButton_start->setEnabled(false);
}

//�ⲿ���ò���,��������ͼ
RFinterface::RFinterface(cv::Mat img, cv::Mat disp, cv::Mat xyz, QWidget* parent) : QWidget(parent)
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

RFinterface::~RFinterface()
{
}
//��O���ڻ�ͼ
void RFinterface::printImgToO(cv::Mat value)
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
void RFinterface::printImgToD(cv::Mat value)
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

void RFinterface::checkEnable()
{
	if(ui.checkBox_leftOK->isChecked()&&ui.checkBox_dispOK->isChecked()&&ui.checkBox_pointcloudOK->isChecked())
	{
		ui.pushButton_start->setEnabled(true);
	}
}

//��Ӧ����ƶ�
void RFinterface::onMouseMove(int x, int y)
{
	ui.lineEdit_ImgX->setText(QString::fromStdString(std::to_string(x)));
	ui.lineEdit_ImgY->setText(QString::fromStdString(std::to_string(y)));

}
//��Ӧ����������
void RFinterface::onMouseLButtonDown(int x, int y)
{
	if (started)
	{
		m_ObjectDistance = 16 * depth.at<float>(y, x);
		ui.lineEdit_Res->setText(QString::fromStdString(std::to_string(m_ObjectDistance)));
	}
}
//��Ӧ����Ҽ�����
void RFinterface::onMouseRButtonDown(int x, int y)
{

}

void RFinterface::onSelectDisparityMap()
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

void RFinterface::onSelectleftMap()
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

void RFinterface::onSelectPointcloudFile()
{
	QFileDialog * fileDialog = new QFileDialog();
	fileDialog->setWindowTitle(QStringLiteral("��ѡ������ļ�"));
	fileDialog->setNameFilter(QStringLiteral("�����ļ�(*.xml *.yml *.yaml)"));
	fileDialog->setFileMode(QFileDialog::ExistingFile);
	if (fileDialog->exec() == QDialog::Accepted)
	{
		xyz = StereoMatch::readXYZ(fileDialog->selectedFiles().at(0).toStdString().c_str());
		ui.checkBox_pointcloudOK->setChecked(true);
		checkEnable();
	}
}

void RFinterface::onStart()
{

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
	ui.pushButton_selectDisp->setEnabled(false);
	ui.pushButton_selectLeft->setEnabled(false);
	ui.pushButton_selectPointCloud->setEnabled(false);
	started = true;
}
