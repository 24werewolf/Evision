#pragma once

#include <QObject>
#include <core/affine.hpp>
#include <QThread>
/*
 *1.�����Ӧ���Ǹ�������
 *2.�洢�궨�ͽ��������������������
 *3.�����಻Ӧ�ó���������ʵ���ͳ�ö����������ڲ����͵�ʵ��
 *
 *4.����Ҫ�ķ�������Ӧ��ɾ��
 *5.ע��Ҫע�����뻹�����
 */

class Calibrater : public QThread
{
	Q_OBJECT

public:
	static Calibrater* getInstance();
	~Calibrater();
	void initialize();
private:
	Calibrater(QObject *parent = Q_NULLPTR);
	//���̽ǵ����� �ṹ��
	struct CornerDatas
	{
		int nPoints;			// ���̽ǵ�����
		int nImages;			// ����ͼ����
		int	nPointsPerImage;	// ÿ�����̵Ľǵ���
		cv::Size	imageSize;			// ͼ��ֱ���
		cv::Size	boardSize;			// ���̳ߴ�
		std::vector<std::vector<cv::Point3f> >	objectPoints;	// ���̽ǵ�������������
		std::vector<std::vector<cv::Point2f> >	imagePoints1;	// ����ͼ�����̽ǵ�������������
		std::vector<std::vector<cv::Point2f> >	imagePoints2;	// ����ͼ�����̽ǵ�������������
		CornerDatas()
		{
			nPoints=0;			
			nImages=0;			
			nPointsPerImage=0;	
			imageSize.height=0;
			imageSize.width = 0;
			boardSize.height = 0;
			boardSize.width = 0;
			objectPoints=*new std::vector<std::vector<cv::Point3f> >;	
			imagePoints1=*new std::vector<std::vector<cv::Point2f> >;	
			imagePoints2=*new std::vector<std::vector<cv::Point2f> >;	
		}
	};
	//��Ŀ�궨���������
	struct CameraParams
	{
		cv::Size		imageSize;				// ͼ��ֱ���
		cv::Mat			cameraMatrix;			// ���������
		cv::Mat			distortionCoefficients;	// ������������
		std::vector<cv::Mat> rotations;				// ����ͼƬ����ת����
		std::vector<cv::Mat> translations;			// ����ͼƬ��ƽ������
		int				flags;					// ��Ŀ�궨���õı�־λ
	};
	//˫Ŀ�궨���������
	struct StereoParams
	{
		cv::Size		imageSize;		// ͼ��ֱ���
		CameraParams	cameraParams1;	// ��������궨����
		CameraParams	cameraParams2;	// ��������궨����
		cv::Mat			rotation;		// ��ת����
		cv::Mat			translation;	// ƽ������
		cv::Mat			essential;		// ���ʾ���
		cv::Mat			foundational;	// ��������
		int				flags;			// ˫Ŀ�궨���õı�־λ
		double          alpha;
	};
	//˫ĿУ�����������
	struct RemapMatrixs
	{
		cv::Mat		mX1;	// ����ͼ X ��������ӳ�����
		cv::Mat		mY1;	// ����ͼ Y ��������ӳ�����
		cv::Mat		mX2;	// ����ͼ X ��������ӳ�����
		cv::Mat		mY2;	// ����ͼ Y ��������ӳ�����
		cv::Mat		Q;		// ���ڼ�����ά���Ƶ� Q ����
		cv::Rect	roi1;	// ����ͼ��Ч����ľ���
		cv::Rect	roi2;	// ����ͼ��Ч����ľ���
	};
public:
	CornerDatas cornerDatas;
	StereoParams stereoParams;
	RemapMatrixs remapMatrixs;
	//˫ĿУ������
	enum RECTIFYMETHOD { RECTIFY_BOUGUET, RECTIFY_HARTLEY };

