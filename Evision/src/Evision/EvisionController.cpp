#include "EvisionController.h"
#include <QMessageBox>
#include "QFileDialog"
#include <imgcodecs/imgcodecs_c.h>
#include <imgproc.hpp>

EvisionController::EvisionController()
{
	m_entity = EvisionParamEntity::getInstance();
}


EvisionController::~EvisionController()
{
}
//����:�궨Ĭ�ϲ���
void EvisionController::setDefaultCalibParamCommand()
{
	m_entity->setBoardWidth(9);
	m_entity->setBoardHeight(6);
	m_entity->setSquareSize(25);
	m_entity->setnBoards(20);
	m_entity->setAlpha(-1);
	m_entity->setFPP(true);
	m_entity->setUIG(true);
	m_entity->setFAR(true);
	m_entity->setSFL(true);
	m_entity->setFI(false);
	m_entity->setBouguet(true);
}
//����:�궨
void EvisionController::CalibrateCommand()
{
	//1.��֤����
	if (m_entity->getBoardWidth()*m_entity->getBoardHeight()*m_entity->getnBoards()*m_entity->getSquareSize()<=0)
	{
		//δͨ��������������֤
		QMessageBox::information(NULL, QStringLiteral("����"), QStringLiteral("��������!����!"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		return;
	}
	//2.ѡ���ļ�
	QFileDialog * fileDialog=new QFileDialog();
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

	//3.���
}

//����:ƥ��Ĭ�ϲ���
void EvisionController::setDefaultMatchParamCommand()
{
	if (m_entity->getBM())
	{
		m_entity->setMinDisp(0);
		m_entity->setUniradio(25);
		m_entity->setSpecwinsz(100);
		m_entity->setMaxDisp(144);
		m_entity->setSpecrange(32);
		m_entity->setPrefilcap(31);
		m_entity->setSadWinsz(51);
		m_entity->setTextThread(10);
		m_entity->setMaxdifdisp12(1);
	}
	else if (m_entity->getSGBM())
	{
		m_entity->setMinDisp(0);
		m_entity->setUniradio(20);
		m_entity->setSpecwinsz(100);
		m_entity->setMaxDisp(144);
		m_entity->setSpecrange(32);
		m_entity->setPrefilcap(63);
		m_entity->setSadWinsz(25);
		//m_entity->setTextThread(10);
		m_entity->setMaxdifdisp12(1);
	}
	else if (m_entity->getVAR())
	{
		m_entity->setMinDisp(-64);
		m_entity->setMaxDisp(64);
		m_entity->setLevels(1);
		m_entity->setPyrScale(0.1);
		m_entity->setPolyN(5);
		m_entity->setPolySigma(52.6);
		m_entity->setFi(90);
		m_entity->setLambda(0.82);
	}
	else
	{
		QMessageBox::information(NULL, QStringLiteral("����"), QStringLiteral("û��ѡ��ƥ���㷨"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	}
}

//��ͼƬ�궨
void EvisionController::CalibrateFromImage()
{
	//1. �ߴ��һ��
	//2. �������
	//3. ���̱߳궨,�߳��򻺳�������д�봦�����ͼƬ,�����̲ۺ��������������ı仯,���½����ˢ�µ�������
	//cv::Mat frame0, frame1, img0, img1;
	////ȡ����ͼ��һ��ͼƬ����������ߴ�
	//img0 = cvLoadImage(ImageListL.at(0).toStdString().c_str());
	//if (img0.rows > 1000)
	//{
	//	cv::resize(img0, img0, cv::Size(img0.cols / 6, img0.rows / 6));
	//}
	////�������
	////ʵ�ʵĵ�������,��ֵΪ:�û����õĵ�������/����ͼͼƬ����/����ͼͼƬ����,�����е���Сֵ
	//int NumOfAvailableImages = std::min(ui.lineEdit__nBoards->text().toInt(), std::min(ImageListL.size(), ImageListR.size()));
	//Calibrater::getInstance()->initCornerData(
	//	NumOfAvailableImages,
	//	img0.size(),
	//	cv::Size(ui.lineEdit_BoardWidth->text().toInt(), ui.lineEdit_BoardHeight->text().toInt()),
	//	ui.lineEdit_SquareSize->text().toDouble());

	//// ��ʼ���ǵ�
	//int nSucceedBoard = 0;//����ɹ���ͼƬ������
	//for (int i = 0; i < NumOfAvailableImages; i++)
	//{
	//	frame0 = cvLoadImage(ImageListL.at(i).toStdString().c_str());
	//	img0 = frame0.clone();
	//	if (img0.rows > 1000)
	//	{
	//		cv::resize(img0, img0, cv::Size(img0.cols / 6, img0.rows / 6));
	//	}
	//	frame1 = cvLoadImage(ImageListR.at(i).toStdString().c_str());
	//	img1 = frame1.clone();
	//	if (img1.rows > 1000)
	//	{
	//		cv::resize(img1, img1, cv::Size(img1.cols / 6, img1.rows / 6));
	//	}

	//	//if (img0.rows>1000)//???
	//	//{
	//	//	cv::resize(img0, img0, cv::Size(img0.cols / 6, img0.rows / 6));
	//	//	cv::resize(img1, img1, cv::Size(img1.cols / 6, img1.rows / 6));
	//	//}
	//	// ���ǵ�

	//	if (Calibrater::getInstance()->detectCorners(img0, img1, i))//������ɹ�
	//	{
	//		nSucceedBoard++;//�ɹ���ͼƬ������1
	//		cv::bitwise_not(img0, img0);//ʹͼ��ɫ������ͬʱ�ҵ����������̽ǵ�
	//		cv::bitwise_not(img1, img1);
	//	}
	//	else//������ʧ��
	//	{
	//		//PutMessage(CalibWnd, _T("��ͼƬ���ʧ��!\n"));
	//	}
	//	//F_ShowImage(img0, m_lfImage, IDC_PicLfCam);//�������ˢ������ͼ 
	//	//F_ShowImage(img1, m_riImage, IDC_PicRiCam);
	//	//ShowImage(img0, img1);
	//	imgLtoShow = img0;
	//	imgRtoShow = img1;
	//	emit IsTimeToShowImages();
	//}
	//if (nSucceedBoard < 4)//�ɹ�������С��4,�޷����ڱ궨
	//{
	//	//PutMessage(CalibWnd, _T("���ɹ�������ͼ����С��4�����궨ʧ��!\n�����½��б궨����.\n"));
	//	return;
	//}
	//Calibrater::getInstance()->resizeCornerData(nSucceedBoard);//���������洢���Ĵ�С
	//// ����ǵ���������
	//QString FileTemp = WorkPath;
	//FileTemp.append("\\");
	//FileTemp.append("\\DATA\\CornerData.yml");
	//Calibrater::getInstance()->saveCornerData(FileTemp.toStdString().c_str());
	////PutMessage(CalibWnd, _T("���̽ǵ������.\n"));
	////����,�ǵ�����ݺ����̵������Ѿ����,�������ڶ�Ӧ����������ת��Ϊ�ļ�
	////�궨�������
	//Calibrater::getInstance()->stereoParams.flags = 0;//��־λ����shiver��Calibrater��ֱ�Ӹ�����,Ӧ�����õ������ϴ��ⲿ����
	//Calibrater::getInstance()->stereoParams.alpha = ui.lineEdit_Alpha->text().toInt();
	////�궨
	//Calibrater::getInstance()->calibrateStereoCamera();
	////����궨���
	//double avgErr = 0;
	//Calibrater::getInstance()->getStereoCalibrateError(avgErr);
	//char info[50];
	//sprintf_s(info, "�궨��� = %7.4g", avgErr);

	////PutMessage(CalibWnd, ss);//����궨���
	////���˱궨����

	//// ִ��У��
	//Calibrater::getInstance()->rectifyStereoCamera((ui.checkBox_Bouguet->isChecked() == true ? Calibrater::RECTIFY_BOUGUET : Calibrater::RECTIFY_HARTLEY));
	////�õ���ͶӰ�����У��ӳ�����
	////PutMessage(CalibWnd, _T("�����˫ĿУ��.\n"));
	//// ��������ͷ�������
	//QString CalibParasFile = WorkPath;
	//CalibParasFile.append("\\DATA\\calib_paras.xml");
	//Calibrater::getInstance()->saveCalibrationDatas(
	//	CalibParasFile.toStdString().c_str(),
	//	(ui.checkBox_Bouguet->isChecked() == true ? Calibrater::RECTIFY_BOUGUET : Calibrater::RECTIFY_HARTLEY));
	////PutMessage(CalibWnd, _T("�ѱ��涨������ļ�:\n"));
	//if (avgErr > 5.0) {
	//	//AfxMessageBox(_T("�궨������!ǿ�ҽ��������궨��Դ�ĺ����Բ����е���������,���������ִ�в���,���ή�ͽ�������Ŷ�!"));
	//}
}
