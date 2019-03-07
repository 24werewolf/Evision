#define NOMINMAX
#include "StereoMatch.h"
#include <QFileDialog>
#include "EvisionUtils.h"
//#include <direct.h>
#include <qDebug>
#include "../EvisionElas/EvisionElas.h"
//#include <boost/filesystem/path.hpp>
//#include <boost/filesystem/operations.hpp>
//#include <pcl/common/common_headers.h>
//#include <pcl/io/pcd_io.h>
#include "../EvisionADCensus/imageprocessor.h"
#include "../EvisionADCensus/stereoprocessor.h"
//#include <boost/date_time/posix_time/ptime.hpp>
//#include <boost/thread/lock_algorithms.hpp>

#include <QTime>
#include "rectify.h"
#include <algorithm>
StereoMatch::StereoMatch(std::string img1_filename, std::string img2_filename, std::string cameraParams_filename)
{
	m_entity = StereoMatchParamEntity::getInstance();
	this->img1_filename = img1_filename;
	this->img2_filename = img2_filename;
	QFileInfo *_fileInfo1 = new QFileInfo(QString::fromStdString(img1_filename));
	QFileInfo *_fileInfo2 = new QFileInfo(QString::fromStdString(img2_filename));
	
	if(_fileInfo1->absolutePath()!=_fileInfo2->absolutePath())
	{
		//������ͼ����һ��
		//�Ȱ�������ͼ������һ��
	}

	this->cameraParams_filename = cameraParams_filename;
	//����midname:����ͼ��_����ͼ��
	std::string midname = _fileInfo1->baseName().toStdString();
	midname.append("_");
	midname.append(_fileInfo2->baseName().toStdString());
	this->root = _fileInfo1->absolutePath().toStdString().append("/");
	this->disparity_filename = _fileInfo1->absolutePath().toStdString().append("/disp-"+ midname+".png");
	this->disparity_raw_filename= _fileInfo1->absolutePath().toStdString().append("/disp-raw-" + midname + ".xml");
	this->point_cloud_filename = _fileInfo1->absolutePath().toStdString().append("/pointcloud-"+ midname +".pcd");

}

StereoMatch::~StereoMatch()
{
}
/*
 * ��ʼ��
 */