	/*----------------------------
	* ���� : ��ʼ�����̽ǵ�������Ϣ
	*----------------------------
	* ���� : calib::initCornerData
	* ���� : public
	* ���� : 0 - ����ʧ�ܣ�1 - �����ɹ�
	*
	* ���� : nImages		[in]	����ͼ����
	* ���� : imageSize		[in]	ͼ��ֱ���
	* ���� : boardSize		[in]	���̽ǵ���
	* ���� : squareWidth	[in]	���̷�����
	*/
	int initCornerData(int nImages, cv::Size imageSize, cv::Size boardSize, float squareWidth);

	/*----------------------------
	* ���� : ���ݳɹ�����������Ŀ�޸����̽ǵ�����
	*----------------------------
	* ���� : calib::resizeCornerData
	* ���� : public
	* ���� : 0 - ����ʧ�ܣ�1 - �����ɹ�
	*
	* ���� : nImages		[in]	����ͼ����
	*/
	int resizeCornerData(int nImages);

	/*----------------------------
	* ���� : �������̽ǵ�������Ϣ
	*----------------------------
	* ���� : calib::loadCornerData
	* ���� : public
	* ���� : 0 - ����ʧ�ܣ�1 - �����ɹ�
	*
	* ���� : filename		[in]	�����ļ�·��/�ļ���
	* ���� : cornerDatas	[out]	��������̽ǵ�����
	*/
	int loadCornerData(const char* filename, CornerDatas& cornerDatas);

	/*----------------------------
	* ���� : �������̽ǵ�������Ϣ
	*----------------------------
	* ���� : calib::saveCornerData
	* ���� : public
	* ���� : 0 - ����ʧ�ܣ�1 - �����ɹ�
	*
	* ���� : filename		[in]	�����ļ�·��/�ļ���
	*/
	int saveCornerData(const char* filename);

	/*----------------------------
	* ���� : ������̽ǵ�
	*----------------------------
	* ���� : calib::detectCorners
	* ���� : public
	* ���� : 0 - ����ʧ�ܣ�1 - �����ɹ�
	*
	* ���� : img1			[in]	����ͼ
	* ���� : img2			[in]	����ͼ
	* ���� : imageCount		[in]	��ǰ���̽ǵ���ĳɹ�����
	*/
	int detectCorners(cv::Mat& img1, cv::Mat& img2,  int imageCount);

	/*----------------------------
	* ���� : �����ѱ궨�õ�������ڲ�����
	*----------------------------
	* ���� : calib::loadCameraParams
	* ���� : public
	* ���� : 0 - ����ʧ�ܣ�1 - �����ɹ�
	*
	* ���� : filename		[in]	�����ļ�·��/�ļ���
	* ���� : cameraParams	[out]	��������������
	*/
	int loadCameraParams(const char* filename, CameraParams& cameraParams);

	/*----------------------------
	* ���� : �����ѱ궨�õ�������ڲ�����
	*----------------------------
	* ���� : calib::saveCameraParams
	* ���� : public
	* ���� : 0 - ����ʧ�ܣ�1 - �����ɹ�
	*
	* ���� : cameraParams	[in]	�ѱ궨�����������
	* ���� : filename		[in]	�����ļ�·��/�ļ���
	*/
	int saveCameraParams(const CameraParams& cameraParams, const char* filename = "cameraParams.yml");

	/*----------------------------
	* ���� : ִ�е�Ŀ������궨
	*----------------------------
	* ���� : calib::calibrateSingleCamera
	* ���� : public
	* ���� : 0 - ����ʧ�ܣ�1 - �����ɹ�
	*
	* ���� : cornerDatas			[in]	���̽ǵ�����
	* ���� : cameraParams			[out]	˫Ŀ�궨����
	*/
	int calibrateSingleCamera(CornerDatas& cornerDatas, CameraParams& cameraParams);

