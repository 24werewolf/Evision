#include "StereoCalibrate.h"
#include <QMessageBox>
#include "QFileDialog"
#include <imgcodecs/imgcodecs_c.h>
#include <imgproc.hpp>
#include <highgui.hpp>
#include <iostream>
#include <calib3d/calib3d.hpp>
#include "EvisionUtils.h"
#include <boost/mpl/back_inserter.hpp>


StereoCalibrate::StereoCalibrate(std::vector<std::string>* imagelistL, std::vector<std::string>* imagelistR, cv::Size boardSize, float squareSize, bool useCalibrated, bool showRectified, QObject * parent)
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

void StereoCalibrate::run_old()
{
	if (imagelist->size() % 2 != 0)//ͼƬ���ɶ�
	{
		QMessageBox::information(NULL, QStringLiteral("����"), QStringLiteral("ͼƬ���ɶ�!"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		return;
	}

	const int maxScale = 2;
	// ARRAY AND VECTOR STORAGE:

	std::vector<std::vector<cv::Point2f> > imagePoints[2];
	std::vector<std::vector<cv::Point3f> > objectPoints;
	cv::Size imageSize;

	int i, j, k, nimages = (int)imagelist->size() / 2;

	imagePoints[0].resize(nimages);
	imagePoints[1].resize(nimages);
	std::vector<std::string> goodImageList;
	//Ѱ�ҽ���,���ܹ��ҵ��������ЩͼƬ���˳��������궨
	for (i = j = 0; i < nimages; i++)
	{
		for (k = 0; k < 2; k++)
		{
			const std::string& filename = imagelist->at(i * 2 + k);
			cv::Mat img = cv::imread(filename, 0);
			if (img.empty())
				break;
			if (imageSize == cv::Size())
				imageSize = img.size();
			else if (img.size() != imageSize)
			{
				//m_entity->setmsgBuffer(QString::fromStdString(filename) + "���һ��ͼƬ�ߴ粻ͬ,����.");
				break;
			}
			bool found = false;
			std::vector<cv::Point2f>& corners = imagePoints[k][j];
			for (int scale = 1; scale <= maxScale; scale++)
			{
				cv::Mat timg;
				if (scale == 1)
					timg = img;
				else
					resize(img, timg, cv::Size(), scale, scale, cv::INTER_LINEAR_EXACT);
				found = findChessboardCorners(timg, boardSize, corners,
					cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_NORMALIZE_IMAGE);

				if (found)
				{
					if (scale > 1)
					{
						cv::Mat cornersMat(corners);
						cornersMat *= 1. / scale;
					}
					break;
				}
			}
			//��ʾ����
			std::cout << filename << std::endl;
			cv::Mat cimg, cimg1;
			cvtColor(img, cimg, cv::COLOR_GRAY2BGR);
			drawChessboardCorners(cimg, boardSize, corners, found);
			double sf = 640. / MAX(img.rows, img.cols);
			resize(cimg, cimg1, cv::Size(), sf, sf, cv::INTER_LINEAR_EXACT);
			if (k==0)
			{
				m_entity->setImageLtoShow(cimg1);
			}
			else
			{
				m_entity->setImageRtoShow(cimg1);

			}

			if (!found)
				break;
			cornerSubPix(img, corners, cv::Size(11, 11), cv::Size(-1, -1),
				cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS,
					30, 0.01));
		}
		if (k == 2)
		{
			goodImageList.push_back(imagelist->at(i * 2));
			goodImageList.push_back(imagelist->at(i * 2 + 1));
			j++;
		}
	}//���������

	nimages = j;//ֻ���ҵ������ͼƬ�������궨,ȷ������
	if (nimages < 2)
	{
		//std::cout << "Error: too little pairs to run the calibration\n";
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
		cv::CALIB_FIX_K3 + cv::CALIB_FIX_K4 + cv::CALIB_FIX_K5,
		cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS, 100, 1e-5));
	std::string tmp="RMS error = \n";
	tmp += std::to_string(rms);
	emit openMessageBox(QStringLiteral("�궨���"), QString::fromStdString(tmp));
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
	tmp = "average epipolar err = \n";
	tmp += std::to_string(err / npoints);
	emit openMessageBox(QStringLiteral("ƽ���������"), QString::fromStdString(tmp));

	// �����ڲ�����
	cv::FileStorage fs("intrinsics.yml", cv::FileStorage::WRITE);
	if (fs.isOpened())
	{
		fs << "M1" << cameraMatrix[0] << "D1" << distCoeffs[0] <<
			"M2" << cameraMatrix[1] << "D2" << distCoeffs[1];
		fs.release();
	}
	else
		emit openMessageBox(QStringLiteral("�ļ����ʴ���"), QStringLiteral("�޷�д��:intrinsics.yml"));
	cv::Mat R1, R2, P1, P2, Q;
	cv::Rect validRoi[2];

	stereoRectify(cameraMatrix[0], distCoeffs[0],
		cameraMatrix[1], distCoeffs[1],
		imageSize, R, T, R1, R2, P1, P2, Q,
		cv::CALIB_ZERO_DISPARITY, 1, imageSize, &validRoi[0], &validRoi[1]);
	// �����ⲿ����
	fs.open("extrinsics.yml", cv::FileStorage::WRITE);
	if (fs.isOpened())
	{
		fs << "R" << R << "T" << T << "R1" << R1 << "R2" << R2 << "P1" << P1 << "P2" << P2 << "Q" << Q;
		fs.release();
	}
	else
		emit openMessageBox(QStringLiteral("�ļ����ʴ���"), QStringLiteral("�޷�д��:extrinsics.yml"));
	// OpenCV can handle left-right
	// or up-down camera arrangements
	bool isVerticalStereo = fabs(P2.at<double>(1, 3)) > fabs(P2.at<double>(0, 3));

	// COMPUTE AND DISPLAY RECTIFICATION
	if (!showRectified)
		return;

	cv::Mat rmap[2][2];
	// IF BY CALIBRATED (BOUGUET'S METHOD)
	if (useCalibrated)
	{
		// we already computed everything
	}
	// OR ELSE HARTLEY'S METHOD
	else
		// use intrinsic parameters of each camera, but
		// compute the rectification transformation directly
		// from the fundamental matrix
	{
		std::vector<cv::Point2f> allimgpt[2];
		for (k = 0; k < 2; k++)
		{
			for (i = 0; i < nimages; i++)
				std::copy(imagePoints[k][i].begin(), imagePoints[k][i].end(), back_inserter(allimgpt[k]));
		}
		F = cv::findFundamentalMat(cv::Mat(allimgpt[0]), cv::Mat(allimgpt[1]), cv::FM_8POINT, 0, 0);
		cv::Mat H1, H2;
		stereoRectifyUncalibrated(cv::Mat(allimgpt[0]), cv::Mat(allimgpt[1]), F, imageSize, H1, H2, 3);

		R1 = cameraMatrix[0].inv()*H1*cameraMatrix[0];
		R2 = cameraMatrix[1].inv()*H2*cameraMatrix[1];
		P1 = cameraMatrix[0];
		P2 = cameraMatrix[1];
	}

	//Precompute maps for cv::remap()
	initUndistortRectifyMap(cameraMatrix[0], distCoeffs[0], R1, P1, imageSize, CV_16SC2, rmap[0][0], rmap[0][1]);
	initUndistortRectifyMap(cameraMatrix[1], distCoeffs[1], R2, P2, imageSize, CV_16SC2, rmap[1][0], rmap[1][1]);

	cv::Mat canvas;
	double sf;
	int w, h;
	if (!isVerticalStereo)
	{
		sf = 600. / MAX(imageSize.width, imageSize.height);
		w = cvRound(imageSize.width*sf);
		h = cvRound(imageSize.height*sf);
		canvas.create(h, w * 2, CV_8UC3);
	}
	else
	{
		sf = 300. / MAX(imageSize.width, imageSize.height);
		w = cvRound(imageSize.width*sf);
		h = cvRound(imageSize.height*sf);
		canvas.create(h * 2, w, CV_8UC3);
	}

	for (i = 0; i < nimages; i++)
	{
		for (k = 0; k < 2; k++)
		{
			cv::Mat img = cv::imread(goodImageList[i * 2 + k], 0), rimg, cimg;
			remap(img, rimg, rmap[k][0], rmap[k][1], cv::INTER_LINEAR);
			cvtColor(rimg, cimg, cv::COLOR_GRAY2BGR);
			cv::Mat canvasPart = !isVerticalStereo ? canvas(cv::Rect(w*k, 0, w, h)) : canvas(cv::Rect(0, h*k, w, h));
			resize(cimg, canvasPart, canvasPart.size(), 0, 0, cv::INTER_AREA);
			if (useCalibrated)
			{
				cv::Rect vroi(cvRound(validRoi[k].x*sf), cvRound(validRoi[k].y*sf),
					cvRound(validRoi[k].width*sf), cvRound(validRoi[k].height*sf));
				rectangle(canvasPart, vroi, cv::Scalar(0, 0, 255), 3, 8);
			}
		}

		if (!isVerticalStereo)
			for (j = 0; j < canvas.rows; j += 16)
				line(canvas, cv::Point(0, j), cv::Point(canvas.cols, j), cv::Scalar(0, 255, 0), 1, 8);
		else
			for (j = 0; j < canvas.cols; j += 16)
				line(canvas, cv::Point(j, 0), cv::Point(j, canvas.rows), cv::Scalar(0, 255, 0), 1, 8);
		imshow("rectified", canvas);
		char c = (char)cv::waitKey();
		if (c == 27 || c == 'q' || c == 'Q')
			break;
	}
}