bool StereoMatch::init(bool needCameraParamFile)
{
	std::cout<<"��ʼ��..." <<std::endl;
	try
	{
		//1.��ͼƬ,����ԭͼ��ʽ��,�����ѡ���㷨����ͼƬ�ĸ�ʽ��Ҫ��,����ת��
		std::cout << "����ͼƬ..." << std::endl;
		img1 = cv::imread(img1_filename);
		img2 = cv::imread(img2_filename);
		if (img1.empty() || img2.empty())
		{
			emit openMessageBox(QStringLiteral("����"), QStringLiteral("����ͼ��Ϊ��!"));
			return false;
		}
		//2.��ȡ�������
		std::cout << "��ȡ�������..." << std::endl;
		bool flag = EvisionUtils::read_AllCameraParams(cameraParams_filename,
			&cameraMatrix1, &distCoeffs1, &cameraMatrix2, &distCoeffs2, &R, &T, &E, &F, &img_size, &R1, &P1, &R2, &P2, &Q, &roi1, &roi2);
		if(flag==false)
		{
			std::cout << "���������ȡʧ��!" << std::endl;
			return false;
		}
		//3.����������δУ����ͼƬ,���ڴ˴�����У��
		if (!m_entity->getRectifiedInput())
		{
			std::cout << "�������δУ����ͼƬ,����У��..." << std::endl;
			try
			{
				std::vector<cv::Mat>images, undistortedImages;
				images.push_back(img1);
				images.push_back(img2);

				cv::Size imageSize;
				imageSize.height = ((cv::Mat)images.at(0)).rows;
				imageSize.width = ((cv::Mat)images.at(0)).cols;

				//�Ȱ������ͼƬ���û������ֱ���������
				intrinsicExtrinsic::undistortStereoImages(images, undistortedImages, cameraMatrix1, cameraMatrix2, distCoeffs1, distCoeffs2);
				//��һ�����㼫�߽�������,�����Ѿ����������Ի����������Ϊ��0
				cv::Mat rmap[2][2];
				cv::Mat noDist = cv::Mat::zeros(5, 1, CV_32F);
				initUndistortRectifyMap(cameraMatrix1, noDist, R1, P1, imageSize, CV_16SC2, rmap[0][0], rmap[0][1]);
				initUndistortRectifyMap(cameraMatrix2, noDist, R2, P2, imageSize, CV_16SC2, rmap[1][0], rmap[1][1]);
				int imgCount = undistortedImages.size() / 2;
				//����ROI
				/*
				 *(std::max)for disable the macro max in winnt.h
				 *see: http://www.voidcn.com/article/p-okycmabx-bms.html
				 */
				cv::Point2i rectCorner1((std::max)(roi1.x, roi2.x), (std::max)(roi1.y, roi2.y));
				cv::Point2i rectCorner2((std::min)(roi1.x + roi1.width, roi2.x + roi2.width),
					(std::min)(roi1.y + roi1.height, roi2.y + roi2.height));
				cv::Rect validRoi = cv::Rect(rectCorner1.x, rectCorner1.y, rectCorner2.x - rectCorner1.x, rectCorner2.y - rectCorner1.y);
				cv::Mat  remapImg1, rectImg1, remapImg2, rectImg2;
				remap(undistortedImages[0], remapImg1, rmap[0][0], rmap[0][1], CV_INTER_LINEAR);
				rectImg1 = remapImg1(validRoi);//У�����
				remap(undistortedImages[1], remapImg2, rmap[1][0], rmap[1][1], CV_INTER_LINEAR);
				rectImg2 = remapImg2(validRoi);//У�����

				img1 = rectImg1;
				img2 = rectImg2;
				std::cout << "У�����" << std::endl;

			}catch(...)
			{
				std::cout << "У�������з��������ش���" << std::endl;
				return false;
			}
		}
		else
		{
			std::cout << "�������У������ͼƬ,����У��..." << std::endl;
		}		
	}
	catch (...)
	{
		std::cout << "ƥ��ģ��ĳ�ʼ�����̷������ش���!" << std::endl;
		return false;
	}
	std::cout << "��ʼ�����..." << std::endl;
	return true;
}

/*
 * �̷߳���
 */
void StereoMatch::run()
{
	try
	{
		if (m_entity->getBM() == true)
		{
			OpenCVBM();
		}
		else if (m_entity->getSGBM() == true)
		{
			OpenCVSGBM();
		}
		else if (m_entity->getElas() == true)
		{
			Elas();
		}
		else if (m_entity->getADCensus() == true)
		{
			ADCensusDriver();
		}
	}
	catch(...)
	{
		std::cout << "�㷨ִ�й����г������ش���,�ص���:[StereoMatch �̷߳���]" << std::endl;
	}
}
/*
 * ����ԭʼ�Ӳ�����,�Ӳ�ʾ��ͼ,PCD����
 */
void StereoMatch::Save()
{
	if (!Raw_Disp_Data.empty() && !Gray_Disp_Data.empty())
	{
		try
		{
			cv::FileStorage fs(disparity_raw_filename, cv::FileStorage::WRITE);
			fs << "disp" << Raw_Disp_Data;
			fs.release();
			std::cout << "�Ѿ�����ԭʼ�Ӳ�����:" << disparity_raw_filename << std::endl;
			/*
			 * ������ʾ���Ӳ�ͼ������׼ȷ����,Ϊ�˻�����õ���ʾЧ���������ݽ�����һЩ�ü���ѹ��
			 * �����һ����0~255��ı�ԭʼ���Ӳ�����,���,����ʱ����ʹ��ԭʼ�Ӳ�����
			 */
			 //��ȡ�Ҷ��Ӳ�ͼ������
			cv::imwrite(disparity_filename, Gray_Disp_Data);
			std::cout << "�Ѿ������Ӳ�ʾ��ͼ:" << disparity_filename << std::endl;

			//����pcd����
#ifdef WITH_PCL
			EvisionUtils::createAndSavePointCloud(Raw_Disp_Data, img2, Q, point_cloud_filename);
			std::cout << "�Ѿ�����PCD����:" << point_cloud_filename << std::endl;
#endif
		}
		catch (...)
		{
			std::cout << "��������г������ش���!\n" << "�ص���:StereoMatch.cpp, void StereoMatch::Save()" << std::endl;
		}

	}
}

