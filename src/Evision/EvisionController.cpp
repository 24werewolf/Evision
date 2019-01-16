#include "EvisionController.h"
#include <QMessageBox>
#include "QFileDialog"
#include <imgcodecs/imgcodecs_c.h>
#include <imgproc.hpp>
#include <highgui.hpp>
#include <iostream>
#include <calib3d/calib3d.hpp>
#include "StereoCalibrate.h"
#include "QMessageBox"
#include "StereoMatch.h"
#include "PointCloudUtils.h"
#include "RFinterface.h"
#include "Camera.h"
#include "StereoCamera.h"


EvisionController::EvisionController(QObject * parent):QObject(parent)
{
	m_entity = EvisionParamEntity::getInstance();
}

EvisionController::~EvisionController()
{
}


//����:����
void EvisionController::getDistanceCommand()
{
	cv::Mat img, disp, xyz;

		//ѯ���ļ�λ�ò��������
		QString imgFile, dispFile, xyzFile;
		QFileDialog * fileDialog = new QFileDialog();
		fileDialog->setWindowTitle(QStringLiteral("��ѡ���Ӳ�ͼ"));
		fileDialog->setNameFilter(QStringLiteral("ͼƬ�ļ�(*.jpg *.png *.jpeg)"));
		fileDialog->setFileMode(QFileDialog::ExistingFile);
		if (fileDialog->exec() == QDialog::Accepted)
		{
			imgFile = fileDialog->selectedFiles().at(0);
			fileDialog->setWindowTitle(QStringLiteral("��ѡ�����������ѡ�Ӳ�ͼ������ͼ"));
			if (fileDialog->exec() == QDialog::Accepted)
			{
				dispFile = fileDialog->selectedFiles().at(0);

				QFileDialog * fileDialog2 = new QFileDialog();
				fileDialog2->setWindowTitle(QStringLiteral("��ѡ������ļ�"));
				fileDialog2->setNameFilter(QStringLiteral("�����ļ�(*.xml *.yml *.yaml)"));
				fileDialog2->setFileMode(QFileDialog::ExistingFile);
				if (fileDialog2->exec() == QDialog::Accepted)
				{
					xyzFile = fileDialog2->selectedFiles().at(0);
					if (imgFile.isEmpty()||dispFile.isEmpty()||xyzFile.isEmpty())
					{
						//�ļ���ȫ,������ʾ�˳�
						QMessageBox::information(NULL, QStringLiteral("����"), QStringLiteral("��ѡ����Ч���ļ�!"));
						return;
					}
					else
					{
						//�ļ���ȫ,��ȡ����
						img= cv::imread(imgFile.toStdString());
						disp= cv::imread(dispFile.toStdString());
						xyz = StereoMatch::readXYZ(xyzFile.toStdString().c_str());
					}
				}
				else
				{
					QMessageBox::information(NULL, QStringLiteral("����"), QStringLiteral("��ѡ����Ч���ļ�!"));
					return;
				}
			}
			else
			{
				QMessageBox::information(NULL, QStringLiteral("����"), QStringLiteral("��ѡ����Ч���ļ�!"));
				return;
			}
		}
		else
		{
			QMessageBox::information(NULL, QStringLiteral("����"), QStringLiteral("��ѡ����Ч���ļ�!"));
			return;
		}
	

	//׼����������,����������е����λ��,˵������������ֵ��������Чֵ,��ʱ������������ʽ������view
	//img,disp.xyz
	RFinterface * _Rfinterface = new RFinterface(img, disp, xyz);
	_Rfinterface->show();
}
//����:��ʾ����
void EvisionController::ShowPointCloudCommand()
{
	QFileDialog * fileDialog2 = new QFileDialog();
	fileDialog2->setWindowTitle(QStringLiteral("��ѡ������ļ�"));
	fileDialog2->setNameFilter(QStringLiteral("�����ļ�(*.xml *.yml *.yaml)"));
	fileDialog2->setFileMode(QFileDialog::ExistingFile);
	if (fileDialog2->exec() == QDialog::Accepted)
	{
		QString xyzFile = fileDialog2->selectedFiles().at(0);
		cv::Mat xyz = StereoMatch::readXYZ(xyzFile.toStdString().c_str());
	}
	else
	{
		QMessageBox::information(NULL, QStringLiteral("����"), QStringLiteral("��ѡ����Ч�ĵ����ļ�!"));
		return;
	}
	//���ƻ�ȡok,׼����ʾ
}
//����:�������
void EvisionController::openCameraCommand()
{
	Camera * _camera = new Camera();
	_camera->show();
}
//����:����˫Ŀ���
void EvisionController::openStereoCameraCommand()
{
	StereoCamera * _stereoCamera = new StereoCamera();
	_stereoCamera->show();
}

//��Ϣ��Ӧ:�����Ի���
void EvisionController::onOpenMessageBox(QString title, QString msg)
{
	QMessageBox::information(NULL, title, msg);
}