void StereoCalibrate::run()
{
	if (imagelistL->size()!= imagelistR->size())//ͼƬ���ɶ�
	{
		emit openMessageBox(QStringLiteral("����"), QStringLiteral("ͼƬ���ɶ�!"));
		return;
	}
	UseCalib();
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
 * ��������ı궨����
 */
void StereoCalibrate::StereoCalib(const std::vector<std::string>& imagelist, 
	cv::Size boardSize, 
	float squareSize, 
	bool displayCorners , 
	bool useCalibrated , 
	bool showRectified )
{
	if (imagelist.size() % 2 != 0)
	{
		std::cout << "Error: the image list contains odd (non-even) number of elements\n";
		return;
	}

	const int maxScale = 2;
	// ARRAY AND VECTOR STORAGE:

	std::vector<std::vector<cv::Point2f> > imagePoints[2];
	std::vector<std::vector<cv::Point3f> > objectPoints;
	cv::Size imageSize;

	int i, j, k, nimages = (int)imagelist.size() / 2;

	imagePoints[0].resize(nimages);
	imagePoints[1].resize(nimages);
	std::vector<std::string> goodImageList;

	for (i = j = 0; i < nimages; i++)
	{
		for (k = 0; k < 2; k++)
		{
			const std::string& filename = imagelist[i * 2 + k];
			cv::Mat img = cv::imread(filename, 0);
			if (img.empty())
				break;
			if (imageSize == cv::Size())
				imageSize = img.size();
			else if (img.size() != imageSize)
			{
				std::cout << "The image " << filename << " has the size different from the first image size. Skipping the pair\n";
				break;
			}
			bool found = false;
			std::vector<cv::Point2f>& corners = imagePoints[k][j];
			for (int scale = 1; scale <= maxScale; scale++)
			{
				cv::Mat timg;
				if (scale == 1)
					timg = img;
				else
					resize(img, timg, cv::Size(), scale, scale, cv::INTER_LINEAR_EXACT);
				found = findChessboardCorners(timg, boardSize, corners,
				                              cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_NORMALIZE_IMAGE);
				if (found)
				{
					if (scale > 1)
					{
						cv::Mat cornersMat(corners);
						cornersMat *= 1. / scale;
					}
					break;
				}
			}
			if (displayCorners)
			{
				std::cout << filename << std::endl;
				cv::Mat cimg, cimg1;
				cvtColor(img, cimg, cv::COLOR_GRAY2BGR);
				drawChessboardCorners(cimg, boardSize, corners, found);
				double sf = 640. / MAX(img.rows, img.cols);
				resize(cimg, cimg1, cv::Size(), sf, sf, cv::INTER_LINEAR_EXACT);
				imshow("corners", cimg1);
				char c = (char)cv::waitKey(500);
				if (c == 27 || c == 'q' || c == 'Q') //Allow ESC to quit
					exit(-1);
			}
			else
				putchar('.');
			if (!found)
				break;
			cornerSubPix(img, corners, cv::Size(11, 11), cv::Size(-1, -1),
			             cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS,
					30, 0.01));
		}
		if (k == 2)
		{
			goodImageList.push_back(imagelist[i * 2]);
			goodImageList.push_back(imagelist[i * 2 + 1]);
			j++;
		}
	}
	std::cout << j << " pairs have been successfully detected.\n";
	nimages = j;
	if (nimages < 2)
	{
		std::cout << "Error: too little pairs to run the calibration\n";
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
	//�Ƚ��е�Ŀ�궨,�ڽ���˫Ŀ�궨





	cv::Mat R, T, E, F;

	double rms = stereoCalibrate(objectPoints, imagePoints[0], imagePoints[1],
		cameraMatrix[0], distCoeffs[0],
		cameraMatrix[1], distCoeffs[1],
		imageSize, R, T, E, F,
	                             cv::CALIB_FIX_ASPECT_RATIO +
	                             cv::CALIB_ZERO_TANGENT_DIST +
	                             cv::CALIB_USE_INTRINSIC_GUESS +
	                             cv::CALIB_SAME_FOCAL_LENGTH +
	                             cv::CALIB_RATIONAL_MODEL +
	                             cv::CALIB_FIX_K3 + cv::CALIB_FIX_K4 + cv::CALIB_FIX_K5,
	                             cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS, 100, 1e-5));
	std::cout << "done with RMS error=" << rms << std::endl;

	// CALIBRATION QUALITY CHECK
	// because the output fundamental matrix implicitly
	// includes all the output information,
	// we can check the quality of calibration using the
	// epipolar geometry constraint: m2^t*F*m1=0
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
	std::cout << "average epipolar err = " << err / npoints << std::endl;

	// save intrinsic parameters
	cv::FileStorage fs("F:\\intrinsics.yml", cv::FileStorage::WRITE);
	if (fs.isOpened())
	{
		fs << "M1" << cameraMatrix[0] << "D1" << distCoeffs[0] <<
			"M2" << cameraMatrix[1] << "D2" << distCoeffs[1];
		fs.release();
	}
	else
		std::cout << "Error: can not save the intrinsic parameters\n";

	cv::Mat R1, R2, P1, P2, Q;
	cv::Rect validRoi[2];

	stereoRectify(cameraMatrix[0], distCoeffs[0],
		cameraMatrix[1], distCoeffs[1],
		imageSize, R, T, R1, R2, P1, P2, Q,
	              cv::CALIB_ZERO_DISPARITY, 1, imageSize, &validRoi[0], &validRoi[1]);

	fs.open("F:\\extrinsics.yml", cv::FileStorage::WRITE);
	if (fs.isOpened())
	{
		fs << "R" << R << "T" << T << "R1" << R1 << "R2" << R2 << "P1" << P1 << "P2" << P2 << "Q" << Q;
		fs.release();
	}
	else
		std::cout << "Error: can not save the extrinsic parameters\n";

	// OpenCV can handle left-right
	// or up-down camera arrangements
	bool isVerticalStereo = fabs(P2.at<double>(1, 3)) > fabs(P2.at<double>(0, 3));

	// COMPUTE AND DISPLAY RECTIFICATION
	if (!showRectified)
		return;

	cv::Mat rmap[2][2];
	// IF BY CALIBRATED (BOUGUET'S METHOD)
	if (useCalibrated)
	{
		// we already computed everything
	}
	// OR ELSE HARTLEY'S METHOD
	else
		// use intrinsic parameters of each camera, but
		// compute the rectification transformation directly
		// from the fundamental matrix
	{
		std::vector<cv::Point2f> allimgpt[2];
		for (k = 0; k < 2; k++)
		{
			for (i = 0; i < nimages; i++)
				std::copy(imagePoints[k][i].begin(), imagePoints[k][i].end(), back_inserter(allimgpt[k]));
		}
		F = cv::findFundamentalMat(cv::Mat(allimgpt[0]), cv::Mat(allimgpt[1]), cv::FM_8POINT, 0, 0);
		cv::Mat H1, H2;
		stereoRectifyUncalibrated(cv::Mat(allimgpt[0]), cv::Mat(allimgpt[1]), F, imageSize, H1, H2, 3);

		R1 = cameraMatrix[0].inv()*H1*cameraMatrix[0];
		R2 = cameraMatrix[1].inv()*H2*cameraMatrix[1];
		P1 = cameraMatrix[0];
		P2 = cameraMatrix[1];
	}

	//Precompute maps for cv::remap()
	initUndistortRectifyMap(cameraMatrix[0], distCoeffs[0], R1, P1, imageSize, CV_16SC2, rmap[0][0], rmap[0][1]);
	initUndistortRectifyMap(cameraMatrix[1], distCoeffs[1], R2, P2, imageSize, CV_16SC2, rmap[1][0], rmap[1][1]);

	cv::Mat canvas;
	double sf;
	int w, h;
	if (!isVerticalStereo)
	{
		sf = 600. / MAX(imageSize.width, imageSize.height);
		w = cvRound(imageSize.width*sf);
		h = cvRound(imageSize.height*sf);
		canvas.create(h, w * 2, CV_8UC3);
	}
	else
	{
		sf = 300. / MAX(imageSize.width, imageSize.height);
		w = cvRound(imageSize.width*sf);
		h = cvRound(imageSize.height*sf);
		canvas.create(h * 2, w, CV_8UC3);
	}

	for (i = 0; i < nimages; i++)
	{
		for (k = 0; k < 2; k++)
		{
			cv::Mat img = cv::imread(goodImageList[i * 2 + k], 0), rimg, cimg;
			remap(img, rimg, rmap[k][0], rmap[k][1], cv::INTER_LINEAR);
			cvtColor(rimg, cimg, cv::COLOR_GRAY2BGR);
			cv::Mat canvasPart = !isVerticalStereo ? canvas(cv::Rect(w*k, 0, w, h)) : canvas(cv::Rect(0, h*k, w, h));
			resize(cimg, canvasPart, canvasPart.size(), 0, 0, cv::INTER_AREA);
			if (useCalibrated)
			{
				cv::Rect vroi(cvRound(validRoi[k].x*sf), cvRound(validRoi[k].y*sf),
					cvRound(validRoi[k].width*sf), cvRound(validRoi[k].height*sf));
				rectangle(canvasPart, vroi, cv::Scalar(0, 0, 255), 3, 8);
			}
		}

		if (!isVerticalStereo)
			for (j = 0; j < canvas.rows; j += 16)
				line(canvas, cv::Point(0, j), cv::Point(canvas.cols, j), cv::Scalar(0, 255, 0), 1, 8);
		else
			for (j = 0; j < canvas.cols; j += 16)
				line(canvas, cv::Point(j, 0), cv::Point(j, canvas.rows), cv::Scalar(0, 255, 0), 1, 8);
		imshow("rectified", canvas);
		char c = (char)cv::waitKey();
		if (c == 27 || c == 'q' || c == 'Q')
			break;
	}
}

