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
	int v_nMinDisp;
	int v_nMaxDisp;
	int v_nSADWinSiz;
	int v_nUniqRatio;
	int v_nSpeckRange;
	int v_nTextThres;
	int v_nSpeckWinSiz;
	int v_nPreFiltCap;
	int v_nDisp12MaxDiff;
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
};
static CPara2* CP2_instance;//����ģʽ