/*
 * ADCensus
 */
void StereoMatch::ADCensusDriver()
{

#pragma region ����
	// Minimum and maximum disparity
	uint dMin = 0;
	uint dMax = 60;

	// Parameters for the cost-initialization for the ADCensus
	cv::Size censusWin;
	censusWin.height = 9;
	censusWin.width = 7;
	float defaultBorderCost = 0.999;
	float lambdaAD = 10.0; // TODO Namen anpassen
	float lambdaCensus = 30.0;


	// Parameters for the cross-based cost aggregation
	uint aggregatingIterations = 4;
	uint colorThreshold1 = 20;
	uint colorThreshold2 = 6;
	uint maxLength1 = 34;
	uint maxLength2 = 17;

	// Parameters for the optimization of image cells
	uint colorDifference = 15;
	float pi1 = 0.1;
	float pi2 = 0.3;

	// Parameters for outlier detection
	uint dispTolerance = 0;
	// Parameters for the iterative range rating
	uint votingThreshold = 20;
	float votingRatioThreshold = 4;

	// Parameters for the proper interpolation
	uint maxSearchDepth = 20;

	// Parameters for the approximation of depths discontinuities 
	uint cannyThreshold1 = 20;
	uint cannyThreshold2 = 60;
	uint cannyKernelSize = 3;

	// Parameters for the sub-pixel enhancement
	uint blurKernelSize = 3;
#pragma endregion 
	m_entity->setIconImgL(img1);
	m_entity->setIconImgR(img2);
	//����Q����
	cv::Mat Q(4, 4, CV_64F);
	Q=this->Q;
	//����images
	std::vector<cv::Mat> images;
	images.push_back(img1);
	images.push_back(img2);
	if (images.size() % 2 == 0)
	{
		bool error = false;
		for (int i = 0; i < (images.size() / 2) && !error; ++i)
		{
			QTime time;
			time.start();//��ʱ��ʼ

			ImageProcessor iP(0.1);
			cv::Mat eLeft, eRight;
			eLeft = iP.unsharpMasking(images[i * 2], "gauss", 3, 1.9, -1);
			eRight = iP.unsharpMasking(images[i * 2 + 1], "gauss", 3, 1.9, -1);

			StereoProcessor sP(dMin, dMax, images[i * 2], images[i * 2 + 1], 
				censusWin, defaultBorderCost, lambdaAD, lambdaCensus, root,
				aggregatingIterations, colorThreshold1, colorThreshold2, maxLength1, maxLength2,
				colorDifference, pi1, pi2, dispTolerance, votingThreshold, votingRatioThreshold,
				maxSearchDepth, blurKernelSize, cannyThreshold1, cannyThreshold2, cannyKernelSize);
			string errorMsg;
			error = !sP.init(errorMsg);

			if (!error && sP.compute())
			{
				//�����Ӳ�����
				Raw_Disp_Data = sP.getDisparity();
				/*
				 * ������ʾ���Ӳ�ͼ������׼ȷ����,Ϊ�˻�����õ���ʾЧ���������ݽ�����һЩ�ü���ѹ��
				 * �����һ����0~255��ı�ԭʼ���Ӳ�����,���,����ʱ����ʹ��ԭʼ�Ӳ�����
				 */

				Gray_Disp_Data = sP.getGrayDisparity();
				//������ʾ�Ҷ��Ӳ�ͼ
				m_entity->setIconRawDisp(Gray_Disp_Data);
			}
			else
			{
				std::cout << "[ADCensusCV] " << errorMsg << endl;
			}
			std::cout << "Finished computation after " << time.elapsed() / 1000.0 << "s" << std::endl;
		}
	}
	else
	{
		std::cout << "[ADCensusCV] Not an even image number!" << std::endl;
	}
}
/*
 * OpenCV-BM
 */