double StereoCalibrate::computeReprojectionErrors(const std::vector<std::vector<cv::Point3f>>& objectPoints,
	const std::vector<std::vector<cv::Point2f>>& imagePoints, const std::vector<cv::Mat>& rvecs,
	const std::vector<cv::Mat>& tvecs, const cv::Mat& cameraMatrix, const cv::Mat& distCoeffs,
	std::vector<float>& perViewErrors)
{
	std::vector<cv::Point2f> imagePoints2;
	int i, totalPoints = 0;
	double totalErr = 0, err;
	perViewErrors.resize(objectPoints.size());

	for (i = 0; i < (int)objectPoints.size(); i++)
	{
		projectPoints(cv::Mat(objectPoints[i]), rvecs[i], tvecs[i],
			cameraMatrix, distCoeffs, imagePoints2);
		err = norm(cv::Mat(imagePoints[i]), cv::Mat(imagePoints2), cv::NORM_L2);
		int n = (int)objectPoints[i].size();
		perViewErrors[i] = (float)std::sqrt(err*err / n);
		totalErr += err * err;
		totalPoints += n;
	}

	return std::sqrt(totalErr / totalPoints);
}

void StereoCalibrate::calcChessboardCorners(cv::Size boardSize, float squareSize, std::vector<cv::Point3f>& corners,
	Pattern patternType)
{
	corners.resize(0);

	switch (patternType)
	{
	case CHESSBOARD:
	case CIRCLES_GRID:
		for (int i = 0; i < boardSize.height; i++)
			for (int j = 0; j < boardSize.width; j++)
				corners.push_back(cv::Point3f(float(j*squareSize),
					float(i*squareSize), 0));
		break;

	case ASYMMETRIC_CIRCLES_GRID:
		for (int i = 0; i < boardSize.height; i++)
			for (int j = 0; j < boardSize.width; j++)
				corners.push_back(cv::Point3f(float((2 * j + i % 2)*squareSize),
					float(i*squareSize), 0));
		break;

	default:
		CV_Error(cv::Error::StsBadArg, "Unknown pattern type\n");
	}
}

