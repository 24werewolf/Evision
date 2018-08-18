#include "Calibration.h"
#include <QFileDialog>

#include "opencv2\core\core.hpp"
#include "cv.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <math.h>
#include <vector>
#include "CommonHelper.h"

/*
 * ������"�궨"���ܵ���ͼ��,ҵ���߼���...��
 */

Calibration::Calibration(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//��ʼ��Calibrater
	Calibrater::getInstance()->initialize();
	//�����ź�,ʹ���첽ģʽ
	imgLtoShow = *new cv::Mat();
	imgRtoShow = *new cv::Mat();
	connect(this, SIGNAL(IsTimeToShowImages()), this, SLOT(OnShowImages()));
}

Calibration::~Calibration()
{
}
//��ʾͼƬ
void Calibration::ShowImage(cv::Mat imgL, cv::Mat imgR)
{
	
	//������Matת��ΪQImage
	QImage LQImage = CommonHelper::cvMat2QImage(imgL);
	QImage RQImage = CommonHelper::cvMat2QImage(imgR);
	//��ʾ����QImage
	ui.Viewer_CalibrateL;

	QGraphicsScene *sceneL = new QGraphicsScene;
	sceneL->addPixmap(QPixmap::fromImage(LQImage));
	ui.Viewer_CalibrateL->setScene(sceneL);
	//ui.Viewer_CalibrateL->resize(LQImage.width() + 10, LQImage.height() + 10);
	ui.Viewer_CalibrateL->show();

	QGraphicsScene *sceneR = new QGraphicsScene;
	sceneR->addPixmap(QPixmap::fromImage(RQImage));
	ui.Viewer_CalibrateR->setScene(sceneR);
	//ui.Viewer_CalibrateR->resize(RQImage.width() + 10, RQImage.height() + 10);
	ui.Viewer_CalibrateR->show();

	ui.Viewer_CalibrateR->update();
}
//��Ӧ��ʾͼƬ���ź�
void Calibration::OnShowImages()
{
	ShowImage(imgLtoShow, imgRtoShow);
}

