#include "StereoCalibrate.h"
#include <QMessageBox>
#include "QFileDialog"
#include <imgcodecs/imgcodecs_c.h>
#include <imgproc.hpp>
#include <highgui.hpp>
#include <iostream>
#include <calib3d/calib3d.hpp>
#include "EvisionUtils.h"
#include <QListWidget>
#include <QListWidgetItem>
#include <QPixmap>


StereoCalibrate::StereoCalibrate(std::vector<std::string>* imagelistL, std::vector<std::string>* imagelistR, QObject * parent)
{
	m_entity = CalibrateParamEntity::getInstance();
	this->imagelistL = imagelistL;
	this->imagelistR = imagelistR;
	this->boardSize = boardSize;
	this->squareSize = squareSize;
	this->useCalibrated = useCalibrated;
	this->showRectified = showRectified;

	QFileInfo *_fileInfo = new QFileInfo(QString::fromStdString(imagelistL->at(0)));
	this->cameraParamsFilename = _fileInfo->absolutePath().toStdString().append("/cameraParams.yml");
}

StereoCalibrate::~StereoCalibrate()
{

}

void StereoCalibrate::run()
{
	if (imagelistL->size()!= imagelistR->size())//ͼƬ���ɶ�
	{
		emit openMessageBox(QStringLiteral("����"), QStringLiteral("ͼƬ���ɶ�!"));
		return;
	}
	//UseCalib();
	return;
	const int maxScale = 2;
	// ARRAY AND VECTOR STORAGE:

	std::vector<std::vector<cv::Point2f> > imagePoints[2];
	std::vector<std::vector<cv::Point3f> > objectPoints;
	cv::Size imageSize;

	int i, j, k, nimages = (int)imagelistL->size();

	imagePoints[0].resize(nimages);
	imagePoints[1].resize(nimages);
	std::vector<std::string> goodImageList;
	//Ѱ�ҽ���,���ܹ��ҵ��������ЩͼƬ���˳��������궨
	for (i = j = 0; i < nimages; i++)
	{

		//const std::string& filename = imagelist->at(i * 2 + k);
		const std::string& filenameL = imagelistL->at(i);
		const std::string& filenameR = imagelistR->at(i);


		//cv::Mat img = cv::imread(filename, 0);
		cv::Mat imgL = cv::imread(filenameL, 0);
		cv::Mat imgR = cv::imread(filenameR, 0);

		if (imgL.empty() || imgR.empty())
			break;
		if (imageSize == cv::Size())
			imageSize = imgL.size();
		else if (imgL.size() != imageSize|| imgL.size()!=imgR.size())
		{
			//m_entity->setmsgBuffer("ͼƬ�ߴ�������,����");
			std::cout << "ͼƬ�ߴ�������,����" << std::endl;
			break;
		}
		//bool found = false;
		bool foundL = false;
		bool foundR = false;

		std::vector<cv::Point2f>& cornersL = imagePoints[0][j];
		std::vector<cv::Point2f>& cornersR = imagePoints[1][j];

		for (int scale = 1; scale <= maxScale; scale++)
		{
			cv::Mat timgL;
			if (scale == 1)
				timgL = imgL;
			else
				resize(imgL, timgL, cv::Size(), scale, scale, cv::INTER_LINEAR_EXACT);
			foundL = findChessboardCorners(timgL, boardSize, cornersL,
				cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_NORMALIZE_IMAGE);

			cv::Mat timgR;
			if (scale == 1)
				timgR = imgR;
			else
				resize(imgR, timgR, cv::Size(), scale, scale, cv::INTER_LINEAR_EXACT);
			foundR = findChessboardCorners(timgR, boardSize, cornersR,
				cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_NORMALIZE_IMAGE);

			if (foundL&&foundR)
			{
				if (scale > 1)
				{
					cv::Mat cornersMat(cornersL);
					cornersMat *= 1. / scale;
				}
				break;
			}
		}
		//��ʾ����
		//std::cout << filename << std::endl;
		cv::Mat cimgL, cimg1L, cimgR, cimg1R;
		cvtColor(imgL, cimgL, cv::COLOR_GRAY2BGR);
		drawChessboardCorners(cimgL, boardSize, cornersL, foundL);
		double sfL = 640. / MAX(imgL.rows, imgL.cols);
		resize(cimgL, cimg1L, cv::Size(), sfL, sfL, cv::INTER_LINEAR_EXACT);

		cvtColor(imgR, cimgR, cv::COLOR_GRAY2BGR);
		drawChessboardCorners(cimgR, boardSize, cornersR, foundR);
		double sfR = 640. / MAX(imgR.rows, imgR.cols);
		resize(cimgR, cimg1R, cv::Size(), sfR, sfR, cv::INTER_LINEAR_EXACT);
		m_entity->setImageLtoShow(cimg1L);
		m_entity->setImageRtoShow(cimg1R);

		cv::MatSize ss = cimg1L.size;

		if (!foundL || !foundR)
			break;
		cornerSubPix(imgL, cornersL, cv::Size(11, 11), cv::Size(-1, -1),
			cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS,
				30, 0.01));
		cornerSubPix(imgR, cornersR, cv::Size(11, 11), cv::Size(-1, -1),
			cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS,
				30, 0.01));


		goodImageList.push_back(imagelistL->at(i));
		goodImageList.push_back(imagelistR->at(i));
		j++;
		std::string temp = std::to_string(j);
		temp += "/"; temp += std::to_string(nimages);
		//m_entity->setmsgBuffer(QString::fromStdString(temp));
		std::cout << temp << std::endl;
	}//���������

	//std::cout << j << " pairs have been successfully detected.\n";
	//m_entity->setmsgBuffer(QStringLiteral("���������,���ڱ궨����..."));
	std::cout << "���������,���ڱ궨����..." << std::endl;
	nimages = j;//ֻ���ҵ������ͼƬ�������궨,ȷ������
	if (nimages < 2)
	{
		emit openMessageBox(QStringLiteral("����"), QStringLiteral("����ͼƬ̫��,��ѡ���㹻�ı궨ͼƬ!"));
		return;
	}

	imagePoints[0].resize(nimages);
	imagePoints[1].resize(nimages);
	objectPoints.resize(nimages);

	for (i = 0; i < nimages; i++)
	{
		for (j = 0; j < boardSize.height; j++)
			for (k = 0; k < boardSize.width; k++)
				objectPoints[i].push_back(cv::Point3f(k*squareSize, j*squareSize, 0));
	}

	std::cout << "Running stereo calibration ...\n";

	cv::Mat cameraMatrix[2], distCoeffs[2];
	cameraMatrix[0] = initCameraMatrix2D(objectPoints, imagePoints[0], imageSize, 0);
	cameraMatrix[1] = initCameraMatrix2D(objectPoints, imagePoints[1], imageSize, 0);
	cv::Mat R, T, E, F;
	//�궨
	double rms = stereoCalibrate(objectPoints, imagePoints[0], imagePoints[1],
		cameraMatrix[0], distCoeffs[0],
		cameraMatrix[1], distCoeffs[1],
		imageSize, R, T, E, F,
		cv::CALIB_FIX_ASPECT_RATIO +
		cv::CALIB_ZERO_TANGENT_DIST +
		cv::CALIB_USE_INTRINSIC_GUESS +
		cv::CALIB_SAME_FOCAL_LENGTH +
		cv::CALIB_RATIONAL_MODEL +
		cv::CALIB_FIX_K3 + cv::CALIB_FIX_K4 + cv::CALIB_FIX_K5 + cv::CALIB_FIX_K6+ cv::CALIB_FIX_S1_S2_S3_S4+cv::CALIB_FIX_TAUX_TAUY,
		cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS, 100, 1e-5));
