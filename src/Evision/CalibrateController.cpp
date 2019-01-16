#include "CalibrateController.h"
#include "StereoCalibrate.h"
#include <QMessageBox>
#include <QFileDialog>
#include <opencv.hpp>

CalibrateController::CalibrateController(QObject *parent)
	: QObject(parent)
{
	m_calib_entity = CalibrateParamEntity::getInstance();
}

CalibrateController::~CalibrateController()
{
}
//����:Ĭ�ϱ궨����
void CalibrateController::setDefaultCalibParamCommand()
{
	m_calib_entity->setBoardWidth(9);
	m_calib_entity->setBoardHeight(6);
	m_calib_entity->setSquareSize(25);
	m_calib_entity->setshowRectified(false);
	m_calib_entity->setBouguet(true);
}
//����:�궨
void CalibrateController::CalibrateCommand()
{
	//1.��֤����
	if (m_calib_entity->getBoardWidth()*m_calib_entity->getBoardHeight()*m_calib_entity->getSquareSize() <= 0)
	{
		//δͨ��������������֤
		QMessageBox::information(NULL, QStringLiteral("����"), QStringLiteral("��������!����!"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		return;
	}
	//2.ѡ���ļ�
	QFileDialog * fileDialog = new QFileDialog();
	fileDialog->setWindowTitle(QStringLiteral("��ѡ��������ͷ�����ͼƬ�ļ�����"));
	fileDialog->setNameFilter("ͼƬ�ļ�(*.jpg *.png *.jpeg)");
	fileDialog->setFileMode(QFileDialog::ExistingFiles);
	if (fileDialog->exec() == QDialog::Accepted)
	{
		ImageListL = fileDialog->selectedFiles();
		fileDialog->setWindowTitle(QStringLiteral("��ѡ��������ͷ�����ͼƬ�ļ�����"));
		if (fileDialog->exec() == QDialog::Accepted)
		{
			ImageListR = fileDialog->selectedFiles();
			//�����ļ��б������ȷ��
			//��֤����
			if (ImageListL.size() != ImageListR.size() || ImageListL.size() == 0 || ImageListR.size() == 0)
			{
				//��һ��ͼ����ĿΪ0���������ͼ��������һ��,�˳�
				QMessageBox::information(NULL, QStringLiteral("����"), QStringLiteral("������ͼ��������Ȼ�Ϊ��"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
				return;
			}
			else
			{
				/*
				 *3.һ������,���Խ��д�ͼƬ�궨
				 */
				std::vector<std::string>* imagelist = new std::vector<std::string>();
				std::vector<std::string>* imagelistL = new std::vector<std::string>();
				std::vector<std::string>* imagelistR = new std::vector<std::string>();
				for (int i = 0; i < std::min(ImageListL.size(), ImageListR.size()); ++i)
				{
					imagelist->push_back(ImageListL.at(i).toStdString());
					imagelist->push_back(ImageListR.at(i).toStdString());
					imagelistL->push_back(ImageListL.at(i).toStdString());
					imagelistR->push_back(ImageListR.at(i).toStdString());

				}
				cv::Size * _size = new cv::Size();
				_size->width = m_calib_entity->getBoardWidth();
				_size->height = m_calib_entity->getBoardHeight();
				StereoCalibrate * _stereoCalib = new StereoCalibrate(imagelistL, imagelistR, *_size, m_calib_entity->getSquareSize(), m_calib_entity->getBouguet(), m_calib_entity->getshowRectified());
				connect(_stereoCalib, SIGNAL(openMessageBox(QString, QString)), this, SLOT(onOpenMessageBox(QString, QString)));
				_stereoCalib->start();
			}
		}
		else
		{
			//ѡ����ͼ��ʱ���˳�
			return;
		}
	}
	else
	{
		//ѡ����ͼ��ʱ���˳�
		return;
	}
}
//��Ϣ��Ӧ:�����Ի���
void CalibrateController::onOpenMessageBox(QString title, QString msg)
{
	QMessageBox::information(NULL, title, msg);
}
