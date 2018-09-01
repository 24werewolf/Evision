// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���  
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�  
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://go.microsoft.com/fwlink/?LinkId=238214��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// MainFrm.h : CMainFrame ��Ľӿ�

//

#pragma once
#pragma comment( lib, "vfw32.lib" )  
#pragma comment( lib, "comctl32.lib" )  

#include "OutputWnd.h"
#include "opencv2\core\core.hpp"
#include "afxwin.h"
#include "afxcmn.h"
#include "stdlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <ctype.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "afxdialogex.h"
#include "calib.h"
#include "StereoMatch.h"
#include "PointCloudAnalyzer.h"
#include "string.h"
#include "cvaux.h"
#include "cxcore.h"
#include "highgui.h"
#include "cv.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "CvvImage.h"
#include "calib.h"
#include <math.h>
#define CalibWnd 541301
#define MatchWnd 541302
#define RangeWnd 541303

//using namespace std;
using namespace cv;
static Point moupoint = 0;
static Point moupoint2 = 0;//����������������Ĳ���������
class CMainFrame : public CFrameWndEx
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;
	COutputWnd        m_wndOutput;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnViewOutputWindow();
	afx_msg void OnUpdateViewOutputWindow(CCmdUI* pCmdUI);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	DECLARE_MESSAGE_MAP()
	
	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
public:
	/*===============================�û��Զ�����������============================*/
	   // ƥ���㷨ö��
	typedef enum { STEREO_BM, STEREO_SGBM, STEREO_VAR} STEREO_METHOD;
	   // ֡�����㷨ö��
	typedef enum { SHOW_ORIGINAL_FRAME, SHOW_EDGE_IMAGE, SHOW_EQUAL_HISTOGRAM, SHOW_CONVERT_COLOR } FRAME_PROCESS_METHOD;
	   // ���ģʽö��
	typedef enum { GetDepth, GetLength } RANGING_MODEL;
	   // ����궨���ýṹ��
	struct OptionCameraCalib
	{
		int				numberBoards;		   //���̼�����
		int				flagStereoCalib;	   //˫Ŀ�����־��
		int				numberFrameSkip;	   //�ǵ����֡������
		double   		squareSize;			   //���̷����С
		cv::Size		cornerSize;			   //���̽ǵ���
		double          alpha;                 //˫ĿУ������ϵ��
		calib::RECTIFYMETHOD	rectifyMethod; //ѡ���˫ĿУ���㷨
	};
private:
	// OpenCV��Ա
	cv::Mat m_lfImage;                          // ��������ͼ����ʾ
	cv::Mat m_riImage;                          // ��������ͼ����ʾ
	cv::Mat m_disparity;                        // �����Ӳ�ͼ����ʾ
    cv::Mat OriginalDisparity;                  // ԭʼ������        (ʹ��:����:OnBngivedisp();OnBnCompdisp())
	cv::Mat ProcessedImageL, ProcessedImageR;   // ��������������ͼ(ʹ��:����:OnBngivedisp() OnBnCompdisp())
	cv::Mat DisparityMap;                       // �Ӳ�ͼ            (ʹ��;����:OnBngivedisp();OnBnCompdisp();OnBnMouseon())
	cv::Mat DisparityMap2;                      // �Ӳ�ͼ����,�����ڲ�����������ʱ����е���            (ʹ��;����:)
	cv::Mat pointCloud;                         // ��ά����          (ʹ��:����:OnBnMouseon();OnBnCompdisp())
	cv::Mat TargetImageL, TargetImageR;         // ȫ�ֱ���: ����Ŀ��ͼ��      (ʹ��:����:OnBngivedisp(); RefreshDispMap())
	cv::Mat depth;                              // ȫ�ֱ���: ��ͼ�������ά����Ϊ�����������Ϣ (ʹ��:����:
	// �����ݳ�Ա
	CString WorkPath;                           // ����·��
	UINT m_nID_RAD;                             // ɫ�ʿռ�任����
	int m_ProcMethod;                           // ֡�����㷨
	int m_nCamCount;                            // ����ͷ��Ŀ
	int m_lfCamID;                              // ��ͷID
	int m_riCamID;                              // �Ҿ�ͷID
	int m_nImageWidth;                          // ����ֱ���:��
	int m_nImageHeight;                         // ����ֱ���:��
	int m_nImageChannels;                       // ���ͨ����
	double m_ObjectDistance;                    // Ŀ�����
	bool BOUGUET=true;                          // �Ƿ�ʹ��BOUGUET�궨�㷨?  true=BOUGUET; false=Hartley
	bool BM=true;                               // �Ƿ�ʹ��BMƥ���㷨?       true=BM;      false=SGBM    
	bool VAR;                                   // �Ƿ�ʹ��VAR�����?        true=ʹ��;    false=��ʹ��
	bool CalibDefaultParamEnable = false;       // �Ƿ����� �궨->Ĭ�ϲ���
	bool CalibDeleteParamEnable = false;        // �Ƿ����� �궨->�������        
	bool CalibFromImage = false;                // �Ƿ����� �궨->��ͼƬ�궨
	bool CalibFromCamera = false;               // �Ƿ����� �궨->������궨
	bool CalibFromFile = false;                 // �Ƿ����� �궨->���ļ��궨
	bool StopCalibFromCamera = false;           // �Ƿ����� �궨->ֹͣ�Ӿ�ͷ�궨
	bool MatchDefaultParamEnable = false;       // �Ƿ����� ƥ��->Ĭ�ϲ���
	bool MatchDeleteParamEnable = false;        // �Ƿ����� ƥ��->�������
	bool MatchBngivedispEnable = false;         // �Ƿ����� ƥ��->�����Ӳ�ͼ
	bool MatchDeepRebuildEnable = false;        // �Ƿ����� ƥ��->����ؽ�
	bool DoRefreshDisparityMapEnable = false;   // �Ƿ����� ƥ��->ˢ���Ӳ�ͼ
	bool RangeEnable = false;                   // �Ƿ����� �����ع���
	bool FileSelected = false;                  // �Ƿ�ѡ����ƥ��������ļ�
	bool IsSecondPoint = true;                 // �ǲ��ǵڶ�����
	STEREO_METHOD stereoMethod;		        // ѡ�������ƥ���㷨
	RANGING_MODEL rangingModel;
	// �����Ա
	VideoCapture lfCam;                         //��ͷ����
	VideoCapture riCam;                         //�Ҿ�ͷ����
	calib m_stereoCalibrator;                   //
	StereoMatch m_stereoMatcher;
	calib::CornerDatas cornerDatas;
	calib::StereoParams stereoParams;
	calib::RemapMatrixs remapMatrixs;
	CMainFrame::OptionCameraCalib optCalib;
	