;
	std::cout << "RMS error = " << rms << std::endl;

	// CALIBRATION QUALITY CHECK
	// because the output fundamental matrix implicitly
	// includes all the output information,
	// we can check the quality of calibration using the
	// epipolar geometry constraint: m2^t*F*m1=0
	/*�ü���Լ�����궨����*/
	double err = 0;
	int npoints = 0;
	std::vector<cv::Vec3f> lines[2];
	for (i = 0; i < nimages; i++)
	{
		int npt = (int)imagePoints[0][i].size();
		cv::Mat imgpt[2];
		for (k = 0; k < 2; k++)
		{
			imgpt[k] = cv::Mat(imagePoints[k][i]);
			undistortPoints(imgpt[k], imgpt[k], cameraMatrix[k], distCoeffs[k], cv::Mat(), cameraMatrix[k]);
			computeCorrespondEpilines(imgpt[k], k + 1, F, lines[k]);
		}
		for (j = 0; j < npt; j++)
		{
			double errij = fabs(imagePoints[0][i][j].x*lines[1][j][0] +
				imagePoints[0][i][j].y*lines[1][j][1] + lines[1][j][2]) +
				fabs(imagePoints[1][i][j].x*lines[0][j][0] +
					imagePoints[1][i][j].y*lines[0][j][1] + lines[0][j][2]);
			err += errij;
		}
		npoints += npt;
	}

	std::cout << "ƽ���������" << "(average epipolar err) =" << std::to_string(err / npoints) <<std::endl;
	//ӳ�����
	/*�������cameraMatrix
	 * fx   0   u0
	 * 0    fy  v0
	 * 0    0   1
	 * ƽ�ƾ���T
	 * [x',y',z']
	 * ��ת����R
	 * 
	 */
	cv::Mat R1, P1, R2, P2, Q;//stereoRectify�����
	cv::Rect roi1, roi2;	  //stereoRectify�����
	stereoRectify(cameraMatrix[0], distCoeffs[0],cameraMatrix[1], distCoeffs[1], imageSize, R, T, 
					R1, R2, P1, P2, Q, cv::CALIB_ZERO_DISPARITY, -1, imageSize, &roi1, &roi2);
	std::cout << "ӳ��(R1,P1,R2,P2,Q)�������" << std::endl;
	//�����������

	cv::Mat map1x, map1y, map2x, map2y;//��������
	initUndistortRectifyMap(cameraMatrix[0], distCoeffs[0], R1, P1, imageSize, CV_16SC2, map1x, map1y);
	initUndistortRectifyMap(cameraMatrix[1], distCoeffs[1], R2, P2, imageSize, CV_16SC2, map2x, map2y);
	std::cout << "��������(map1x, map1y, map2x, map2y)�������" << std::endl;
	//�������е����������������������������

	// �������
	bool flag = EvisionUtils::write_AllCameraParams(cameraParamsFilename, cameraMatrix[0], distCoeffs[0],
												cameraMatrix[1], distCoeffs[1], R, T, E, F,
												imageSize,R1,P1,R2,P2,Q,roi1,roi2);
	std::cout << "�����Ѿ����浽:" << cameraParamsFilename << std::endl;
	if (!flag)
	{
		emit openMessageBox(QStringLiteral("�ļ����ʴ���"), QStringLiteral("�޷�д��:cameraParams.yml"));

	}
}
/*
 * ��������ͼ
 */
void StereoCalibrate::insertMat(cv::Mat img)
{
	QListWidgetItem * item = new QListWidgetItem;
	item->setIcon(QIcon(QPixmap::fromImage(EvisionUtils::cvMat2QImage(img))));
	item->setText(QString::fromStdString(std::to_string(index)));
	itemMap.insert(std::pair<QString, cv::Mat>(item->text(), img));

	ui.listWidget->addItem(item);
}
