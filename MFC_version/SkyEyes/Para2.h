 #pragma once
#include "afxcmn.h"


// CPara2 �Ի���

class CPara2 : public CDialog
{
	DECLARE_DYNAMIC(CPara2)

public:
	static CPara2* getInstance();//ȡ��ʵ��
	virtual ~CPara2();

// �Ի�������
	enum { IDD = IDD_PARA2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	CPara2(CWnd* pParent = NULL);   // ��׼���캯��
	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl s_nMinDisp;
	CSliderCtrl s_nUniqRatio;
	CSliderCtrl s_nSpeckWinSiz;
	CSliderCtrl s_nMaxDisp;
	CSliderCtrl s_nSpeckRange;
	CSliderCtrl s_nPreFiltCap;
	CSliderCtrl s_nSADWinSiz;
	CSliderCtrl s_nTextThres;
	CSliderCtrl s_nDisp12MaxDiff;
	CSliderCtrl s_nLevels;
	CSliderCtrl s_nPyrScale;
	CSliderCtrl s_nPolyn;
	CSliderCtrl s_nPolySigma;
	CSliderCtrl s_nFi;
	CSliderCtrl s_nLambda;
	int v_nMinDisp; //��С���ܵĲ���ֵ��ͨ���������㣬����ʱУ���㷨����ת��ͼ���������������Ҫ������
	int v_nMaxDisp; //������ȥ��С��ࡣ��ֵ���Ǵ����㡣��Ŀǰ��ʵ���У��˲��������ܱ�16������
	int v_nSADWinSiz;//ƥ����С���������Ǵ��ڵ���1��������ͨ������£���Ӧ����3��11֮��
	/*Margin in percentage by which the best (minimum) computed cost function value should ��win�� the second best value to consider the found match correct. 
	ͨ�������ֵ��[5,15]*/
	int v_nUniqRatio; //Ψһ��
	int v_nSpeckRange;//ɢ�߱�
	int v_nTextThres;
	
	int v_nSpeckWinSiz;/*���ǵ������ߵ����Ч�Ĺ⻬���Ӳ�������ߴ硣����Ϊ0����ɢ���˲���������������50-200��Χ���ڡ�*/
	/*Ԥ�˲�ͼ��Ľض�����ֵ. ���㷨�ȶ�ÿ�����ؼ���X-����ֵ,������Щֵ������[-preFilterCap, preFilterCap]֮��
	. �ٽ�������͸� Birchfield-Tomasi���ؼ�������*/
	int v_nPreFiltCap;//Ԥ�˲�ͼ��Ľض�����ֵ

	int v_nDisp12MaxDiff;//�������Ӳ��������������ֵ���������ص�λ������������Ϊ����ֵ��������øü�顣

	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	// �����������ն�Ӧ��������λ��
	void SetSlider();
	afx_msg void OnChangeEditMindisp();
	afx_msg void OnChangeEditDisp12maxdiff();
	afx_msg void OnChangeEditMaxdisp();
	afx_msg void OnChangeEditPrefiltcap();
	afx_msg void OnChangeEditSadwinsiz();
	afx_msg void OnChangeEditSpeckrange();
	afx_msg void OnChangeEditSpeckwinsiz();
	afx_msg void OnChangeEditTextthres();
	afx_msg void OnChangeEditUniqratio();
//	afx_msg void OnInitMenu(CMenu* pMenu);
	virtual BOOL OnInitDialog();
	
	// �����
	int v_nLevels;
	// ���ű���
	float v_nPyrScale;
	int v_nPolyN;
	// ��˹��׼��
	float v_nPolySigma;
	// ƽ����
	float v_nFi;
	// ��Եƽ��
	float v_nLambda;
//	afx_msg void OnEnChangeEditLevels();
	afx_msg void OnChangeEditLevels();
	afx_msg void OnChangeEditFi();
	afx_msg void OnChangeEditLambda();
	afx_msg void OnChangeEditPolyn();
	afx_msg void OnChangeEditPolysigma();
	afx_msg void OnChangeEditPyrscale();
};
static CPara2* CP2_instance;//����ģʽ