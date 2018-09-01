#pragma once
#include <core/types.hpp>
#include <vector>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/imgproc/imgproc_c.h>
#include "opencv2/highgui/highgui.hpp"
/*
 * ʵ����ά���Ʒ�������ز���
 */
class PointCloudUtils
{
public:
	PointCloudUtils();
	~PointCloudUtils();
	struct ObjectInfo
	{
		cv::Point		center;		//����
		double			distance;	//����
		double			area;		//���
		cv::Rect		boundRect;	//��Ӿ���
		cv::RotatedRect minRect;	//��С����

		// ���帳ֵ����
		void operator = (const ObjectInfo& rhs)
		{
			center = rhs.center;
			distance = rhs.distance;
			area = rhs.area;
			boundRect = rhs.boundRect;
			minRect = rhs.minRect;
		}

		// ���վ��붨���������
		bool operator < (const ObjectInfo& rhs) const   //��������ʱ����д�ĺ���
		{
			return distance < rhs.distance;
		}
		bool operator >(const ObjectInfo& rhs) const   //��������ʱ����д�ĺ���
		{
			return distance > rhs.distance;
		}

	};

	int detectNearObject(cv::Mat& image, cv::Mat& pointCloud, std::vector<ObjectInfo>& objectInfos);
	void showObjectInfo(std::vector<ObjectInfo>& objectInfos, cv::Mat& outImage);

private:

	void imageDenoising(cv::Mat& img, int iters);
	void parseCandidates(cv::Mat& objects, cv::Mat& depthMap, std::vector<ObjectInfo>& objectInfos);
};