bool StereoCalibrate::calibrate_1D_core(const std::vector<std::vector<cv::Point2f>>& imagePoints, cv::Size imageSize,
	cv::Size boardSize, Pattern patternType, float squareSize, float aspectRatio, int flags, cv::Mat& cameraMatrix,
	cv::Mat& distCoeffs)
{
	std::vector<cv::Mat> rvecs, tvecs;
	std::vector<float> reprojErrs;


	cameraMatrix = cv::Mat::eye(3, 3, CV_64F);
	if (flags & cv::CALIB_FIX_ASPECT_RATIO)
		cameraMatrix.at<double>(0, 0) = aspectRatio;

	distCoeffs = cv::Mat::zeros(8, 1, CV_64F);

	std::vector<std::vector<cv::Point3f> > objectPoints(1);
	calcChessboardCorners(boardSize, squareSize, objectPoints[0], patternType);

	objectPoints.resize(imagePoints.size(), objectPoints[0]);

	double rms = calibrateCamera(objectPoints, imagePoints, imageSize, cameraMatrix,
		distCoeffs, rvecs, tvecs, flags | cv::CALIB_FIX_K3 | cv::CALIB_FIX_K4 | cv::CALIB_FIX_K5);
	printf("RMS error reported by calibrateCamera: %g\n", rms);

	bool ok = checkRange(cameraMatrix) && checkRange(distCoeffs);

	double totalAvgErr = computeReprojectionErrors(objectPoints, imagePoints,
		rvecs, tvecs, cameraMatrix, distCoeffs, reprojErrs);

	printf("%s. avg reprojection error = %.2f\n", ok ? "Calibration succeeded" : "Calibration failed", totalAvgErr);

	return ok;
}
/*
 *��Ŀ�궨
 *	cv::Size		[in]	boardSize				�궨��ߴ�
 *	float			[in]	squareSize				����ߴ�
 *	vector<string>	[in]	imageList				�궨ͼƬ�ļ���
 *	Mat&			[io]	cameraMatrix			�������
 *	Mat&			[io]	distCoeffs				����ϵ��
 *	float			[in]	aspectRatio=1			��߱�,ֻ�е�flag��ָ��CALIB_FIX_ASPECT_RATIOʱ��������
 *	Pattern			[in]	pattern=CHESSBOARD		�궨��ģʽ,��ѡ:
 *														CHESSBOARD				������,
 *														CIRCLES_GRID			Բ������,
 *														ASYMMETRIC_CIRCLES_GRID	�ǶԳ�Բ������
 *	int				[in]	flags=0					�궨��־λ,��ѡ
 *														CALIB_FIX_ASPECT_RATIO	�̶���߱�
 *														CALIB_ZERO_TANGENT_DIST
 *														CALIB_FIX_PRINCIPAL_POINT
 *	bool			[in]	showUndistorted=true	�Ƿ���ʾ����֮������
 */
