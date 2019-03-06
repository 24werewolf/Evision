#pragma once
#include <qimage.h>
#include "opencv2\core\core.hpp"
#include "cv.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <QGraphicsView>
#include <QGraphicsScene>

/*
 * ʵ�ù��߷���
 */
class EvisionUtils
{
public:
	EvisionUtils();
	~EvisionUtils();
	/*
	 * cv::Matת��ΪQImage
	 */
	static QImage cvMat2QImage(const cv::Mat& mat);

	/*
	 * QImageת��Ϊcv::Mat
	 */
	static cv::Mat QImage2cvMat(QImage image);

	/*
	 * ��img��ʾ��view��
	 */
	static void ShowImageOnUi(cv::Mat& img, QGraphicsScene*sense, QGraphicsView* view);
	/*
	 * ��˫Ŀ�궨�õ������в���д���ļ�
	 * 1.�ļ���							std::string filename
	 * 2.�������1(��Խ������������)	cv::Mat& cameraMatrix1
	 * 3.����ϵ��1						cv::Mat& distCoeffs1
	 * 4.�������2						cv::Mat& cameraMatrix2
	 * 5.����ϵ��2						cv::Mat& distCoeffs2
	 * 6.�������֮�����ת				cv::Mat& R
	 * 7.�������֮���ƽ��				cv::Mat& T
	 * 8.���ʾ���						cv::Mat& E
	 * 9.��������						cv::Mat& F
	 * 10.ͼƬ�ߴ�						cv::Size& imageSize,
	 * 11.��תӳ�����1                 cv::Mat& R1,
	 * 12.ͶӰӳ�����1                 cv::Mat& P1,
	 * 13.��תӳ�����2                 cv::Mat& R2,
	 * 14.ͶӰӳ�����2                 cv::Mat& P2,
	 * 15.��άӳ�����                  cv::Mat& Q,
	 * 16.�������roi1                  cv::Rect& roi1,
	 * 17.�������roi2                  cv::Rect& roi2
	 * ����ֵ:
	 *	�ɹ�:true,ʧ�ܺͳ���:false
	 */
	static bool write_AllCameraParams(std::string& filename,
		cv::Mat& cameraMatrix1,
		cv::Mat& distCoeffs1,
		cv::Mat& cameraMatrix2,
		cv::Mat& distCoeffs2,
		cv::Mat& R,
		cv::Mat& T,
		cv::Mat& E,
		cv::Mat& F,
		cv::Size& imageSize,
		cv::Mat& R1,
		cv::Mat& P1,
		cv::Mat& R2,
		cv::Mat& P2,
		cv::Mat& Q,
		cv::Rect& roi1,
		cv::Rect& roi2);

	/*
	 * ���ļ��ж�ȡ˫Ŀ�궨�õ��Ĳ���
	 * 1.�ļ���							std::string filename
	 * 2.�������1(��Խ������������)	cv::Mat* cameraMatrix1
	 * 3.����ϵ��1						cv::Mat* distCoeffs1
	 * 4.�������2						cv::Mat* cameraMatrix2
	 * 5.����ϵ��2						cv::Mat* distCoeffs2
	 * 6.�������֮�����ת				cv::Mat* R
	 * 7.�������֮���ƽ��				cv::Mat* T
	 * 8.���ʾ���						cv::Mat* E
	 * 9.��������						cv::Mat* F
	 * 10.ͼƬ�ߴ�						cv::Size* imageSize,
	 * 11.��תӳ�����1                 cv::Mat* R1,
	 * 12.ͶӰӳ�����1                 cv::Mat* P1,
	 * 13.��תӳ�����2                 cv::Mat* R2,
	 * 14.ͶӰӳ�����2                 cv::Mat* P2,
	 * 15.��άӳ�����                  cv::Mat* Q,
	 * 16.�������roi1                  cv::Rect* roi1,
	 * 17.�������roi2                  cv::Rect* roi2
	 * ����ֵ:
	 *	�ɹ�:true,ʧ�ܺͳ���:false
	 */
	static bool read_AllCameraParams(std::string& filename,
		cv::Mat* cameraMatrix1,
		cv::Mat* distCoeffs1,
		cv::Mat* cameraMatrix2,
		cv::Mat* distCoeffs2,
		cv::Mat* R,
		cv::Mat* T,
		cv::Mat* E,
		cv::Mat* F,
		cv::Size* imageSize,
		cv::Mat* R1,
		cv::Mat* P1,
		cv::Mat* R2,
		cv::Mat* P2,
		cv::Mat* Q,
		cv::Rect* roi1,
		cv::Rect* roi2);

	/*
	 * ��ȡƥ������Ĳ���
	 */
	static bool read_ParamsForStereoMatch(std::string& filename,
		cv::Mat* cameraMatrix1,
		cv::Mat* distCoeffs1,
		cv::Mat* cameraMatrix2,
		cv::Mat* distCoeffs2, 
		cv::Mat* R1,
		cv::Mat* P1,
		cv::Mat* R2,
		cv::Mat* P2,
		cv::Mat* Q, 
		cv::Rect* roi1,
		cv::Rect* roi2);
	/*
	 * ��ȡУ������Ĳ���
	 */
	static bool read_ParamsForStereoRectify(std::string& filename,
		cv::Mat* cameraMatrix1,
		cv::Mat* distCoeffs1,
		cv::Mat* cameraMatrix2,
		cv::Mat* distCoeffs2,
		cv::Mat* R1,
		cv::Mat* P1,
		cv::Mat* R2,
		cv::Mat* P2,
		cv::Rect* roi1,
		cv::Rect* roi2);
	/*
	 * �ѵ��Ʊ������ļ���
	 */
	static bool write_PointCloud(std::string&filename, cv::Mat&PointCloudMatrix);
	/*
	 * ���ļ��ж�ȡ����
	 */
	static bool read_PointCloud(std::string&filename, cv::Mat*PointCloudMatrix);
#ifdef WITH_PCL
	/*
	 * ����PCD����
	 */
	static void createAndSavePointCloud(cv::Mat &disparity, cv::Mat &leftImage, cv::Mat &Q, std::string filename);
#endif
};