//�궨��Ĭ�ϲ���
void Calibration::OnDefaultBoardParams()
{
	ui.lineEdit_BoardWidth->setText("9");
	ui.lineEdit_BoardHeight->setText("6");
	ui.lineEdit__nBoards->setText("20");
	ui.lineEdit_SquareSize->setText("25");
	ui.lineEdit_Alpha->setText("-1");
	ui.checkBox_FPP->setChecked(true);
	ui.checkBox_UIG->setChecked(true);
	ui.checkBox_FAR->setChecked(true);
	ui.checkBox_SFL->setChecked(true);
	ui.checkBox_FI->setChecked(false);
	ui.checkBox_Bouguet->setChecked(true);
	ui.checkBox_Hartley->setChecked(false);
}
//���"Bouguet"ѡ��
void Calibration::OnChecked_Bouguet()
{
}
//���"Hartley"ѡ��
void Calibration::OnChecked_Hartley()
{
}
//���"Fi"ѡ��
void Calibration::OnChecked_Fi()
{
}
//���"Uig"ѡ��
void Calibration::OnChecked_Uig()
{
}
//���"SFI"ѡ��
void Calibration::OnChecked_Sfl()
{
}
//���"FPPѡ��"
void Calibration::OnChecked_FPP()
{
}
//���"FAR"ѡ��
void Calibration::OnChecked_Far()
{
}
//ѡ��궨ͼƬ
void Calibration::OnChooseImages()
{
	QFileDialog fileDialog(this);
	fileDialog.setWindowTitle(QStringLiteral("��ѡ��������ͷ�����ͼƬ�ļ�����"));
	fileDialog.setNameFilter("ͼƬ�ļ�(*.jpg *.png *.jpeg)");
	fileDialog.setFileMode(QFileDialog::ExistingFiles);

	
	if (fileDialog.exec() == QDialog::Accepted)
	{
		ImageListL = fileDialog.selectedFiles();
		fileDialog.setWindowTitle(QStringLiteral("��ѡ��������ͷ�����ͼƬ�ļ�����"));
		if (fileDialog.exec() == QDialog::Accepted)
		{
			ImageListR = fileDialog.selectedFiles();
			//�����ļ��б������ȷ��
			//��֤����
			if(ImageListL.size()!= ImageListR.size()|| ImageListL.size()==0|| ImageListR.size()==0)
			{
				//��һ��ͼ����ĿΪ0���������ͼ��������һ��,�˳�
				return;
			}
			else
			{
				/*
				 *һ������
				 *���Խ��д�ͼƬ�궨,���ڿ��Խ���ͼƬ�궨�İ�ť���
				 */
				ui.pushButton_CalibStart->setEnabled(true);
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
//��ͼƬ�궨
void Calibration::OnCalibrateFromImage()
{
	//1. �ߴ��һ��
	//2. �������
	//3. ���̱߳궨,�߳��򻺳�������д�봦�����ͼƬ,�����̲ۺ��������������ı仯,���½����ˢ�µ�������
	cv::Mat frame0, frame1, img0, img1;
	//ȡ����ͼ��һ��ͼƬ����������ߴ�
	img0 = cvLoadImage(ImageListL.at(0).toStdString().c_str());
	if (img0.rows>1000)
	{
		cv::resize(img0, img0, cv::Size(img0.cols / 6, img0.rows / 6));
	}
	//�������
	//ʵ�ʵĵ�������,��ֵΪ:�û����õĵ�������/����ͼͼƬ����/����ͼͼƬ����,�����е���Сֵ
	int NumOfAvailableImages = std::min(ui.lineEdit__nBoards->text().toInt(), std::min(ImageListL.size(), ImageListR.size()));
	Calibrater::getInstance()->initCornerData(
		NumOfAvailableImages,
		img0.size(),
		cv::Size(ui.lineEdit_BoardWidth->text().toInt(), ui.lineEdit_BoardHeight->text().toInt()),
		ui.lineEdit_SquareSize->text().toDouble());

	// ��ʼ���ǵ�
	int nSucceedBoard = 0;//����ɹ���ͼƬ������
	for (int i = 0; i<NumOfAvailableImages; i++)
	{
		frame0 = cvLoadImage(ImageListL.at(i).toStdString().c_str());
		img0 = frame0.clone();
		if (img0.rows>1000)
		{
			cv::resize(img0, img0, cv::Size(img0.cols / 6, img0.rows / 6));
		}
		frame1 = cvLoadImage(ImageListR.at(i).toStdString().c_str());
		img1 = frame1.clone();
		if (img1.rows>1000)
		{
			cv::resize(img1, img1, cv::Size(img1.cols / 6, img1.rows / 6));
		}

		//if (img0.rows>1000)//???
		//{
		//	cv::resize(img0, img0, cv::Size(img0.cols / 6, img0.rows / 6));
		//	cv::resize(img1, img1, cv::Size(img1.cols / 6, img1.rows / 6));
		//}
		// ���ǵ�

		if (Calibrater::getInstance()->detectCorners(img0, img1, i))//������ɹ�
		{
			nSucceedBoard++;//�ɹ���ͼƬ������1
			cv::bitwise_not(img0, img0);//ʹͼ��ɫ������ͬʱ�ҵ����������̽ǵ�
			cv::bitwise_not(img1, img1);
		}
		else//������ʧ��
		{
			//PutMessage(CalibWnd, _T("��ͼƬ���ʧ��!\n"));
		}
		//F_ShowImage(img0, m_lfImage, IDC_PicLfCam);//�������ˢ������ͼ 
		//F_ShowImage(img1, m_riImage, IDC_PicRiCam);
		//ShowImage(img0, img1);
		imgLtoShow = img0;
		imgRtoShow = img1;
		emit IsTimeToShowImages();
	}
	if (nSucceedBoard < 4)//�ɹ�������С��4,�޷����ڱ궨
	{
		//PutMessage(CalibWnd, _T("���ɹ�������ͼ����С��4�����궨ʧ��!\n�����½��б궨����.\n"));
		return;
	}
	Calibrater::getInstance()->resizeCornerData(nSucceedBoard);//���������洢���Ĵ�С
	// ����ǵ���������
	QString FileTemp= WorkPath;
	FileTemp.append("\\");
	FileTemp.append("\\DATA\\CornerData.yml");
	Calibrater::getInstance()->saveCornerData(FileTemp.toStdString().c_str());
	//PutMessage(CalibWnd, _T("���̽ǵ������.\n"));
	//����,�ǵ�����ݺ����̵������Ѿ����,�������ڶ�Ӧ����������ת��Ϊ�ļ�
	//�궨�������
	Calibrater::getInstance()->stereoParams.flags = 0;//��־λ����shiver��Calibrater��ֱ�Ӹ�����,Ӧ�����õ������ϴ��ⲿ����
	Calibrater::getInstance()->stereoParams.alpha = ui.lineEdit_Alpha->text().toInt();
	//�궨
	Calibrater::getInstance()->calibrateStereoCamera();
	//����궨���
	double avgErr = 0;
	Calibrater::getInstance()->getStereoCalibrateError(avgErr);
	char info[50];
	sprintf_s(info, "�궨��� = %7.4g", avgErr);

	//PutMessage(CalibWnd, ss);//����궨���
	//���˱궨����

	// ִ��У��
	Calibrater::getInstance()->rectifyStereoCamera((ui.checkBox_Bouguet->isChecked()==true? Calibrater::RECTIFY_BOUGUET: Calibrater::RECTIFY_HARTLEY));
	//�õ���ͶӰ�����У��ӳ�����
	//PutMessage(CalibWnd, _T("�����˫ĿУ��.\n"));
	// ��������ͷ�������
	QString CalibParasFile= WorkPath;
	CalibParasFile.append("\\DATA\\calib_paras.xml");
	Calibrater::getInstance()->saveCalibrationDatas(
		CalibParasFile.toStdString().c_str(), 
		(ui.checkBox_Bouguet->isChecked() == true ? Calibrater::RECTIFY_BOUGUET : Calibrater::RECTIFY_HARTLEY));
	//PutMessage(CalibWnd, _T("�ѱ��涨������ļ�:\n"));
	if (avgErr > 5.0) {
		//AfxMessageBox(_T("�궨������!ǿ�ҽ��������궨��Դ�ĺ����Բ����е���������,���������ִ�в���,���ή�ͽ�������Ŷ�!"));
	}
}
//���������ͷ
void Calibration::OnChanged_LCameraComboBox()
{
}
//���������ͷ
void Calibration::OnChanged_RChangeComboBox()
{
}
//����ֱ���
void Calibration::OnChanged_ResolutionComboBox()
{
}
//ˢ������ͷ
void Calibration::OnRefreshCameras()
{
}
//����/�ر�����ͷ
void Calibration::OnCamerasPowerOn()
{
}
//������ͷ�궨
void Calibration::OnCalibrateFromCameras()
{
}
//ѡ��궨�ļ�
void Calibration::OnChooseCalibrateFile()
{
}
//���ļ��궨
void Calibration::OnCalibrateFromFile()
{
}
//����:��ʾͼƬ
void Calibration::OnShowImg()
{
	QFileDialog fileDialog(this);
	fileDialog.setWindowTitle(QStringLiteral("��ѡ��������ͷ�����ͼƬ�ļ�����"));
	fileDialog.setNameFilter("ͼƬ�ļ�(*.jpg *.png *.jpeg)");
	//fileDialog.setFileMode(QFileDialog::ExistingFiles);


	if (fileDialog.exec() == QDialog::Accepted)
	{
		//QString X = fileDialog.selectedFiles().at(0);
		//std::string  Y = X.toStdString();
		//const char * str = Y.c_str();
		//cv::Mat temp=cvLoadImage(str);

		//QByteArray ba = X.toLatin1();
		//const char *c_str2 = ba.data();

		cv::Mat img = cv::imread(fileDialog.selectedFiles().at(0).toStdString().c_str(), CV_LOAD_IMAGE_UNCHANGED);

		
		if (img.empty()==false)
		{
			cv::namedWindow("MyWindow", CV_WINDOW_AUTOSIZE);
			imshow("MyWindow", img);
			cv::waitKey(0);
			//cvReleaseImage(&temp);
			cv::destroyWindow("MyWindow");
		}
		imgLtoShow = img;
		imgRtoShow = img;
		emit IsTimeToShowImages();
		//ShowImage(img, img);
	}
}