void StereoCalibrate::Calib1D(cv::Size boardSize, float squareSize, std::vector<std::string> imageList,
	cv::Mat& cameraMatrix, cv::Mat& distCoeffs, float aspectRatio, Pattern pattern, int flags, bool showUndistorted)
{
	cv::Size imageSize;
	std::vector<std::vector<cv::Point2f> > imagePoints;
	int nframes = (int)imageList.size();
	cv::namedWindow("Image View", 1);

	for (int i = 0;; i++)
	{
		cv::Mat view, viewGray;
		if (i < (int)imageList.size())
			view = cv::imread(imageList[i], 1);

		if (view.empty())//���ݶ�����,��ʼ�궨
		{
			if (imagePoints.size() > 0)
				calibrate_1D_core(imagePoints, imageSize, boardSize, pattern, squareSize, aspectRatio, flags, cameraMatrix, distCoeffs);
			break;
		}

		imageSize = view.size();

		std::vector<cv::Point2f> pointbuf;
		cvtColor(view, viewGray, cv::COLOR_BGR2GRAY);

		bool found;
		switch (pattern)
		{
		case CHESSBOARD:
			found = findChessboardCorners(view, boardSize, pointbuf,
				cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_FAST_CHECK | cv::CALIB_CB_NORMALIZE_IMAGE);
			break;
		case CIRCLES_GRID:
			found = findCirclesGrid(view, boardSize, pointbuf);
			break;
		case ASYMMETRIC_CIRCLES_GRID:
			found = findCirclesGrid(view, boardSize, pointbuf, cv::CALIB_CB_ASYMMETRIC_GRID);
			break;
		default:
			return;
		}

		// improve the found corners' coordinate accuracy
		if (pattern == CHESSBOARD && found) cornerSubPix(viewGray, pointbuf, cv::Size(11, 11),
			cv::Size(-1, -1), cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 30, 0.1));

		if (found)
		{
			imagePoints.push_back(pointbuf);
		}

		if (found)
			drawChessboardCorners(view, boardSize, cv::Mat(pointbuf), found);

		std::string msg = "100/100";
		int baseLine = 0;
		cv::Size textSize = cv::getTextSize(msg, 1, 1, 1, &baseLine);
		cv::Point textOrigin(view.cols - 2 * textSize.width - 10, view.rows - 2 * baseLine - 10);


		msg = cv::format("%d/%d", (int)imagePoints.size(), nframes);

		putText(view, msg, textOrigin, 1, 1, cv::Scalar(0, 0, 255));

		imshow("Image View", view);
		char key = (char)cv::waitKey(50);

		if (key == 27)
			break;

	}

	if (showUndistorted)
	{
		cv::Mat view, rview, map1, map2;
		initUndistortRectifyMap(cameraMatrix, distCoeffs, cv::Mat(),
			getOptimalNewCameraMatrix(cameraMatrix, distCoeffs, imageSize, 1, imageSize, 0),
			imageSize, CV_16SC2, map1, map2);

		for (int i = 0; i < (int)imageList.size(); i++)
		{
			view = cv::imread(imageList[i], 1);
			if (view.empty())
				continue;
			//undistort( view, rview, cameraMatrix, distCoeffs, cameraMatrix );
			remap(view, rview, map1, map2, cv::INTER_LINEAR);
			imshow("Image View", rview);
			char c = (char)cv::waitKey();
			if (c == 27 || c == 'q' || c == 'Q')
				break;
		}
	}
}


/*
 *˫Ŀ�궨
 */
void StereoCalibrate::UseCalib()
{
	std::vector<std::string>imagelist;

	for (int i = 0; i < imagelistL->size(); ++i)
	{
		imagelist.push_back(imagelistL->at(i));
		imagelist.push_back(imagelistR->at(i));
	}


	StereoCalib(imagelist, boardSize, squareSize, true, true, true);
}