private:
	/*===================================����Ĺ��߷���==================================*/
	// �������ƥ��Ĳ���
	void DoClearParamsOfStereoMatch();
	// �ļ�ѡ�����Ի���
	vector<CStringA> DoSelectFiles(LPCTSTR lpszDefExt, DWORD dwFlags, LPCTSTR lpszFilter, LPCTSTR lpstrTitle, LPCTSTR lpstrInitialDir);
	// ����ͼƬ����ʾ
	void F_ShowImage(Mat& src, Mat& des, UINT ID);
	// ��������ڵ�ָ��λ�����ָ���ı���Ϣ,
	void PutMessage(int wndID, LPCTSTR message);
	// ����ͼƬ֮ǰ�ĵ�������,Ψһһ�����õ��Ѿ���ע��
	void FixDisp(Mat_<float> & disp, int numofdisp);
	// ��궨�㺯��
	static void On_Mouse(int event, int x, int y, int flags, void *);
	// ˢ������ͷ
	void RefalshCamera();
	// ��ʾ����ͷʵʱ����
	void DoShowOrigFrame();
	// ִ��֡����
	void DoFrameProc(Mat& src, Mat& dst);
	// Canny��Ե���
	void F_EdgeDetectCanny(Mat& src, Mat& des);
	// ȷ���������������ѡ��
	bool DoParseOptionsOfCameraCalib(OptionCameraCalib& opt);
	// �Ӳ�ͼˢ�µ�ִ�к���
	void RefreshDisparityMap();
	// ��ƥ�������������������
	void SetSolver(int imgChannels);
public:
	/*================================�Զ�����Ϣ�Ļص�����===============================*/
	afx_msg LRESULT OnUserInitializable(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserChangeDPI(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserChangeFrameProcMethod(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserCPara4ChangeCameraL(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserCPara4ChangeCameraR(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserChangedpi(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRefreshDisparityMap(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnXYZAnalyse(WPARAM wParam, LPARAM lParam);
	/*===============================�����ǽ����¼��������==============================*/
	afx_msg void OnBnDefaultcamcalibparam();
	afx_msg void OnBndetectag();
	afx_msg void OnBn2stereocalib();
	afx_msg void OnBnStereodefparam();
	afx_msg void OnBngivedisp();
	afx_msg void OnBnCompdisp();
	afx_msg void OnRadBm();
	afx_msg void OnRadSgbm();
	afx_msg void OnBnMouseon();
	afx_msg void OnUpdateRadCalibfromimg(CCmdUI *pCmdUI);
	afx_msg void OnRadCalibfromimg();
	afx_msg void OnRadBouguet();
	afx_msg void OnUpdateRadBouguet(CCmdUI *pCmdUI);
	afx_msg void OnRadHartley();
	afx_msg void OnUpdateRadHartley(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRadBm(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRadSgbm(CCmdUI *pCmdUI);
	afx_msg void OnNewproject();
	afx_msg void OnOpenproject();
	afx_msg void OnOpenpath();
	afx_msg void OnHelpdoc();
	afx_msg void OnUpdateBnDefaultcamcalibparam(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBnDeletecamcalibparam(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBndetectag(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBn2stereocalib(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBnStereodefparam(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBnStereodeleteparam(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBngivedisp(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBnCompdisp(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBnMouseon(CCmdUI *pCmdUI);
	afx_msg void OnCloseproject();
	afx_msg void OnPaint();
	afx_msg void OnRefreshcam();
	afx_msg void OnBn1runcam();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBn2stopcam();
	afx_msg void OnTestcalib();
	afx_msg void OnStopcalib();
	afx_msg void OnChkCalculate();
	afx_msg void OnPhotograph();
	afx_msg void OnCalibfromyml();
	afx_msg void OnUpdateTestcalib(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCalibfromyml(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStopcalib(CCmdUI *pCmdUI);
	afx_msg void OnBnDeletecamcalibparam();
	afx_msg void OnBnStereodeleteparam();
	afx_msg void OnCheck2();
	afx_msg void OnUpdateCheck2(CCmdUI *pCmdUI);
	afx_msg void OnChkGc();
	afx_msg void OnUpdateChkGc(CCmdUI *pCmdUI);
	afx_msg void OnDorefreshdisparitymap();
	afx_msg void OnUpdateDorefreshdisparitymap(CCmdUI *pCmdUI);
	afx_msg void OnChkGetdepth();
	afx_msg void OnUpdateChkGetdepth(CCmdUI *pCmdUI);
	afx_msg void OnChkGetlength();
	afx_msg void OnUpdateChkGetlength(CCmdUI *pCmdUI);
};