	/*----------------------------
	* ���� : ִ��˫Ŀ������궨
	*		 ��ÿ���������δ�궨�������Ƚ��е�Ŀ�궨���ٽ���˫Ŀ�궨
	*----------------------------
	* ���� : calib::calibrateStereoCamera
	* ���� : public
	* ���� : 0 - ����ʧ�ܣ�1 - �����ɹ�
	*
	*/
	int calibrateStereoCamera();

	/*----------------------------
	* ���� : ���㵥Ŀ�궨���
	*----------------------------
	* ���� : calib::getCameraCalibrateError
	* ���� : public
	* ���� : 0 - ����ʧ�ܣ�1 - �����ɹ�
	*
	* ���� : _objectPoints	[in]	���̽ǵ����������
	* ���� : _imagePoints	[in]	���̽ǵ��ͼ������
	* ���� : cameraParams	[in]	�궨�����������
	* ���� : err			[out]	��Ŀ�궨���
	*/
	int getCameraCalibrateError(std::vector<std::vector<cv::Point3f> >& objectPoints, std::vector<std::vector<cv::Point2f> >& imagePoints, CameraParams& cameraParams, double err);

	/*----------------------------
	* ���� : ����˫Ŀ�궨���
	*----------------------------
	* ���� : calib::getStereoCalibrateError
	* ���� : public
	* ���� : 0 - ����ʧ�ܣ�1 - �����ɹ�
	*
	* ���� : err			[out]	˫Ŀ�궨���
	*/
	int getStereoCalibrateError(double& err);

	/*----------------------------------
	* ���� : ���ɵ�������ͷ��У������
	*----------------------------------
	* ���� : calib::rectifySingleCamera
	* ���� : public
	* ���� : 0 - ����ʧ�ܣ�1 - �����ɹ�
	*
	* ���� : cameraParams	[in]	�궨�����������
	* ���� : remapMatrixs	[out]	��ĿУ�����
	*/
	int rectifySingleCamera(CameraParams& cameraParams, RemapMatrixs& remapMatrixs);

	/*----------------------------
	* ���� : ִ��˫Ŀ�����У��
	*----------------------------
	* ���� : calib::rectifyStereoCamera
	* ���� : public
	* ���� : 0 - ����ʧ�ܣ�1 - �����ɹ�
	*
	* ���� : method			[in]	˫ĿУ������
	*/
	int rectifyStereoCamera(RECTIFYMETHOD method);

	/*----------------------------
	* ���� : ����˫ĿУ������
	*----------------------------
	* ���� : calib::saveCalibrationDatas
	* ���� : public
	* ���� : 0 - ����ʧ�ܣ�1 - �����ɹ�
	*
	* ���� : filename		[in]	����·��/�ļ���
	* ���� : method			[in]	˫ĿУ������
	*/
	int saveCalibrationDatas(const char* filename, RECTIFYMETHOD method);

	/*----------------------------------
	* ���� : ��ͼ�����У��
	*----------------------------------
	* ���� : calib::remapImage
	* ���� : public
	* ���� : 0 - ����ʧ�ܣ�1 - �����ɹ�
	*
	* ���� : img1			[in]	����ͼ��1
	* ���� : img2			[in]	����ͼ��2
	* ���� : img1r			[out]	У��ͼ��1
	* ���� : img2r			[out]	У��ͼ��2
	* ���� : remapMatrixs	[in]	ͼ��У��������ݣ��������������ӳ�����
	*/
	int remapImage(cv::Mat& img1, cv::Mat& img2, cv::Mat& img1r, cv::Mat& img2r, RemapMatrixs& remapMatrixs);
	
private:

	/*----------------------------
	* ���� : ��ͼ�����½���ʾָ��������Ϣ
	*----------------------------
	* ���� : calib::showText
	* ���� : private
	* ���� : void
	*
	* ���� : img	[in]	ͼ��
	* ���� : text	[in]	������Ϣ
	*/
	void showText(cv::Mat& img, std::string text);
};
