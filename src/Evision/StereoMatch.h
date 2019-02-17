#pragma once
#include <QThread>
#include <core/matx.hpp>
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core/utility.hpp"
#include "EvisionParamEntity.h"
#include "StereoMatchParamEntity.h"

/*
 * 
 */
class StereoMatch :public QThread
{
	Q_OBJECT
public:
	StereoMatch(std::string img1_filename, std::string img2_filename, std::string cameraParams_filename);
	~StereoMatch();
	bool init();
	void run();
	enum { STEREO_BM = 0, STEREO_SGBM = 1, STEREO_HH = 2, STEREO_VAR = 3, STEREO_3WAY = 4 };
	void saveXYZ(const char* filename, const cv::Mat& mat);
private:
	StereoMatchParamEntity * m_entity;
	//������ȡ���ļ�
	std::string img1_filename = "";
	std::string img2_filename = "";
	std::string cameraParams_filename = "";
	//���ڱ�����ļ�
	std::string disparity_filename = "";//�Ӳ�ͼ
	std::string point_cloud_filename = "";//�����ļ�
	//
	cv::Mat img1, img2;
	cv::Size img_size;

	cv::Mat cameraMatrix1;//������ڲ�
	cv::Mat distCoeffs1;//���������ϵ��
	cv::Mat cameraMatrix2;//������ڲ�
	cv::Mat distCoeffs2;//���������ϵ��
	cv::Mat R1, P1, R2, P2,Q;//ӳ�������
	cv::Rect roi1;
	cv::Rect roi2;
	int alg = STEREO_SGBM;

	bool no_display=false;
signals:
	void openMessageBox(QString, QString);
};