void StereoMatch::OpenCVBM()
{
	std::cout << "BM��ʼ����..." << std::endl;
	cv::Mat img1G,img2G;
	cv::cvtColor(img1, img1G, CV_RGB2GRAY);//��ͼƬת��Ϊ�Ҷ�ͼ
	cv::cvtColor(img2, img2G, CV_RGB2GRAY);//��ͼƬת��Ϊ�Ҷ�ͼ

	m_entity->setIconImgL(img1G);
	m_entity->setIconImgR(img2G);
	cv::Ptr<cv::StereoBM> bm = cv::StereoBM::create();
	//bm->setROI1(roi1);
	//bm->setROI2(roi2);
	bm->setPreFilterCap(m_entity->getPrefilcap());
	bm->setBlockSize(m_entity->getSadWinsz());
	bm->setMinDisparity(m_entity->getMinDisp());
	bm->setNumDisparities(m_entity->getNumDisparities());
	bm->setTextureThreshold(m_entity->getTextThread());
	bm->setUniquenessRatio(m_entity->getUniradio());
	bm->setSpeckleWindowSize(m_entity->getSpecwinsz());
	bm->setSpeckleRange(m_entity->getSpecrange());
	bm->setDisp12MaxDiff(m_entity->getMaxdifdisp12());
	int64 t = cv::getTickCount();
	bm->compute(img1G, img2G, Raw_Disp_Data);

	//��ȡ������ʾ���Ӳ�ʾ��ͼ
	EvisionUtils::getGrayDisparity<float>(Raw_Disp_Data, Gray_Disp_Data);
	m_entity->setIconRawDisp(Gray_Disp_Data);

	t = cv::getTickCount() - t;

	std::cout << "Time elapsed: " << t * 1000 / cv::getTickFrequency() << "ms\n BM�������" << std::endl;
}
/*
 * OpenCV-SGBM
 */
void StereoMatch::OpenCVSGBM()
{
	std::cout << "SGBM ��ʼ����..." << std::endl;
	m_entity->setIconImgL(img1);
	m_entity->setIconImgR(img2);
	cv::Ptr<cv::StereoSGBM> sgbm = cv::StereoSGBM::create(0, 16, 3);

	sgbm->setPreFilterCap(m_entity->getPrefilcap());
	sgbm->setBlockSize(m_entity->getSadWinsz());
	int cn = img1.channels();
	sgbm->setP1(48 * cn*m_entity->getSadWinsz()*m_entity->getSadWinsz());
	sgbm->setP2(48 * cn*m_entity->getSadWinsz()*m_entity->getSadWinsz());
	sgbm->setMinDisparity(m_entity->getMinDisp());
	sgbm->setNumDisparities(m_entity->getNumDisparities());
	sgbm->setUniquenessRatio(m_entity->getUniradio());
	sgbm->setSpeckleWindowSize(m_entity->getSpecwinsz());
	sgbm->setSpeckleRange(m_entity->getSpecrange());
	sgbm->setDisp12MaxDiff(m_entity->getMaxdifdisp12());
	if (m_entity->getMODE_HH())
		sgbm->setMode(cv::StereoSGBM::MODE_HH);
	else if (m_entity->getMODE_SGBM())
		sgbm->setMode(cv::StereoSGBM::MODE_SGBM);
	else if (m_entity->getMODE_3WAY())
		sgbm->setMode(cv::StereoSGBM::MODE_SGBM_3WAY);

	int64 t = cv::getTickCount();
	sgbm->compute(img1, img2, Raw_Disp_Data);
	

	//��ȡ������ʾ���Ӳ�ʾ��ͼ
	EvisionUtils::getGrayDisparity<float>(Raw_Disp_Data, Gray_Disp_Data);
	m_entity->setIconRawDisp(Gray_Disp_Data);

	t = cv::getTickCount() - t;
	std::cout << "Time elapsed: " << t * 1000 / cv::getTickFrequency() << "ms\n SGBM�������" << std::endl;
}
/*
 * Elas
 */
void StereoMatch::Elas()
{
	ElasMatch(img1, img2);
}