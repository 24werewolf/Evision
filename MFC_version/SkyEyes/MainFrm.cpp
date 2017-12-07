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

// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "SkyEyes.h"
#include "SkyEyesView.h"
#include "MainFrm.h"
#include "NewProject.h"
//#include "CameraDS.h"
#include "DirectShowHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_COMMAND(ID_VIEW_OUTPUTWND, &CMainFrame::OnViewOutputWindow)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OUTPUTWND, &CMainFrame::OnUpdateViewOutputWindow)
	ON_WM_SETTINGCHANGE()
	ON_COMMAND(IDC_BN_DefaultCamCalibParam, &CMainFrame::OnBnDefaultcamcalibparam)
	ON_COMMAND(IDC_BNDETECTAG, &CMainFrame::OnBndetectag)
	ON_COMMAND(IDC_BN_StereoDefParam, &CMainFrame::OnBnStereodefparam)
	ON_COMMAND(IDC_BNGIVEDISP, &CMainFrame::OnBngivedisp)
	ON_COMMAND(IDC_BN_CompDisp, &CMainFrame::OnBnCompdisp)
	ON_COMMAND(IDC_RAD_BM, &CMainFrame::OnRadBm)
	ON_COMMAND(IDC_RAD_SGBM, &CMainFrame::OnRadSgbm)
	ON_COMMAND(IDC_BN_MOUSEON, &CMainFrame::OnBnMouseon)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(IDC_RAD_BOUGUET, &CMainFrame::OnRadBouguet)
	ON_UPDATE_COMMAND_UI(IDC_RAD_BOUGUET, &CMainFrame::OnUpdateRadBouguet)
	ON_COMMAND(IDC_RAD_HARTLEY, &CMainFrame::OnRadHartley)
	ON_UPDATE_COMMAND_UI(IDC_RAD_HARTLEY, &CMainFrame::OnUpdateRadHartley)
	ON_UPDATE_COMMAND_UI(IDC_RAD_BM, &CMainFrame::OnUpdateRadBm)
	ON_UPDATE_COMMAND_UI(IDC_RAD_SGBM, &CMainFrame::OnUpdateRadSgbm)
	ON_COMMAND(ID_NewProject, &CMainFrame::OnNewproject)
	ON_COMMAND(ID_OpenProject, &CMainFrame::OnOpenproject)
	ON_COMMAND(ID_OpenPath, &CMainFrame::OnOpenpath)
	ON_COMMAND(ID_HelpDoc, &CMainFrame::OnHelpdoc)
	ON_UPDATE_COMMAND_UI(IDC_BN_DefaultCamCalibParam, &CMainFrame::OnUpdateBnDefaultcamcalibparam)
	ON_UPDATE_COMMAND_UI(IDC_BN_DeleteCamCalibParam, &CMainFrame::OnUpdateBnDeletecamcalibparam)
	ON_UPDATE_COMMAND_UI(IDC_BNDETECTAG, &CMainFrame::OnUpdateBndetectag)
	ON_UPDATE_COMMAND_UI(IDC_BN_StereoDefParam, &CMainFrame::OnUpdateBnStereodefparam)
	ON_UPDATE_COMMAND_UI(IDC_BN_StereoDeleteParam, &CMainFrame::OnUpdateBnStereodeleteparam)
	ON_UPDATE_COMMAND_UI(IDC_BNGIVEDISP, &CMainFrame::OnUpdateBngivedisp)
	ON_UPDATE_COMMAND_UI(IDC_BN_CompDisp, &CMainFrame::OnUpdateBnCompdisp)
	ON_UPDATE_COMMAND_UI(IDC_BN_MOUSEON, &CMainFrame::OnUpdateBnMouseon)
	ON_COMMAND(ID_CloseProject, &CMainFrame::OnCloseproject)
	ON_WM_PAINT()
	ON_MESSAGE(WM_USER_Initializable, &CMainFrame::OnUserInitializable)
	ON_COMMAND(ID_RefreshCam, &CMainFrame::OnRefreshcam)
	ON_MESSAGE(WM_USER_ChangeDPI, &CMainFrame::OnUserChangeDPI)
	ON_COMMAND(IDC_BN1RunCam, &CMainFrame::OnBn1runcam)
	ON_MESSAGE(WM_USER_CPara4ChangeCameraL, &CMainFrame::OnUserCPara4ChangeCameraL)
	ON_MESSAGE(WM_USER_CPara4ChangeCameraR, &CMainFrame::OnUserCPara4ChangeCameraR)
	ON_MESSAGE(WM_USER_ChangeFrameProcMethod, &CMainFrame::OnUserChangeFrameProcMethod)
	ON_WM_TIMER()
	ON_COMMAND(IDC_BN2StopCam, &CMainFrame::OnBn2stopcam)
	ON_COMMAND(ID_TESTCALIB, &CMainFrame::OnTestcalib)
	ON_COMMAND(ID_STOPCALIB, &CMainFrame::OnStopcalib)
	ON_COMMAND(ID_Photograph, &CMainFrame::OnPhotograph)
	ON_COMMAND(ID_CalibFromYML, &CMainFrame::OnCalibfromyml)
	ON_UPDATE_COMMAND_UI(ID_TESTCALIB, &CMainFrame::OnUpdateTestcalib)
	ON_UPDATE_COMMAND_UI(ID_CalibFromYML, &CMainFrame::OnUpdateCalibfromyml)
	ON_UPDATE_COMMAND_UI(ID_STOPCALIB, &CMainFrame::OnUpdateStopcalib)
	ON_COMMAND(IDC_BN_DeleteCamCalibParam, &CMainFrame::OnBnDeletecamcalibparam)
	ON_COMMAND(IDC_BN_StereoDeleteParam, &CMainFrame::OnBnStereodeleteparam)
	ON_COMMAND(ID_CHECK2, &CMainFrame::OnCheck2)
	ON_UPDATE_COMMAND_UI(ID_CHECK2, &CMainFrame::OnUpdateCheck2)
	ON_MESSAGE(WM_USER_RefreshDisparityMap, &CMainFrame::OnRefreshDisparityMap)
	ON_COMMAND(ID_DoRefreshDisparityMap, &CMainFrame::OnDorefreshdisparitymap)
	ON_UPDATE_COMMAND_UI(ID_DoRefreshDisparityMap, &CMainFrame::OnUpdateDorefreshdisparitymap)
	ON_COMMAND(ID_CHK_GetDepth, &CMainFrame::OnChkGetdepth)
	ON_UPDATE_COMMAND_UI(ID_CHK_GetDepth, &CMainFrame::OnUpdateChkGetdepth)
	ON_COMMAND(ID_CHK_GetLength, &CMainFrame::OnChkGetlength)
	ON_UPDATE_COMMAND_UI(ID_CHK_GetLength, &CMainFrame::OnUpdateChkGetlength)
	ON_MESSAGE(WM_USER_XYZAnalyse, &CMainFrame::OnXYZAnalyse)
END_MESSAGE_MAP()

// CMainFrame ����/����WM_USER_XYZAnalyse

CMainFrame::CMainFrame()
: m_ProcMethod(0)
, m_nImageWidth(0)
, m_nImageHeight(0)
, BOUGUET(false)
, BM(false)
, m_nCamCount(0)
, m_lfCamID(0)
, m_riCamID(0)
, VAR(false)
{
	// TODO:  �ڴ���ӳ�Ա��ʼ������
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2007_BLACK);
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}

	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

	// ���� Visual Studio 2005 ��ʽͣ��������Ϊ
	CDockingManager::SetDockingMode(DT_SMART);
	// ���� Visual Studio 2005 ��ʽͣ�������Զ�������Ϊ
	EnableAutoHidePanes(CBRS_ALIGN_ANY);
	//EnableLoadDockState(FALSE);//��ֹ����������״̬
	// ����ͣ������
	if (!CreateDockingWindows())
	{
		TRACE0("δ�ܴ���ͣ������\n");
		return -1;
	}

	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndOutput);
	m_wndOutput.SetControlBarStyle(~AFX_CBRS_CLOSE);//��ֹ�û��ر��������
	//m_wndOutput.SetControlBarStyle(AFX_CBRS_RESIZE);//��ֹ�û����������ִ�в������
	// ���ڳ־�ֵ�����Ӿ�����������ʽ
	OnApplicationLook(theApp.m_nAppLook);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;
	// �����������
	CString strOutputWnd;
	bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
	ASSERT(bNameValid);
	if (!m_wndOutput.Create(strOutputWnd, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ����������\n");
		return FALSE; // δ�ܴ���
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndOutput.SetIcon(hOutputBarIcon, FALSE);

}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(TRUE);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
	}

	m_wndOutput.UpdateFonts();
	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

void CMainFrame::OnViewOutputWindow()
{
	// ��ʾ�򼤻�񣬾���ȡ���ڵ�ǰ״̬��
	// ֻ��ͨ������֡�ϵ� [x] ��ť�رմ���
	m_wndOutput.ShowPane(TRUE, FALSE, TRUE);
	m_wndOutput.SetFocus();
}

void CMainFrame::OnUpdateViewOutputWindow(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CFrameWndEx::OnSettingChange(uFlags, lpszSection);
	m_wndOutput.UpdateFonts();
}

void CMainFrame::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CFrameWndEx::OnPaint()
	//OnPaint();
	UpdateWindow();				// ����windows���ڣ�������ⲽ���ã�ͼƬ��ʾ�����������
	if (!m_lfImage.empty() || m_riImage.empty() || !m_disparity.empty())
	{
		F_ShowImage(m_lfImage, m_lfImage, IDC_PicLfCam);		// �ػ�ͼƬ����
		F_ShowImage(m_riImage, m_riImage, IDC_PicRiCam);		// �ػ�ͼƬ����
		F_ShowImage(m_disparity, m_disparity, IDC_PicSynImg);	// �ػ�ͼƬ����
	}
	/*ע��:���ڳ����жԻ�ͼ����ĳ�ʼ����Ҫִ��"�½�����"����"�򿪹���",���Խ���ոռ������ʱ��,������������IF����,
	����ͼ���򲢲��Ǻ�ɫ��.*/
}

/*======================================================================================*/
/*                        ������һ����Ӧ�Զ�����Ϣ�ļ�����                              */
/*======================================================================================*/

//��Ӧ�Զ�����Ϣ,����Ϣ��SkyEyes.cpp(APP��)�з���,�յ�����Ϣ,���ɽ��г�ʼ������
afx_msg LRESULT CMainFrame::OnUserInitializable(WPARAM wParam, LPARAM lParam)
{
	//�յ�����Ϣ���������Ѿ���ɼ���,���Խ����û�����ĳ�ʼ��������
	//1.��ʼ��ͼ����ʾ�ؼ�����ر���
	CRect rect;
	this->GetActiveView()->GetDlgItem(IDC_PicLfCam)->GetClientRect(&rect);
	m_lfImage = Mat::zeros(rect.Height(), rect.Width(), CV_8UC3);
	this->GetActiveView()->GetDlgItem(IDC_PicRiCam)->GetClientRect(&rect);
	m_riImage = Mat::zeros(rect.Height(), rect.Width(), CV_8UC3);
	this->GetActiveView()->GetDlgItem(IDC_PicSynImg)->GetClientRect(&rect);
	m_disparity = Mat::zeros(rect.Height(), rect.Width(), CV_8UC3);
	Invalidate();//ˢ�´���
	UpdateWindow();
	//2.��ȡ����ͷ��Ŀ�ʹ���
	RefalshCamera();
	//3.��д֡������ ��ʾԭʼ����;Canny��Ե���;ֱ��ͼ����;ɫ�ʿռ�任;
	CPara4::getInstance()->m_CP4MethodList.SetCurSel(0);
	return 0;
}

//���յ�����DPI����Ϣ,����Ϣ��CPara1/4����,�ɱ��ಶ��,���ಢ����
afx_msg LRESULT CMainFrame::OnUserChangeDPI(WPARAM wParam, LPARAM lParam)
{
	int index =0;
	//�ж���Ϣ��Դ,���ԳƲ���
	if (wParam == 1){
		index = CPara1::getInstance()->m_CP1Resolution.GetCurSel();//��1ȡֵ
		CPara4::getInstance()->m_CP4Resolution.SetCurSel(index);//��4��ֵ
	}
	if (wParam == 4){
		index = CPara4::getInstance()->m_CP4Resolution.GetCurSel();//��4ȡֵ
		CPara1::getInstance()->m_CP1Resolution.SetCurSel(index);//��1��ֵ
	}
	switch (index)
	{
	case 0:
		m_nImageWidth = 640;
		m_nImageHeight = 480;
		break;
	case 1:
		m_nImageWidth = 352;
		m_nImageHeight = 288;
		break;
	case 2:
		m_nImageWidth = 320;
		m_nImageHeight = 240;
		break;
	default:
		m_nImageWidth = 352;
		m_nImageHeight = 288;
	}
	m_nImageChannels = 3;
	return 0;
}

//���յ�����֡����������Ϣ,����Ϣ��CPara4����,�ɱ��ಶ�񲢴���
afx_msg LRESULT CMainFrame::OnUserChangeFrameProcMethod(WPARAM wParam, LPARAM lParam)
{
	m_ProcMethod = CPara4::getInstance()->m_CP4MethodList.GetCurSel();
	return 0;
}

//���յ�����������ͷ����Ϣ,����Ϣ��CPara1/4����,�ɱ��ಶ��,���ಢ����
afx_msg LRESULT CMainFrame::OnUserCPara4ChangeCameraL(WPARAM wParam, LPARAM lParam)
{
	// ȷ����������ͷ��Ӧ���豸��ţ���Ӧ�����˵�ѡ�������ţ�
	//�ж���Ϣ��Դ,���ԳƲ���
	if (wParam == 1){
		m_lfCamID = CPara1::getInstance()->m_CP1CamList_L.GetCurSel();//��1ȡֵ
		CPara4::getInstance()->m_CP4CamList_L.SetCurSel(m_lfCamID);//��4��ֵ
	}
	if (wParam == 4){
		m_lfCamID = CPara4::getInstance()->m_CP4CamList_L.GetCurSel();//��4ȡֵ
		CPara1::getInstance()->m_CP1CamList_L.SetCurSel(m_lfCamID);//��1��ֵ
	}
	return 0;
}

//���յ�����������ͷ����Ϣ,����Ϣ��CPara1/4����,�ɱ��ಶ��,���ಢ����
afx_msg LRESULT CMainFrame::OnUserCPara4ChangeCameraR(WPARAM wParam, LPARAM lParam)
{
	//�ж���Ϣ��Դ,���ԳƲ���
	if (wParam == 1){
		m_riCamID = CPara1::getInstance()->m_CP1CamList_R.GetCurSel();//��1ȡֵ
		CPara4::getInstance()->m_CP4CamList_R.SetCurSel(m_riCamID);//��4��ֵ
	}
	if (wParam == 4){
		m_riCamID = CPara4::getInstance()->m_CP4CamList_R.GetCurSel();//��4ȡֵ
		CPara1::getInstance()->m_CP1CamList_R.SetCurSel(m_riCamID);//��1��ֵ
	}
	return 0;
}

//���յ�ˢ���Ӳ�ͼ����Ϣ,����Ϣ��CPara2����,�ɱ��ಶ��,���ಢ����
afx_msg LRESULT CMainFrame::OnRefreshDisparityMap(WPARAM wParam, LPARAM lParam)
{
	if (FileSelected == true){
		DoRefreshDisparityMapEnable = true;//ֻ��ѡ�����ļ���������ˢ�¹���
		if (stereoMethod == STEREO_VAR){   //���ʹ�õ���VAR�㷨,���Խ���ʵʱˢ�¶�����Ҫ�ֶ����
			RefreshDisparityMap();
		}
		
	}
	return 0;
}



/*======================================================================================*/
/*                                �����Ǳ���Ĺ��߷�������                              */
/*======================================================================================*/

// ˢ������ͷ
void CMainFrame::RefalshCamera()
{
	DirectShowHelper dsHelper;
	std::vector<std::wstring> devices;
	dsHelper.enumerateDevices(CLSID_VideoInputDeviceCategory, devices);

	m_nCamCount = devices.size();
	if (m_nCamCount < 1)
	{
		AfxMessageBox(_T("δ��⵽����ͷ!��ع��ܽ��޷�ʹ��!"));
		//return -1;
	}

	// ����Ͽ�CamList���������ͷ���Ƶ��ַ���
	//char camera_name[1024];
	//char istr[1024];
	//CString camstr;
	CPara1::getInstance()->m_CP1CamList_R.EnableWindow(TRUE);
	CPara1::getInstance()->m_CP1CamList_L.ResetContent();
	CPara1::getInstance()->m_CP1CamList_R.ResetContent();
	CPara4::getInstance()->m_CP4CamList_R.EnableWindow(TRUE);
	CPara4::getInstance()->m_CP4CamList_L.ResetContent();
	CPara4::getInstance()->m_CP4CamList_R.ResetContent();
	for (int i = 0; i < m_nCamCount; i++)
	{
		//int retval = CCameraDS::CameraName(i, camera_name, sizeof(camera_name));

		//sprintf_s(istr, "#%d ", i);
		//strcat_s(istr, camera_name);
		//camstr = istr;
		if (devices[i].empty()==false)
		{
			CPara1::getInstance()->m_CP1CamList_L.AddString(CString(devices[i].c_str()));
			CPara1::getInstance()->m_CP1CamList_R.AddString(CString(devices[i].c_str()));
			CPara4::getInstance()->m_CP4CamList_L.AddString(CString(devices[i].c_str()));
			CPara4::getInstance()->m_CP4CamList_R.AddString(CString(devices[i].c_str()));
		}
		else
			AfxMessageBox(_T("���ܻ�ȡ����ͷ������"));
	}
	//camstr.ReleaseBuffer();
	if (m_nCamCount <= 1)
	{
		CPara1::getInstance()->m_CP1CamList_R.EnableWindow(FALSE);
		CPara4::getInstance()->m_CP4CamList_R.EnableWindow(FALSE);
	}
		
}



// ������������Ѿ�������....�Ѿ�û�е��õ���
void CMainFrame::FixDisp(Mat_<float> & disp, int numofdisp)
{
	/*
	Mat_<float> disp1;
	float lastPixel = 10;
	int minDisparity = 23;
	//	disp.at<float>(0,144) = lastPixel;
	for (int i = 0; i < disp.rows; i++)
	{
		for (int j = numofdisp; j < disp.cols; j++)
		{
			if (disp(i, j) <= minDisparity) disp(i, j) = lastPixel;
			else lastPixel = disp(i, j);
		}
	}
	int an = 4;
	copyMakeBorder(disp, disp1, an, an, an, an, BORDER_REPLICATE);
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(an * 2 + 1, an * 2 + 1));
	morphologyEx(disp1, disp1, CV_MOP_OPEN, element);
	morphologyEx(disp1, disp1, CV_MOP_CLOSE, element);
	disp = disp1(Range(an, disp.rows - an), Range(an, disp.cols - an)).clone();
	*/
}

// ��ʾ����ͷʵʱ����
void CMainFrame::DoShowOrigFrame()
{
	// ��ͼ����������
	m_lfImage = Scalar(0);
	F_ShowImage(m_lfImage, m_lfImage, IDC_PicLfCam);

	m_riImage = Scalar(0);
	F_ShowImage(m_riImage, m_riImage, IDC_PicRiCam);

	CPara4::getInstance()->m_CP4MethodList.SetCurSel(0);
	m_ProcMethod = SHOW_ORIGINAL_FRAME;
	SetTimer(1, 50, NULL);	// 50ms ��ʱ��ʾ
}

// ��ʱ����Ӧ��Ҫ����û��˫Ŀ�����˫Ŀƥ�����ʱ��������ʾ�ʹ������
void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (lfCam.isOpened())
	{
		Mat lfFrame;
		lfCam >> lfFrame;

		if (m_ProcMethod != SHOW_ORIGINAL_FRAME)
		{
			DoFrameProc(lfFrame, lfFrame);
		}

		F_ShowImage(lfFrame, m_lfImage, IDC_PicLfCam);
	}
	if (riCam.isOpened())
	{
		Mat riFrame;
		riCam >> riFrame;

		if (m_ProcMethod != SHOW_ORIGINAL_FRAME)
		{
			DoFrameProc(riFrame, riFrame);
		}

		F_ShowImage(riFrame, m_riImage, IDC_PicRiCam);
	}
	CFrameWndEx::OnTimer(nIDEvent);
}

// ִ��֡����
void CMainFrame::DoFrameProc(Mat& src, Mat& dst)
{
	try
	{
		switch (m_ProcMethod)
		{
		case SHOW_EDGE_IMAGE:
		{
								F_EdgeDetectCanny(src, dst);
		}
			break;
		case SHOW_EQUAL_HISTOGRAM:
		{
									 vector<Mat> rgb;
									 // �ֽ��������
									 split(src, rgb);
									 // �Ը����������ν���ֱ��ͼ����
									 for (int i = 0; i<3; i++)
									 {
										 equalizeHist(rgb[i], rgb[i]);
									 }
									 // �ϲ�������
									 merge(rgb, dst);
		}
			break;
		case SHOW_CONVERT_COLOR:
		{
								   m_nID_RAD = CPara4::getInstance()->GetCheckedRadioButton(IDC_RAD_ToHSV, IDC_RAD_ToXYZ);
								   int type =
									   m_nID_RAD == IDC_RAD_ToHSV ? CV_BGR2HSV :
									   m_nID_RAD == IDC_RAD_ToHLS ? CV_BGR2HLS :
									   m_nID_RAD == IDC_RAD_ToLab ? CV_BGR2Lab :
									   m_nID_RAD == IDC_RAD_ToLuv ? CV_BGR2Luv :
									   m_nID_RAD == IDC_RAD_ToYCrCb ? CV_BGR2YCrCb :
									   CV_BGR2XYZ;
								   cvtColor(src, dst, type);
		}
			break;
		}
	}
	catch (cv::Exception& e)
	{
		char err[2048];
		sprintf_s(err, "��������: %s", e.what());
		CString errInfo;
		errInfo = err;
		AfxMessageBox(errInfo);
	}
	catch (...)
	{
		AfxMessageBox(_T("����δ֪����"));
	}

	return;
}

// Canny��Ե���
void CMainFrame::F_EdgeDetectCanny(Mat& src, Mat& des)
{
	Mat gray, edge, edge8u;

	edge = cv::Mat(src.size(), CV_16S);

	// ��Դͼ��תΪ�Ҷ�ͼ��
	if (src.channels() == 1)
		src.copyTo(gray);
	else
		cvtColor(src, gray, CV_RGB2GRAY);

	// ��Ե���
	Sobel(gray, edge, CV_16S, 0, 1);
	edge.convertTo(edge8u, CV_8U);

	// ����Ե���ͼ��ת�����ͼ���ʽ
	if (des.channels() == 1)
		edge8u.copyTo(des);
	else
		cvtColor(edge8u, des, CV_GRAY2BGR);
}

// ȷ���������������ѡ��
bool CMainFrame::DoParseOptionsOfCameraCalib(OptionCameraCalib& opt)
{
	//1.����궨�̲����趨
	CString temp;
	(CPara1::getInstance()->GetDlgItem(IDC_BoardWidth)->GetWindowText(temp));//�ǵ�-X
	if (atoi(temp) <= 0){
		return false;
	}
	opt.cornerSize.width = atoi(temp);
	(CPara1::getInstance()->GetDlgItem(IDC_BoardHeight)->GetWindowText(temp));//�ǵ�-Y
	if (atoi(temp) <= 0){
		return false;
	}
	opt.cornerSize.height = atoi(temp);
	(CPara1::getInstance()->GetDlgItem(IDC_SquareSize)->GetWindowText(temp));//����ߴ�
	if (atoi(temp) <= 0){
		return false;
	}
	opt.squareSize = atof(temp);
	(CPara1::getInstance()->GetDlgItem(IDC_nBoards)->GetWindowText(temp));   //��������
	if (atoi(temp) <= 0){
		return false;
	}
	opt.numberBoards = atoi(temp);

	//2.�����־λ�趨
	UINT nCheckIDs[5] = { IDC_CHK_FPP, IDC_CHK_UIG, IDC_CHK_FAR, IDC_CHK_SFL, IDC_CHK_FI };
	int nFlagDefs2[5] = { CV_CALIB_FIX_PRINCIPAL_POINT, CV_CALIB_USE_INTRINSIC_GUESS,
		CV_CALIB_FIX_ASPECT_RATIO, CV_CALIB_SAME_FOCAL_LENGTH, CV_CALIB_FIX_INTRINSIC };
	for (int i = 0; i<5; i++)
	{
		if (((CButton*)CPara1::getInstance()->GetDlgItem(nCheckIDs[i]))->GetCheck())
			opt.flagStereoCalib |= nFlagDefs2[i];
	}

	//3.�ǵ����֡������(������궨ʱ��ֵΪ30)
	opt.numberFrameSkip = 30;

	//4.ȷ��������ͼ����Դ������ͷ or ����ͼƬ��
	//opt.readLocalImage = LocalPicture;
	//if (opt.readLocalImage)		// ���ӱ���ͼƬ���룬����֡������Ϊ 5 ֡
		//opt.numberFrameSkip = 5;

	//5.ȷ�����̽ǵ��������ݵĻ�ȡ��ʽ���ֳ����㻹�Ǵ�YML�ļ��ж�ȡ
	//opt.loadConerDatas = ReadYML;

	//6.ȷ��˫ĿУ������ϵ��
	(CPara1::getInstance()->GetDlgItem(IDC_Alpha)->GetWindowText(temp));   //Alpha
	opt.alpha = atof(temp);
	if (opt.alpha < 0 || opt.alpha > 1)//���alphaԽ��ʹ��-1ΪĬ��ֵ
		opt.alpha = -1;

	//7.ȷ��˫ĿУ���㷨
	opt.rectifyMethod = (BOUGUET == true ? calib::RECTIFY_BOUGUET : calib::RECTIFY_HARTLEY);

	return true;
}

// ��ƥ�������������������
void CMainFrame::SetSolver(int imgChannels)
{
	//����Ӧ�������������������,ͬʱ����������ȷ��
	CString temp;
	switch (stereoMethod)
	{
	case STEREO_BM:
		(CPara2::getInstance()->GetDlgItem(IDC_EDIT_preFiltCap))->GetWindowText(temp);
		m_stereoMatcher.m_BM.state->preFilterCap = atoi(temp);
		(CPara2::getInstance()->GetDlgItem(IDC_EDIT_SADWinSiz))->GetWindowText(temp);
		m_stereoMatcher.m_BM.state->SADWindowSize = atoi(temp);
		(CPara2::getInstance()->GetDlgItem(IDC_EDIT_minDisp))->GetWindowText(temp);
		m_stereoMatcher.m_BM.state->minDisparity = atoi(temp);
		(CPara2::getInstance()->GetDlgItem(IDC_EDIT_maxDisp))->GetWindowText(temp);
		m_stereoMatcher.m_BM.state->numberOfDisparities = atoi(temp);
		(CPara2::getInstance()->GetDlgItem(IDC_EDIT_textThres))->GetWindowText(temp);
		m_stereoMatcher.m_BM.state->textureThreshold = atoi(temp);
		(CPara2::getInstance()->GetDlgItem(IDC_EDIT_uniqRatio))->GetWindowText(temp);
		m_stereoMatcher.m_BM.state->uniquenessRatio = atoi(temp);
		(CPara2::getInstance()->GetDlgItem(IDC_EDIT_speckWinSiz))->GetWindowText(temp);
		m_stereoMatcher.m_BM.state->speckleWindowSize = atoi(temp);
		(CPara2::getInstance()->GetDlgItem(IDC_EDIT_speckRange))->GetWindowText(temp);
		m_stereoMatcher.m_BM.state->speckleRange = atoi(temp);
		(CPara2::getInstance()->GetDlgItem(IDC_EDIT_disp12MaxDiff))->GetWindowText(temp);
		m_stereoMatcher.m_BM.state->disp12MaxDiff = atoi(temp);

		//	m_stereoMatcher.m_BM.state->preFilterSize=41;
		break;
	case STEREO_SGBM:
		(CPara2::getInstance()->GetDlgItem(IDC_EDIT_preFiltCap))->GetWindowText(temp);
		m_stereoMatcher.m_SGBM.preFilterCap = atoi(temp);
		(CPara2::getInstance()->GetDlgItem(IDC_EDIT_SADWinSiz))->GetWindowText(temp);
		m_stereoMatcher.m_SGBM.SADWindowSize = atoi(temp);
		m_stereoMatcher.m_SGBM.P1 = 48 * imgChannels * atoi(temp) * atoi(temp);//48??????!!!!!!?!?!?!?!!?!??
		m_stereoMatcher.m_SGBM.P2 = 48 * imgChannels * atoi(temp) * atoi(temp);
		(CPara2::getInstance()->GetDlgItem(IDC_EDIT_minDisp))->GetWindowText(temp);
		m_stereoMatcher.m_SGBM.minDisparity = atoi(temp);
		(CPara2::getInstance()->GetDlgItem(IDC_EDIT_maxDisp))->GetWindowText(temp);
		m_stereoMatcher.m_SGBM.numberOfDisparities = atoi(temp);
		(CPara2::getInstance()->GetDlgItem(IDC_EDIT_uniqRatio))->GetWindowText(temp);
		m_stereoMatcher.m_SGBM.uniquenessRatio = atoi(temp);
		(CPara2::getInstance()->GetDlgItem(IDC_EDIT_speckWinSiz))->GetWindowText(temp);
		m_stereoMatcher.m_SGBM.speckleWindowSize = atoi(temp);
		(CPara2::getInstance()->GetDlgItem(IDC_EDIT_speckRange))->GetWindowText(temp);
		m_stereoMatcher.m_SGBM.speckleRange = atoi(temp);
		(CPara2::getInstance()->GetDlgItem(IDC_EDIT_disp12MaxDiff))->GetWindowText(temp);
		m_stereoMatcher.m_SGBM.disp12MaxDiff = atoi(temp);
		m_stereoMatcher.m_SGBM.fullDP = true;
		break;
	case STEREO_VAR:
		(CPara2::getInstance()->GetDlgItem(IDC_EDIT_minDisp))->GetWindowText(temp);
		m_stereoMatcher.m_VAR.minDisp = atoi(temp);
		(CPara2::getInstance()->GetDlgItem(IDC_EDIT_maxDisp))->GetWindowText(temp);
		m_stereoMatcher.m_VAR.maxDisp = atoi(temp);
		(CPara2::getInstance()->GetDlgItem(IDC_EDIT_Levels))->GetWindowText(temp);
		m_stereoMatcher.m_VAR.levels = atoi(temp);// �������USE_AUTO_PARAMS,�㷨�����Զ����ø�ֵ
		(CPara2::getInstance()->GetDlgItem(IDC_EDIT_PyrScale))->GetWindowText(temp);
		m_stereoMatcher.m_VAR.pyrScale = atof(temp);// �������USE_AUTO_PARAMS,�㷨�����Զ����ø�ֵ
		(CPara2::getInstance()->GetDlgItem(IDC_EDIT_PolyN))->GetWindowText(temp);
		m_stereoMatcher.m_VAR.poly_n = atoi(temp);
		(CPara2::getInstance()->GetDlgItem(IDC_EDIT_PolySigma))->GetWindowText(temp);
		m_stereoMatcher.m_VAR.poly_sigma = atof(temp);
		(CPara2::getInstance()->GetDlgItem(IDC_EDIT_Fi))->GetWindowText(temp);
		m_stereoMatcher.m_VAR.fi = atof(temp);
		(CPara2::getInstance()->GetDlgItem(IDC_EDIT_Lambda))->GetWindowText(temp);
		m_stereoMatcher.m_VAR.lambda = atof(temp);//�������PENALIZATION_CHARBONNIER or PENALIZATION_PERONA_MALIK,������Ըò���
		break;
	default:
		break;
	}
}

// �Ӳ�ͼˢ�µ�ִ�к���
void CMainFrame::RefreshDisparityMap()
{
	int imgChannels = TargetImageL.channels();
	SetSolver(imgChannels);//ʶ�������õ�ƥ���㷨������������г�ʼ��
	bool MatchSucceed = false;
	switch (stereoMethod)//����Ӳ�
	{
	case STEREO_BM://ʹ��BM�����
		MatchSucceed = m_stereoMatcher.bmMatch(TargetImageL, TargetImageR, OriginalDisparity, ProcessedImageL, ProcessedImageR);
		break;
	case STEREO_SGBM://ʹ��SGBM�����
		MatchSucceed = m_stereoMatcher.sgbmMatch(TargetImageL, TargetImageR, OriginalDisparity, ProcessedImageL, ProcessedImageR);
		break;
	case STEREO_VAR://ʹ��VAR�����
		MatchSucceed = m_stereoMatcher.varMatch(TargetImageL, TargetImageR, OriginalDisparity, ProcessedImageL, ProcessedImageR);
		break;
	default:
		return;
	}
	if (MatchSucceed == false)//���ʧ��
	{
		return;
	}
	for (int j = 0; j < ProcessedImageL.rows; j += 32)//��ƽ����
	{
		line(ProcessedImageL, cvPoint(0, j), cvPoint(ProcessedImageL.cols, j), CV_RGB(0, 255, 0));
		line(ProcessedImageR, cvPoint(0, j), cvPoint(ProcessedImageR.cols, j), CV_RGB(0, 255, 0));
	}
	m_stereoMatcher.getDisparityImage(OriginalDisparity, DisparityMap, true);//�õ�α��
	//ͼ����ʾ
	F_ShowImage(ProcessedImageL, m_lfImage, IDC_PicLfCam);
	F_ShowImage(ProcessedImageR, m_riImage, IDC_PicRiCam);
	F_ShowImage(DisparityMap, m_disparity, IDC_PicSynImg);
	MatchDeepRebuildEnable = true;      // ����ƥ��->����ؽ�
	DoRefreshDisparityMapEnable = false;//ˢ����,����ˢ�°�ť
}


/*----------------------------------------------
* ���� : ��������ڵ�ָ����ǩҳ���ָ���ı���Ϣ,
*-----------------------------------------------
* ���� : CMainFrame::PutMessage
* ���� : public
* ���� : void
*
* ���� : wndID  			[in]	���λ��
* ���� : message			[in]	�������
*/
void CMainFrame::PutMessage(int wndID, LPCTSTR message)
{
	//LPCTSTR,ʹ��_T(String)ǿ��ת���õ�
	switch (wndID)
	{
	case CalibWnd:
		m_wndOutput.m_wndOutputCalib.AddString(message);
		break;
	case MatchWnd:
		m_wndOutput.m_wndOutputMatch.AddString(message);
		break;
	case RangeWnd:
		m_wndOutput.m_wndOutputRange.AddString(message);
		break;
	default:
		m_wndOutput.m_wndOutputCalib.AddString(_T("�����������,������ʾԤ�����Ϣ:\n"));
		m_wndOutput.m_wndOutputCalib.AddString(message);
		break;
	}
}

/*---------------------------------------------
* ���� : �������ļ��Ի���ѡ�񵥸������ļ�
*----------------------------------------------
* ���� : CMainFrame::DoSelectFiles
* ���� : private
* ���� : selectedFiles	ѡ����ļ���·������
*
* ���� : lpszDefExt			[in]	�ļ�Ĭ�ϸ�ʽ
* ���� : dwFlags			[in]	�Ի���ѡ��
* ���� : lpszFilter			[in]	�ļ���ʽ��������
* ���� : lpstrTitle			[in]	�Ի������
* ���� : lpstrInitialDir	[in]	�Ի���ĳ�ʼ·��
*/
vector<CStringA> CMainFrame::DoSelectFiles(LPCTSTR lpszDefExt, DWORD dwFlags, LPCTSTR lpszFilter, LPCTSTR lpstrTitle, LPCTSTR lpstrInitialDir)
{
	vector<CStringA> selectedFiles;
	POSITION filePosition;
	DWORD MAXFILE = 4000;
	TCHAR* pc = new TCHAR[MAXFILE];

	CFileDialog dlg(TRUE, lpszDefExt, NULL, dwFlags, lpszFilter, NULL);

	dlg.m_ofn.nMaxFile = MAXFILE;
	dlg.m_ofn.lpstrFile = pc;
	dlg.m_ofn.lpstrFile[0] = NULL;
	dlg.m_ofn.lpstrTitle = lpstrTitle;
	dlg.m_ofn.lpstrInitialDir = lpstrInitialDir;

	if (dlg.DoModal() == IDOK)
	{
		filePosition = dlg.GetStartPosition();
		while (filePosition != NULL)
		{
			CStringA path;
			path = dlg.GetNextPathName(filePosition);
			selectedFiles.push_back(path);
		}
	}

	delete[]pc;
	return selectedFiles;
}

/*---------------------------------------------
* ���� : ��ʾͼ��
*		 ��Ҫ���Ƶ�ͼ�� src ���Ƶ� des��Ȼ����Ƶ��ؼ���Ϊ ID �� Picture �ؼ�
*----------------------------------------------
* ���� : CMainFrame::F_ShowImage
* ���� : private
* ���� : void
*
* ���� : src	[in]	����ʾͼ��
* ���� : des	[in]	����ͼ��
* ���� : ID		[in]	ͼ�񴰿ڿؼ�ID
*/
void CMainFrame::F_ShowImage(Mat& src, Mat& des, UINT ID)
{
	if (src.empty())
	{
		return;
	}
	// ���㽫ͼƬ���ŵ� Image ��������ı�������
	double wRatio = des.cols / (double)src.cols;
	double hRatio = des.rows / (double)src.rows;
	double srcWH = src.cols / (double)src.rows;
	double desWH = des.cols / (double)des.rows;
	double scale = srcWH > desWH ? wRatio : hRatio;

	// ���ź�ͼƬ�Ŀ�͸�
	int nw = (int)(src.cols * scale);
	int nh = (int)(src.rows * scale);

	// Ϊ�˽����ź��ͼƬ���� des �����в�λ�������ͼƬ�� des ���Ͻǵ���������ֵ
	int tlx = (int)((des.cols - nw) / 2);
	int tly = (int)((des.rows - nh) / 2);

	// ���� des �� ROI ������������ͼƬ img
	Mat desRoi = des(Rect(tlx, tly, nw, nh));

	// ���src�ǵ�ͨ��ͼ����ת��Ϊ��ͨ��ͼ��
	if (src.channels() == 1)
	{
		Mat src_c;
		cvtColor(src, src_c, CV_GRAY2BGR);
		// ��ͼƬ src_t �������ţ������뵽 des ��
		resize(src_c, desRoi, desRoi.size());
	}
	else
	{
		// ��ͼƬ src �������ţ������뵽 des ��
		resize(src, desRoi, desRoi.size());//===================================
	}

	CDC* pDC = this->GetActiveView()->GetDlgItem(ID)->GetDC();		// �����ʾ�ؼ��� DC
	HDC hDC = pDC->GetSafeHdc();				// ��ȡ HDC(�豸���) �����л�ͼ����
	CRect rect;
	this->GetActiveView()->GetDlgItem(ID)->GetClientRect(&rect);	// ��ȡ�ؼ��ߴ�λ��
	CvvImage cimg;
	IplImage cpy = des;
	cimg.CopyOf(&cpy);						// ����ͼƬ
	cimg.DrawToHDC(hDC, &rect);				// ��ͼƬ���Ƶ���ʾ�ؼ���ָ��������
	ReleaseDC(pDC);
}

/*=====================���µ�һ��������������Ribbon�����ϵĿؼ�״̬====================*/
/*                                     ��־λ˵��:                                       
  bool CalibDefaultParamEnable     = false;      // �Ƿ����ñ궨->Ĭ�ϲ���             
  bool CalibDeleteParamEnable      = false;      // �Ƿ����ñ궨->�������             
  bool CalibFromImage              = false;      // �Ƿ����� �궨->��ͼƬ�궨          
  bool CalibFromCamera             = false;      // �Ƿ����� �궨->������궨          
  bool CalibFromFile               = false;      // �Ƿ����� �궨->���ļ��궨          
  bool StopCalibFromCamera         = false;      // �Ƿ����� �궨->ֹͣ�Ӿ�ͷ�궨      
  bool MatchDefaultParamEnable     = false;      // �Ƿ�����ƥ��->Ĭ�ϲ���             
  bool MatchDeleteParamEnable      = false;      // �Ƿ�����ƥ��->�������             
  bool MatchBngivedispEnable       = false;      // �Ƿ�����ƥ��->�����Ӳ�ͼ           
  bool MatchDeepRebuildEnable      = false;      // �Ƿ�����ƥ��->����ؽ�             
  bool RangeEnable                 = false;      // �Ƿ����ò����ع���               
  bool DoRefreshDisparityMapEnable = false;      // �Ƿ����� ƥ��->ˢ���Ӳ�ͼ          
  */
/*=======================================================================================*/
//ribbon->�궨->Ĭ�ϲ���
void CMainFrame::OnUpdateBnDefaultcamcalibparam(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ������������û����洦��������
	pCmdUI->Enable(CalibDefaultParamEnable);
}

//ribbon->�궨->��ղ���
void CMainFrame::OnUpdateBnDeletecamcalibparam(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ������������û����洦��������
	pCmdUI->Enable(CalibDeleteParamEnable);
}

//ribbon->�궨->��ͼƬ�궨
void CMainFrame::OnUpdateBndetectag(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ������������û����洦��������
	pCmdUI->Enable(CalibFromImage);
}

//ribbon->�궨->�Ӿ�ͷ�궨
void CMainFrame::OnUpdateTestcalib(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ������������û����洦��������
	pCmdUI->Enable(CalibFromCamera);
}

//ribbon->�궨->���ļ��궨
void CMainFrame::OnUpdateCalibfromyml(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ������������û����洦��������
	pCmdUI->Enable(CalibFromFile);
}

//ribbon->�궨->ֹͣ�Ӿ�ͷ�궨
void CMainFrame::OnUpdateStopcalib(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ������������û����洦��������
	pCmdUI->Enable(StopCalibFromCamera);
}

//ribbon->ƥ��->Ĭ�ϲ���
void CMainFrame::OnUpdateBnStereodefparam(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ������������û����洦��������
	pCmdUI->Enable(MatchDefaultParamEnable);
}

//ribbon->ƥ��->�������
void CMainFrame::OnUpdateBnStereodeleteparam(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ������������û����洦��������
	pCmdUI->Enable(MatchDeleteParamEnable);
}

//ribbon->ƥ��->�����Ӳ�ͼ
void CMainFrame::OnUpdateBngivedisp(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ������������û����洦��������
	pCmdUI->Enable(MatchBngivedispEnable);
}

//ribbon->ƥ��->ˢ��
void CMainFrame::OnUpdateDorefreshdisparitymap(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ������������û����洦��������
	pCmdUI->Enable(DoRefreshDisparityMapEnable);
}

//ribbon->ƥ��->����ؽ�
void CMainFrame::OnUpdateBnCompdisp(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ������������û����洦��������
	pCmdUI->Enable(MatchDeepRebuildEnable);
}

//ribbon->���->��궨��
void CMainFrame::OnUpdateBnMouseon(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ������������û����洦��������
	pCmdUI->Enable(RangeEnable);
}

/*======================================================================================*/
/*                          ����ΪHome�������ڲ��˵�����¼�����                        */
/*======================================================================================*/
//Home��->�¹���
void CMainFrame::OnNewproject()
{
	// TODO:  �ڴ���������������
	//1.���������Ի���,����������
	CNewProject NPDialog;
	if (NPDialog.DoModal()){//ģ̬�Ի������
		CString proName = NPDialog.ProjectName;//������Ķ���ȡ����
		if (proName.IsEmpty())//�ж��Ƿ�õ�����Ч�Ĺ�����
		{
			AfxMessageBox("��Ч�Ĺ�����!");
			return;//����������
		}
		else//��������Ч
		{

			char szPath[MAX_PATH];     //���ѡ���Ŀ¼·�� 
			CString AbsPath;
			ZeroMemory(szPath, sizeof(szPath));
			BROWSEINFO bi;
			bi.hwndOwner = m_hWnd;
			bi.pidlRoot = NULL;
			bi.pszDisplayName = szPath;
			CString temp;
			temp.Format(_T("%s%s%s"), "��ѡ���¹���:'", NPDialog.ProjectName, "'��Ŀ¼��");
			bi.lpszTitle = _T(temp);
			bi.ulFlags = 0;
			bi.lpfn = NULL;
			bi.lParam = 0;
			bi.iImage = 0;
			LPITEMIDLIST lp = SHBrowseForFolder(&bi);//����ѡ��Ŀ¼�Ի���
			if (lp && SHGetPathFromIDList(lp, szPath))//Ŀ¼��Ч,����Ŀ¼�ṹ,��ȫ�ֱ������и�ֵ
			{
				AbsPath.Format("%s%s", szPath, proName);//����ѡĿ¼�����������Թ������������ļ�����Ϊ�����̵ĸ�Ŀ¼ 
				CString CalibPicturePath;
				CString RangePicturePath;
				CString DataPath;
				CalibPicturePath.Format(_T("%s\\%s"), AbsPath, _T("�궨ͼƬ"));
				RangePicturePath.Format(_T("%s\\%s"), AbsPath, _T("����"));
				DataPath.Format(_T("%s\\%s"), AbsPath, _T("DATA"));
				//��ʼ��������Ŀ¼
				if (!PathIsDirectory(AbsPath))//ָ��Ŀ¼������
				{
					if (CreateDirectory(AbsPath, NULL) &&         /*��Ŀ¼*/
						CreateDirectory(CalibPicturePath, NULL) &&/*����궨ͼƬ*/
						CreateDirectory(RangePicturePath, NULL) &&/*������ͼƬ*/
						CreateDirectory(DataPath, NULL)           /*���������ļ�*/
						)//�������ж��Ƿ񴴽��ɹ�
					{
						//�����ɹ�,�Թ���Ŀ¼ȫ�ֱ������и�ֵ
						WorkPath = AbsPath;
						CalibDefaultParamEnable = true;      // ���ñ궨->Ĭ�ϲ���
						CalibDeleteParamEnable = true;      // ���ñ궨->�������
						CalibFromImage = true;              // ���� �궨->��ͼƬ�궨
						CalibFromCamera = true;             // ���� �궨->������궨
						CalibFromFile = true;               // ���� �궨->���ļ��궨
						PutMessage(CalibWnd, _T("����Ŀ¼����ɹ�!\n�Ѿ���ɳ�ʼ��!\n"));
					}
					else//����ʧ��
					{
						AfxMessageBox(_T("����ʧ��!"));
						return;
					}
				}
			}
			else
			{
				AfxMessageBox("��Ч�Ĺ���Ŀ¼!");
				return; //����������
			}

		}

	}

}

//Home��->�򿪹���
void CMainFrame::OnOpenproject()
{
	// TODO:  �ڴ���������������
	//1.���ļ�ѡ����
	//2.�ҵ�����Ŀ¼
	//3.��������Ҫ���ļ�
	//4.��ʾ��Ϣ
	char szPath[MAX_PATH];     //���ѡ���Ŀ¼·�� 
	CString AbsPath;
	ZeroMemory(szPath, sizeof(szPath));
	BROWSEINFO bi;
	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szPath;
	CString temp;
	temp.Format(_T("%s"), "��ѡ�񹤳�Ŀ¼��");
	bi.lpszTitle = _T(temp);
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);//����ѡ��Ŀ¼�Ի���
	if (lp && SHGetPathFromIDList(lp, szPath))//Ŀ¼��Ч
	{
		AbsPath.Format("%s", szPath);//��Ŀ¼,������,Ӧ���ڸ�Ŀ¼���潨��һ�����й����������ļ���
		if (!PathIsDirectory(AbsPath))//ָ��Ŀ¼������
		{
			AfxMessageBox(_T("��ѡĿ¼�����ڻ򲻿ɷ���!"));
			return;
		}
		else//��ѡ���Ŀ¼��Ч
		{
			WorkPath = AbsPath;//����Ŀ¼��ֵ
			CalibDefaultParamEnable = true;      // ���ñ궨->Ĭ�ϲ���
			CalibDeleteParamEnable = true;      // ���ñ궨->�������
			CalibFromImage = true;              // ���� �궨->��ͼƬ�궨
			CalibFromCamera = true;             // ���� �궨->������궨
			CalibFromFile = true;               // ���� �궨->���ļ��궨
			PutMessage(CalibWnd, _T("����Ŀ¼����ɹ�!\n�Ѿ���ɳ�ʼ��!\n"));
		}
	}
	else
	{
		AfxMessageBox("��Ч�Ĺ���Ŀ¼!");
		return; //����������
	}

}

//Home��->�򿪹���Ŀ¼
void CMainFrame::OnOpenpath()
{
	// TODO:  �ڴ���������������
	ShellExecute(NULL, NULL, WorkPath, NULL, NULL, SW_SHOW);
}

//Home->�رչ���
void CMainFrame::OnCloseproject()
{
	// TODO:  �ڴ���������������
	//�������еĹ���
	CalibDefaultParamEnable = false;      // ���ñ궨->Ĭ�ϲ���
	CalibDeleteParamEnable = false;       // ���ñ궨->�������
	CalibFromImage = false;               // ���ñ궨->��ͼƬ�궨
	CalibFromCamera = false;              // ���ñ궨->������궨
	CalibFromFile = false;                // ���ñ궨->���ļ��궨
	MatchDefaultParamEnable = false;      // ����ƥ��->Ĭ�ϲ���
	MatchDeleteParamEnable = false;       // ����ƥ��->�������
	MatchBngivedispEnable = false;        // ����ƥ��->�����Ӳ�ͼ
	MatchDeepRebuildEnable = false;       // ����ƥ��->����ؽ�
	RangeEnable = false;                  // ���ò����ع���        
	StopCalibFromCamera = false;          // ���� �궨->ֹͣ�Ӿ�ͷ�궨                     
	DoRefreshDisparityMapEnable = false;  // ���� ƥ��->ˢ���Ӳ�ͼ
}

//Home��->�����ĵ�
void CMainFrame::OnHelpdoc()
{
	// TODO:  �ڴ���������������
	//1.��RTFд�����ĵ�
	//2.�������
}

/*======================================================================================*/
/*                         ������Ribbon�������¼��������                               */
/*======================================================================================*/
//Ribbon->�궨->BOUGUET(��ѡ��)
void CMainFrame::OnRadBouguet()
{
	// TODO:  �ڴ���������������
	BOUGUET = !BOUGUET;
}
void CMainFrame::OnUpdateRadBouguet(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ������������û����洦��������
	pCmdUI->SetCheck(BOUGUET);
}

//Ribbon->�궨->HEARTLY(��ѡ��)
void CMainFrame::OnRadHartley()
{
	// TODO:  �ڴ���������������
	BOUGUET = !BOUGUET;
}
void CMainFrame::OnUpdateRadHartley(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ������������û����洦��������
	pCmdUI->SetCheck(!BOUGUET);
}

//Ribbon->�궨->Ĭ�ϲ���(����)
void CMainFrame::OnBnDefaultcamcalibparam()
{
	// TODO:  �ڴ���������������
	//1.��ѡ���ʼ��
	//LocalPicture = true; //�ӱ��ض�ȡͼƬ
	//ReadYML = false;     //�ӱ��ض�ȡ�ǵ���������
	BOUGUET = true;      //ʹ��BOUGUET����㷨

	//2.������Ӧ�Ľ��������ʼ��
	CPara1::getInstance()->GetDlgItem(IDC_BoardWidth)->SetWindowText("9");
	CPara1::getInstance()->GetDlgItem(IDC_BoardHeight)->SetWindowText("6");
	CPara1::getInstance()->GetDlgItem(IDC_nBoards)->SetWindowText("20");
	CPara1::getInstance()->GetDlgItem(IDC_SquareSize)->SetWindowText("25");
	CPara1::getInstance()->GetDlgItem(IDC_Alpha)->SetWindowText("-1");
	((CButton *)(CPara1::getInstance()->GetDlgItem(IDC_CHK_FPP)))->SetCheck(true);
	((CButton *)(CPara1::getInstance()->GetDlgItem(IDC_CHK_UIG)))->SetCheck(true);
	((CButton *)(CPara1::getInstance()->GetDlgItem(IDC_CHK_FAR)))->SetCheck(true);
	((CButton *)(CPara1::getInstance()->GetDlgItem(IDC_CHK_SFL)))->SetCheck(true);
	((CButton *)(CPara1::getInstance()->GetDlgItem(IDC_CHK_FI)))->SetCheck(false);
	return;
}

//Ribbon->�궨->�������(����)
void CMainFrame::OnBnDeletecamcalibparam()
{
	// TODO:  �ڴ���������������
	CPara1::getInstance()->GetDlgItem(IDC_BoardWidth)->SetWindowText("");
	CPara1::getInstance()->GetDlgItem(IDC_BoardHeight)->SetWindowText("");
	CPara1::getInstance()->GetDlgItem(IDC_nBoards)->SetWindowText("");
	CPara1::getInstance()->GetDlgItem(IDC_SquareSize)->SetWindowText("");
	CPara1::getInstance()->GetDlgItem(IDC_Alpha)->SetWindowText("");
	((CButton *)(CPara1::getInstance()->GetDlgItem(IDC_CHK_FPP)))->SetCheck(false);
	((CButton *)(CPara1::getInstance()->GetDlgItem(IDC_CHK_UIG)))->SetCheck(false);
	((CButton *)(CPara1::getInstance()->GetDlgItem(IDC_CHK_FAR)))->SetCheck(false);
	((CButton *)(CPara1::getInstance()->GetDlgItem(IDC_CHK_SFL)))->SetCheck(false);
	((CButton *)(CPara1::getInstance()->GetDlgItem(IDC_CHK_FI)))->SetCheck(false);
}

//Ribbon->�궨/����->��������ͷ(����)
void CMainFrame::OnBn1runcam()
{
	// TODO:  �ڴ���������������
	if (m_nImageWidth * m_nImageHeight * m_nImageChannels == 0)
	{
		AfxMessageBox(_T("��ѡ������ͷ����ķֱ��ʣ�"));
		return;
	}
	if (m_nCamCount > 0)
	{
		//�򿪵�һ������ͷ
		//if( ! lfCam.OpenCamera(m_riCamID, false, m_nImageWidth, m_nImageHeight) ) //����������ѡ�񴰿ڣ��ô����ƶ�ͼ���͸�
		if (!lfCam.open(m_lfCamID))
		{
			AfxMessageBox(_T("��������ͷʧ��."));
			return;
		}
		lfCam.set(CV_CAP_PROP_FRAME_WIDTH, m_nImageWidth);
		lfCam.set(CV_CAP_PROP_FRAME_HEIGHT, m_nImageHeight);
	}
	if (m_nCamCount > 1)
	{
		if (m_lfCamID == m_riCamID)
		{
			AfxMessageBox(_T("��������ͷ���豸��Ų�����ͬ��"));
			return;
		}
		//�򿪵ڶ�������ͷ
		//if( ! riCam.OpenCamera(m_lfCamID, false, m_nImageWidth, m_nImageHeight) ) 
		if (!riCam.open(m_riCamID))
		{
			AfxMessageBox(_T("��������ͷʧ��."));
			return;
		}
		riCam.set(CV_CAP_PROP_FRAME_WIDTH, m_nImageWidth);
		riCam.set(CV_CAP_PROP_FRAME_HEIGHT, m_nImageHeight);
	}
	/*
	// ʹ���ְ�ť��Ч
	GetDlgItem(IDC_BN2StopCam)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_BN_CompDisp)->EnableWindow(TRUE);
	// ʹ���ְ�ťʧЧ
	GetDlgItem(IDC_BN1RunCam)->EnableWindow(FALSE);
	GetDlgItem(IDC_CBN1CamList_L)->EnableWindow(FALSE);
	GetDlgItem(IDC_CBN1CamList_R)->EnableWindow(FALSE);
	GetDlgItem(IDC_CBN_Resolution)->EnableWindow(FALSE);
	*/


	// ��������ͷ����ʾʵʱ����
	DoShowOrigFrame();
}

//Ribbon->�궨/����->�ر����(����)
void CMainFrame::OnBn2stopcam()
{
	// TODO:  �ڴ���������������
	if (lfCam.isOpened())
	{
		//GetDlgItem(IDC_BN2StopCam)->EnableWindow(FALSE);
		KillTimer(1);

		// ��ͼ����������
		m_lfImage = Scalar(0);
		F_ShowImage(m_lfImage, m_lfImage, IDC_PicLfCam);
		lfCam.release();
		if (riCam.isOpened())
		{
			m_riImage = Scalar(0);
			F_ShowImage(m_riImage, m_riImage, IDC_PicRiCam);
			riCam.release();
		}

		// ʹ��������ͷ��ť������ͷѡ���б���Ч
		/*
		GetDlgItem(IDC_BN1RunCam)->EnableWindow(TRUE);
		GetDlgItem(IDC_CBN1CamList_L)->EnableWindow(TRUE);
		GetDlgItem(IDC_CBN1CamList_R)->EnableWindow(TRUE);
		GetDlgItem(IDC_CBN_Resolution)->EnableWindow(TRUE);
		GetDlgItem(IDC_BN_CompDisp)->EnableWindow(FALSE);
		*/
	}
	return;
}

//Ribbon->�궨/����->ˢ�����(����)
void CMainFrame::OnRefreshcam()
{
	// TODO:  �ڴ���������������
	RefalshCamera();
}

//Ribbon->�궨->��ͼƬ�궨(����)
void CMainFrame::OnBndetectag()
{
	// TODO:  �ڴ���������������
	/*���г�ʼ��*/
	int nFoundBoard = 0, nFrame = 0, nSucceedBoard = 0;
	vector<CStringA> img0Files, img1Files;
	const char* img0_file = NULL, *img1_file = NULL;
	cv::Mat frame0, frame1, img0, img1;
	cv::Size imageSize;
	UpdateData(TRUE);
	
	try
	{
		if (DoParseOptionsOfCameraCalib(optCalib) == false){//�Խ����ϵĲ������м��,�����ݵ���ͷ�궨�����ṹ����	
			AfxMessageBox(_T("��û�����ú���ı궨����!"));
			return;
		};
		optCalib.numberFrameSkip = 5;//��֡���ĳ�5
	
		img0Files = DoSelectFiles(
				_T("*.bmp"),
				OFN_ENABLESIZING | OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
				_T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
				_T("ѡ������ͼ�ļ�"),
				WorkPath);
		img1Files = DoSelectFiles(
				_T("*.bmp"),
				OFN_ENABLESIZING | OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
				_T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
				_T("ѡ������ͼ�ļ�"),
				WorkPath);

		if (img0Files.empty())	// �ж��Ƿ���ͼƬ
		{
			LPCTSTR errMsg = _T("û��ѡ����Ч��ͼ���ļ���������ѡ��!");
			throw errMsg;
		}

		img0_file = img0Files[0];
		img0 = cvLoadImage(img0_file);
		if (img0.rows>1000)
		{
			cv::resize(img0, img0, Size(img0.cols / 6, img0.rows / 6));
		}
		imageSize = img0.size();

		optCalib.numberBoards = MIN(optCalib.numberBoards, MIN(img0Files.size(), img1Files.size()));
			
		m_stereoCalibrator.initCornerData(optCalib.numberBoards, imageSize, optCalib.cornerSize, optCalib.squareSize, cornerDatas);

		// ��ʼ���ǵ�
		while (nFoundBoard < optCalib.numberBoards)
		{
			// ����ͼ��
			img0_file = img0Files[nFoundBoard];
			frame0 = cvLoadImage(img0_file);
			// ����ͼ��
			img0 = frame0.clone();
			if (img0.rows>1000)
			{
				cv::resize(img0, img0, Size(img0.cols / 6, img0.rows / 6));
			}
					
			img1_file = img1Files[nFoundBoard];
			frame1 = cvLoadImage(img1_file);
			img1 = frame1.clone();
			if (img1.rows>1000)
			{
				cv::resize(img1, img1, Size(img1.cols / 6, img1.rows / 6));
			}
				
			if (img0.rows>1000)//
			{
				cv::resize(img0, img0, Size(img0.cols / 6, img0.rows / 6));
				cv::resize(img1, img1, Size(img1.cols / 6, img1.rows / 6));
			}
			// ���ǵ�
			if (m_stereoCalibrator.detectCorners(img0, img1, cornerDatas, nFoundBoard))//������ɹ�
			{				 
				nSucceedBoard++;
				nFrame = 0;
				if (nFoundBoard > 0 && nFrame < 5)
				{
					//ʹͼ��ɫ������ͬʱ�ҵ����������̽ǵ�
					bitwise_not(img0, img0);
					bitwise_not(img1, img1);
				}
			}
			else//������ʧ��
			{
				PutMessage(CalibWnd, _T("��ͼƬ���ʧ��!\n"));
			}
			nFoundBoard++;//���ܳɹ�ʧ��,���ͼ����ȥ��
			// ��ʾ��⵽�Ľǵ�
			F_ShowImage(img0, m_lfImage, IDC_PicLfCam);
			F_ShowImage(img1, m_riImage, IDC_PicRiCam);
		} // --End "while(nFoundBoard < optCalib.numberBoards) "

		if (nSucceedBoard < 4)
		{
			PutMessage(CalibWnd, _T("���ɹ�������ͼ����С��4�����궨ʧ��!\n�����½��б궨����.\n"));
				return;
		}
		else if (nFoundBoard != optCalib.numberBoards)
		{
			optCalib.numberBoards = nFoundBoard;
			m_stereoCalibrator.resizeCornerData(optCalib.numberBoards, cornerDatas);
		}
		cornerDatas.nImages = nSucceedBoard;//��������ͼ������
		// ����ǵ���������
		CString FileTemp;
		FileTemp.Format(_T("%s\\%s"), WorkPath, _T("\\DATA\\CornerData.yml"));
		const char* cornerFile = FileTemp.GetBuffer(FileTemp.GetLength());
		m_stereoCalibrator.saveCornerData(cornerFile, cornerDatas);
		PutMessage(CalibWnd, _T("���̽ǵ������.\n"));
		// �ѻ�ȡ�ǵ���������
		
	}
	catch (LPCTSTR errMsg)
	{
		AfxMessageBox(errMsg);
		return;
	}
	catch (cv::Exception& e)
	{
		char err[2048];
		sprintf_s(err, "��������: %s", e.what());
		CString errInfo;
		errInfo = err;
		//AfxMessageBox(_T(errInfo));
		PutMessage(CalibWnd, _T(errInfo));
		return;
	}
	catch (...)
	{
		//AfxMessageBox(_T("����δ֪����"));
		PutMessage(CalibWnd, _T("����δ֪����"));
		return;
	}
	
	//stereoParams.flags = optCalib.flagStereoCalib;
	stereoParams.flags = 0;
	stereoParams.alpha = optCalib.alpha;
	m_stereoCalibrator.calibrateStereoCamera(cornerDatas, stereoParams, FALSE);

	// ����궨���
	double avgErr = 0;
	int x = m_stereoCalibrator.getStereoCalibrateError(cornerDatas, stereoParams, avgErr);
	char info[50];
	sprintf_s(info, "�궨��� = %7.4g", avgErr);
	CString ss;
	ss = info;
	PutMessage(CalibWnd, ss);//����궨���

	optCalib.rectifyMethod = (BOUGUET == true ? calib::RECTIFY_BOUGUET : calib::RECTIFY_HARTLEY);//ʶ����ѡ���ƥ���㷨

	// ִ��˫ĿУ��
	m_stereoCalibrator.rectifyStereoCamera(cornerDatas, stereoParams, remapMatrixs, optCalib.rectifyMethod);
	//�õ���ͶӰ�����У��ӳ�����
	PutMessage(CalibWnd, _T("�����˫ĿУ��.\n"));
	// ��������ͷ�������
	CString CalibParasFile;
	CalibParasFile.Format(_T("%s\\%s"), WorkPath, _T("\\DATA\\calib_paras.xml"));
	const char* calibparasfile = CalibParasFile.GetBuffer(CalibParasFile.GetLength());
	m_stereoCalibrator.saveCalibrationDatas(calibparasfile, optCalib.rectifyMethod, cornerDatas, stereoParams, remapMatrixs);
	PutMessage(CalibWnd, _T("�ѱ��涨������ļ�:\n"));
	if (avgErr > 5.0){
		AfxMessageBox(_T("�궨������!ǿ�ҽ��������궨��Դ�ĺ����Բ����е���������,���������ִ�в���,���ή�ͽ�������Ŷ�!"));
	}
	MatchDefaultParamEnable = true;      // ����ƥ��->Ĭ�ϲ���
	MatchDeleteParamEnable = true;      // ����ƥ��->�������
	MatchBngivedispEnable = true;      // ����ƥ��->�����Ӳ�ͼ
}

//Ribbon->�궨->������궨(����) 
void CMainFrame::OnTestcalib()
{
	// TODO:  �ڴ���������������
	//ȷ���������������ѡ��
	StopCalibFromCamera = true;      // ���� ֹͣ�궨�İ���
	KillTimer(1);
	if (DoParseOptionsOfCameraCalib(optCalib) == false){//�Խ����ϵĲ������м��,�����ݵ���ͷ�궨�����ṹ����	
		AfxMessageBox(_T("��û�����ú���ı궨����!"));
		return;
	};
	// ������ʹ�õ���ʱ����
	int nFoundBoard = 0, nFrame = 0;
	cv::Mat frame0, frame1, img0, img1;
	cv::Size imageSize;
	try
	{
		// ��ʼ���ǵ����ݼ�
		lfCam >> img0;
		imageSize = img0.size();
		m_stereoCalibrator.initCornerData(optCalib.numberBoards, 
										  imageSize, 
									      optCalib.cornerSize, 
										  optCalib.squareSize,
										  cornerDatas);

		// ��ʼ���ǵ�
		MSG msg;
		while (nFoundBoard < optCalib.numberBoards)//����Ѿ�������ͼ����Ŀû�дﵽԤ��ĵ�������
		{
			// ������Ӧ��;�˳��궨����Ϣ
			if (::PeekMessage(&msg, this->m_hWnd, 0, 0, PM_REMOVE)){
				if (msg.message == WM_QUIT){
					LPCTSTR errMsg = _T("�ֶ��˳�˫Ŀ�궨!");
					throw errMsg;
				}
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}

			// ������ͷ����ͼ��
			lfCam >> frame0;
			riCam >> frame1;

			if (frame0.empty() || frame1.empty())
				break;

			// ����ͼ��
			img0 = frame0.clone();
			img1 = frame1.clone();
			// ���ǵ�
			if (m_stereoCalibrator.detectCorners(img0, img1, cornerDatas, nFoundBoard))//�����һ��ͼ�ǵ���ɹ�
			{
				if (nFrame++ > optCalib.numberFrameSkip)//����ָ����֡�����Ŀ
				{
					//������ͼ
					CString ImgName;
					ImgName.Format(_T("%s\\�궨ͼƬ\\left%03d.jpg"), WorkPath, nFoundBoard);
					string imgnameL(ImgName.GetBuffer());
					imwrite(imgnameL, frame0);
					ImgName.Format(_T("%s\\�궨ͼƬ\\right%03d.jpg"), WorkPath, nFoundBoard);
					string imgnameR(ImgName.GetBuffer());
					imwrite(imgnameR, frame1);
					ImgName.ReleaseBuffer();
					
					nFoundBoard++;
					nFrame = 0;
				}

				if (nFoundBoard > 0 && nFrame < 5)
				{
					//ʹͼ��ɫ������ͬʱ�ҵ����������̽ǵ�
					bitwise_not(img0, img0);
					bitwise_not(img1, img1);
				}
			} // --End "if ( m_stereoCalibrator.detectCorners )"

			// ��ʾ��⵽�Ľǵ�
			F_ShowImage(img0, m_lfImage, IDC_PicLfCam);
			F_ShowImage(img1, m_riImage, IDC_PicRiCam);
		} // --End "while(nFoundBoard < optCalib.numberBoards) "

		if (nFoundBoard < 4)
		{
			LPCTSTR errMsg = _T("���ɹ�������ͼ����С��4�����˳�˫Ŀ�궨!");
			throw errMsg;
		}
		else if (nFoundBoard != optCalib.numberBoards)
		{
			optCalib.numberBoards = nFoundBoard;
			m_stereoCalibrator.resizeCornerData(optCalib.numberBoards, cornerDatas);
		}

		// ����ǵ���������
		CString CornerDataFile;
		CornerDataFile.Format(_T("%s\\%s"), WorkPath, _T("\\DATA\\CornerData.yml"));
		const char* cornerFile = CornerDataFile.GetBuffer(CornerDataFile.GetLength());
		m_stereoCalibrator.saveCornerData(cornerFile, cornerDatas);

		//AfxMessageBox(_T("���̽ǵ������"));
		PutMessage(CalibWnd, _T("���̽ǵ������\n"));//����궨���
		
	}
	catch (LPCTSTR errMsg)
	{
		AfxMessageBox(errMsg);
	}
	catch (cv::Exception& e)
	{
		char err[2048];
		sprintf_s(err, "��������: %s", e.what());
		CString errInfo(err);
		AfxMessageBox(errInfo);
	}
	catch (...)
	{
		AfxMessageBox(_T("����δ֪����"));
	}
	// �ѻ�ȡ�ǵ���������

	// ���ݱ궨����
	//stereoParams.cameraParams1.flags = optCalib.flagCameraCalib;
	//stereoParams.cameraParams2.flags = optCalib.flagCameraCalib;
	stereoParams.flags = optCalib.flagStereoCalib;
	stereoParams.alpha = optCalib.alpha;
	//ִ����������궨(���һ������������Ҫ�Ƚ��е�Ŀ�궨)
	m_stereoCalibrator.calibrateStereoCamera(cornerDatas, stereoParams, false);

	// ����궨���
	double avgErr = 0;
	m_stereoCalibrator.getStereoCalibrateError(cornerDatas, stereoParams, avgErr);
	char info[50];
	sprintf_s(info, "�궨��� = %7.4g\n", avgErr);
	CString ss;
	ss = info;
	PutMessage(CalibWnd, ss);//����궨���
	//AfxMessageBox(ss);

	// ִ�������������
	m_stereoCalibrator.rectifyStereoCamera(cornerDatas, stereoParams, remapMatrixs, optCalib.rectifyMethod);
	//AfxMessageBox(_T("�����˫ĿУ��"));
	PutMessage(CalibWnd, _T("�����˫ĿУ��\n"));//����궨���

	// ��������ͷ�������	
	CString CalibParasFile;
	CalibParasFile.Format(_T("%s\\%s"), WorkPath, _T("\\DATA\\calib_paras.xml"));
	const char* calibparasfile = CalibParasFile.GetBuffer(CalibParasFile.GetLength());
	m_stereoCalibrator.saveCalibrationDatas(calibparasfile, optCalib.rectifyMethod, cornerDatas, stereoParams, remapMatrixs);
	//AfxMessageBox(_T("�ѱ��涨�����"));
	PutMessage(CalibWnd, _T("�ѱ��涨�����\n"));//����궨���
		
	MSG msg;
	while (true)// ��ʾ�궨Ч��
	{
		// MFC ������Ϣ����
		if (::PeekMessage(&msg, this->m_hWnd, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		// ����ͼ��
		lfCam >> frame0;
		riCam >> frame1;
		if (frame0.empty() || frame1.empty())
			break;
		// ����ͼ��
		img0 = frame0.clone();
		img1 = frame1.clone();
		// У��ͼ��
		UpdateData(FALSE);
		m_stereoCalibrator.remapImage(img0, img1, img0, img1, remapMatrixs);
		// ��ʾУ��Ч��	
		// �����Ⱦ�����������ߣ��Աȶ� �ж�׼ ���
		for (int j = 0; j < img0.rows; j += 32)
		{
			line(img0, cvPoint(0, j), cvPoint(img0.cols, j), CV_RGB(0, 255, 0));
			line(img1, cvPoint(0, j), cvPoint(img1.cols, j), CV_RGB(0, 255, 0));
		}
		F_ShowImage(img0, m_lfImage, IDC_PicLfCam);
		F_ShowImage(img1, m_riImage, IDC_PicRiCam);
	}
	

	// �����˳���������갴ť

	//////////////////////////////////////////////////////////////////////////	
	if (lfCam.isOpened() || riCam.isOpened())
	{
		// ����������ָ�˫Ŀ���갴ť
		// �ָ�������ʾ
		DoShowOrigFrame();
	}
	return;
	MatchDefaultParamEnable = true;      // ����ƥ��->Ĭ�ϲ���
	MatchDeleteParamEnable = true;      // ����ƥ��->�������
	MatchBngivedispEnable = true;      // ����ƥ��->�����Ӳ�ͼ
}
 
//Ribbon->�궨->���ļ��궨(����)
void CMainFrame::OnCalibfromyml()
{
	// TODO:  �ڴ���������������
	if (!DoParseOptionsOfCameraCalib(optCalib)){// ��������궨����ز���
		AfxMessageBox(_T("��û�����ú���ı궨����!"));
		return;
	}
		
	try
	{
		vector<CStringA> YmlFilePath;
		YmlFilePath = DoSelectFiles(
			_T("*.yml"),
			OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
			_T("yml files (*.yml) |*.yml| All Files (*.*) |*.*||"),
			_T("ѡ��궨�������ļ�"),
			WorkPath
			);
		/*_T("*.bmp"),
				OFN_ENABLESIZING | OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
				_T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
				_T("ѡ������ͼ�ļ�"),*/
		if (YmlFilePath.empty())
		{
			AfxMessageBox(_T("û��ѡ����Ч�������ļ�!"));
			return;
		}
		const char* YMLFile = YmlFilePath[0];			// ��ȡyml�ļ�·��
		// �ӱ����ļ�����ǵ���������YML
		if (m_stereoCalibrator.loadCornerData(YMLFile, cornerDatas))
		{
			//AfxMessageBox(_T("�Ѷ�����������"));
			PutMessage(CalibWnd, _T("�Ѷ�����������"));
		}
		else
		{
			LPCTSTR errMsg = _T("�������ݶ���ʧ�ܣ�\n ��ȷ���ļ�����ȷ�Ի�ִ�����̽ǵ��⡣");
			throw errMsg;
		}
	}
	catch (LPCTSTR errMsg)
	{
		AfxMessageBox(errMsg);
		return;
	}
	catch (cv::Exception& e)
	{
		char err[2048];
		sprintf_s(err, "�ļ�����!������ϵͳ�ṩ�Ĵ�����Ϣ: %s", e.what());
		CString errInfo(err);
		AfxMessageBox(errInfo);
		return;
	}
	catch (...)
	{
		AfxMessageBox(_T("����δ֪����"));
		return;
	}
	// �ѻ�ȡ�ǵ���������

	// ��������ͷ�궨

	//stereoParams.flags = optCalib.flagStereoCalib;
	stereoParams.flags = 0;
	stereoParams.alpha = optCalib.alpha;
	m_stereoCalibrator.calibrateStereoCamera(cornerDatas, stereoParams, FALSE);

	// ����궨���
	double avgErr = 0;
	m_stereoCalibrator.getStereoCalibrateError(cornerDatas, stereoParams, avgErr);
	char info[50];
	sprintf_s(info, "�궨��� = %7.4g\n", avgErr);
	CString ss;
	ss = info;
	PutMessage(CalibWnd, ss);
	//AfxMessageBox(ss);

	// ִ��˫ĿУ��
	m_stereoCalibrator.rectifyStereoCamera(cornerDatas, stereoParams, remapMatrixs, optCalib.rectifyMethod);
	PutMessage(CalibWnd, _T("�����˫ĿУ��\n"));
	//AfxMessageBox(_T("�����˫ĿУ��"));

	// ���涨�����
	CString CalibParasFile;
	CalibParasFile.Format(_T("%s\\%s"), WorkPath, _T("\\DATA\\calib_paras.xml"));
	const char* calibparasFile = CalibParasFile.GetBuffer(CalibParasFile.GetLength());
	m_stereoCalibrator.saveCalibrationDatas(calibparasFile, optCalib.rectifyMethod, cornerDatas, stereoParams, remapMatrixs);

	//AfxMessageBox(_T("�ѱ��涨�����"));
	PutMessage(CalibWnd, _T("�ѱ��涨�����\n"));
	MatchDefaultParamEnable = true;      // ����ƥ��->Ĭ�ϲ���
	MatchDeleteParamEnable = true;      // ����ƥ��->�������
	MatchBngivedispEnable = true;      // ����ƥ��->�����Ӳ�ͼ
	return;
}

//Ribbon->�궨->ֹͣ�궨(����)
void CMainFrame::OnStopcalib()
{
	// TODO:  �ڴ���������������
	::PostMessage(this->m_hWnd, WM_QUIT, 0, 0);
	StopCalibFromCamera = false;      // �����������
}

//Ribbon->ƥ��->BM(��ѡ��)
void CMainFrame::OnRadBm()
{
	// TODO:  �ڴ���������������
	stereoMethod = STEREO_BM;
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_minDisp)->ShowWindow(SW_NORMAL);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_uniqRatio)->ShowWindow(SW_NORMAL);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_speckWinSiz)->ShowWindow(SW_NORMAL);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_maxDisp)->ShowWindow(SW_NORMAL);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_speckRange)->ShowWindow(SW_NORMAL);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_preFiltCap)->ShowWindow(SW_NORMAL);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_SADWinSiz)->ShowWindow(SW_NORMAL);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_textThres)->ShowWindow(SW_NORMAL);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_disp12MaxDiff)->ShowWindow(SW_NORMAL);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_Levels)->ShowWindow(SW_HIDE);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_PyrScale)->ShowWindow(SW_HIDE);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_PolyN)->ShowWindow(SW_HIDE);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_PolySigma)->ShowWindow(SW_HIDE);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_Fi)->ShowWindow(SW_HIDE);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_Lambda)->ShowWindow(SW_HIDE);
}
void CMainFrame::OnUpdateRadBm(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ������������û����洦��������
	pCmdUI->SetCheck(stereoMethod==STEREO_BM);
}

//Ribbon->ƥ��->SGBM(��ѡ��)
void CMainFrame::OnRadSgbm()
{
	// TODO:  �ڴ���������������
	stereoMethod = STEREO_SGBM;
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_minDisp)->ShowWindow(SW_NORMAL);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_uniqRatio)->ShowWindow(SW_NORMAL);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_speckWinSiz)->ShowWindow(SW_NORMAL);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_maxDisp)->ShowWindow(SW_NORMAL);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_speckRange)->ShowWindow(SW_NORMAL);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_preFiltCap)->ShowWindow(SW_NORMAL);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_SADWinSiz)->ShowWindow(SW_NORMAL);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_textThres)->ShowWindow(SW_HIDE);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_disp12MaxDiff)->ShowWindow(SW_NORMAL);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_Levels)->ShowWindow(SW_HIDE);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_PyrScale)->ShowWindow(SW_HIDE);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_PolyN)->ShowWindow(SW_HIDE);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_PolySigma)->ShowWindow(SW_HIDE);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_Fi)->ShowWindow(SW_HIDE);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_Lambda)->ShowWindow(SW_HIDE);
}
void CMainFrame::OnUpdateRadSgbm(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(stereoMethod == STEREO_SGBM);
}

//Ribbon->ƥ��->VAR(��ѡ��)
void CMainFrame::OnCheck2()
{
	stereoMethod = STEREO_VAR;
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_minDisp)->ShowWindow(SW_NORMAL);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_uniqRatio)->ShowWindow(SW_HIDE);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_speckWinSiz)->ShowWindow(SW_HIDE);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_maxDisp)->ShowWindow(SW_NORMAL);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_speckRange)->ShowWindow(SW_HIDE);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_preFiltCap)->ShowWindow(SW_HIDE);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_SADWinSiz)->ShowWindow(SW_HIDE);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_textThres)->ShowWindow(SW_HIDE);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_disp12MaxDiff)->ShowWindow(SW_HIDE);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_Levels)->ShowWindow(SW_NORMAL);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_PyrScale)->ShowWindow(SW_NORMAL);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_PolyN)->ShowWindow(SW_NORMAL);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_PolySigma)->ShowWindow(SW_NORMAL);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_Fi)->ShowWindow(SW_NORMAL);
	CPara2::getInstance()->GetDlgItem(IDC_SLIDER_Lambda)->ShowWindow(SW_NORMAL);
}
void CMainFrame::OnUpdateCheck2(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(stereoMethod == STEREO_VAR);
}

//Ribbon->ƥ��->Ĭ�ϲ���(����)
void CMainFrame::OnBnStereodefparam()
{
	// TODO:  �ڴ���������������
	switch (stereoMethod)//����Ӳ�
	{
	case STEREO_BM://ʹ��BM�����
		CPara2::getInstance()->GetDlgItem(IDC_EDIT_minDisp)->SetWindowText("0");
		CPara2::getInstance()->GetDlgItem(IDC_EDIT_maxDisp)->SetWindowText("144");
		CPara2::getInstance()->GetDlgItem(IDC_EDIT_SADWinSiz)->SetWindowText("51");
		CPara2::getInstance()->GetDlgItem(IDC_EDIT_textThres)->SetWindowText("10");
		CPara2::getInstance()->GetDlgItem(IDC_EDIT_disp12MaxDiff)->SetWindowText("1");
		CPara2::getInstance()->GetDlgItem(IDC_EDIT_preFiltCap)->SetWindowText("31");
		CPara2::getInstance()->GetDlgItem(IDC_EDIT_uniqRatio)->SetWindowText("25");
		CPara2::getInstance()->GetDlgItem(IDC_EDIT_speckRange)->SetWindowText("32");
		CPara2::getInstance()->GetDlgItem(IDC_EDIT_speckWinSiz)->SetWindowText("100");
		break;
	case STEREO_SGBM://ʹ��SGBM�����
		CPara2::getInstance()->GetDlgItem(IDC_EDIT_minDisp)->SetWindowText("0");
		CPara2::getInstance()->GetDlgItem(IDC_EDIT_maxDisp)->SetWindowText("144");
		CPara2::getInstance()->GetDlgItem(IDC_EDIT_SADWinSiz)->SetWindowText("25");
		CPara2::getInstance()->GetDlgItem(IDC_EDIT_textThres)->SetWindowText("10");//�����ǰ�������ֵ
		CPara2::getInstance()->GetDlgItem(IDC_EDIT_disp12MaxDiff)->SetWindowText("1");
		CPara2::getInstance()->GetDlgItem(IDC_EDIT_preFiltCap)->SetWindowText("63");
		CPara2::getInstance()->GetDlgItem(IDC_EDIT_uniqRatio)->SetWindowText("20");
		CPara2::getInstance()->GetDlgItem(IDC_EDIT_speckRange)->SetWindowText("32");
		CPara2::getInstance()->GetDlgItem(IDC_EDIT_speckWinSiz)->SetWindowText("100");
		break;
	case STEREO_VAR://ʹ��VAR�����
		CPara2::getInstance()->GetDlgItem(IDC_EDIT_minDisp)->SetWindowText("-64");
		CPara2::getInstance()->GetDlgItem(IDC_EDIT_maxDisp)->SetWindowText("64");
		(CPara2::getInstance()->GetDlgItem(IDC_EDIT_Levels))->SetWindowText("1");
		(CPara2::getInstance()->GetDlgItem(IDC_EDIT_PyrScale))->SetWindowText("01");
		(CPara2::getInstance()->GetDlgItem(IDC_EDIT_PolyN))->SetWindowText("5");
		(CPara2::getInstance()->GetDlgItem(IDC_EDIT_PolySigma))->SetWindowText("52.6");
		(CPara2::getInstance()->GetDlgItem(IDC_EDIT_Fi))->SetWindowText("90");
		(CPara2::getInstance()->GetDlgItem(IDC_EDIT_Lambda))->SetWindowText("0.82");
		break;
	default:
		break;
	}
}

//Ribbon->ƥ��->�������(����)
void CMainFrame::OnBnStereodeleteparam()
{
	// TODO:  �ڴ���������������
	CPara2::getInstance()->GetDlgItem(IDC_EDIT_minDisp)->SetWindowText("-64");
	CPara2::getInstance()->GetDlgItem(IDC_EDIT_maxDisp)->SetWindowText("16");
	CPara2::getInstance()->GetDlgItem(IDC_EDIT_SADWinSiz)->SetWindowText("5");
	CPara2::getInstance()->GetDlgItem(IDC_EDIT_textThres)->SetWindowText("0");//�����ǰ�������ֵ
	CPara2::getInstance()->GetDlgItem(IDC_EDIT_disp12MaxDiff)->SetWindowText("0");
	CPara2::getInstance()->GetDlgItem(IDC_EDIT_preFiltCap)->SetWindowText("0");
	CPara2::getInstance()->GetDlgItem(IDC_EDIT_uniqRatio)->SetWindowText("0");
	CPara2::getInstance()->GetDlgItem(IDC_EDIT_speckRange)->SetWindowText("0");
	CPara2::getInstance()->GetDlgItem(IDC_EDIT_speckWinSiz)->SetWindowText("0");
	(CPara2::getInstance()->GetDlgItem(IDC_EDIT_Levels))->SetWindowText("1");
	(CPara2::getInstance()->GetDlgItem(IDC_EDIT_PyrScale))->SetWindowText("0.1");
	(CPara2::getInstance()->GetDlgItem(IDC_EDIT_PolyN))->SetWindowText("1");
	(CPara2::getInstance()->GetDlgItem(IDC_EDIT_PolySigma))->SetWindowText("0");
	(CPara2::getInstance()->GetDlgItem(IDC_EDIT_Fi))->SetWindowText("0");
	(CPara2::getInstance()->GetDlgItem(IDC_EDIT_Lambda))->SetWindowText("0");
}

//Ribbon->ƥ��->ѡ���ļ�(����)
void CMainFrame::OnBngivedisp()
{
	// TODO:  �ڴ���������������
	CStringA xmlPath;			// �����������ļ�
	vector<CStringA> xmlFiles;
	vector<CStringA> imgFiles1; //������ͼ�ļ�·������
	vector<CStringA> imgFiles2;
	const char* img1_filename = NULL;
	const char* img2_filename = NULL;
	const char* xml_filename = NULL;
	
	LPCTSTR errMsg;
	try
	{
		// ѡ������ͼ
		imgFiles1 = DoSelectFiles(
				_T("*.bmp"),
				OFN_ENABLESIZING | OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
				_T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
				_T("ѡ������ͼͼ��"),
				WorkPath
				);
		// ѡ������ͼ
		imgFiles2 = DoSelectFiles(
				_T("*.bmp"),
				OFN_ENABLESIZING | OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
				_T("image files (*.bmp; *.png; *.jpg) |*.bmp; *.png; *.jpg; *.jpeg| All Files (*.*) |*.*||"),
				_T("ѡ������ͼͼ��"),
				WorkPath
				);
		if (imgFiles1.empty() || imgFiles2.empty())
		{
			errMsg = _T("û��ѡ����Ч��ͼ���ļ�!");
			throw errMsg;
		}
		// ѡ��ͷ�����ļ�
		xmlFiles = DoSelectFiles(
				_T("*.xml"),
				OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
				_T("XML/YML file (*.xml; *.yml) |*.xml; *.yml | All Files (*.*) |*.*||"),
				_T("ѡ������ͷ��������ļ�"),
				WorkPath
				);
		if (xmlFiles.empty())
		{
			errMsg = _T("û��ѡ����Ч������ͷ��������ļ�!");
			throw errMsg;
		}// ��ȡͼƬ
		img1_filename = imgFiles1[0];
		img2_filename = imgFiles2[0];
		TargetImageL = imread(img1_filename);
		TargetImageR = imread(img2_filename);

		if (TargetImageL.empty() || TargetImageR.empty()){
			AfxMessageBox(_T("ͼƬ�ļ�����!������."));
			return;
		}

			
		if (TargetImageL.rows>1000)
		{
			cv::resize(TargetImageL, TargetImageL, Size(TargetImageL.cols / 6, TargetImageL.rows / 6));
			cv::resize(TargetImageR, TargetImageR, Size(TargetImageL.cols / 6, TargetImageL.rows / 6));
		}
		// ��ȡxml�ļ�·��
		xmlPath = xmlFiles[0];			
		xml_filename = xmlPath;
		// ��������ͷ�������
		switch (m_stereoMatcher.init(TargetImageL.cols, TargetImageL.rows, xml_filename))
		{
		case 0:
		case -99:
			errMsg = _T("��ȡ����ͷ��������ļ�ʧ�ܣ�������ѡ��!");
			throw errMsg;
		case -1:
			errMsg = _T("��ѡ��Ĳ�����ȷ�ı궨�����ļ�������ѡ���ͼƬ���Բ�ͬ�����!");
			throw errMsg;
			break;
		}
	}
	catch (LPCTSTR ErrMsg)
	{
		AfxMessageBox(ErrMsg);
		return;
	}
	catch (cv::Exception& e)
	{
		char err[2048];
		sprintf_s(err, "��������: %s", e.what());
		CString errInfo;
		errInfo = err;
		AfxMessageBox(errInfo);
		return;
	}
	catch (...)
	{
		AfxMessageBox(_T("����δ֪����"));
		return;
	}
	FileSelected = true;//�Ѿ�ѡ�����ļ�
	//ֱ��ִ��һ��ˢ��
	RefreshDisparityMap();
}

//Ribbon->ƥ��->ˢ��(����)
void CMainFrame::OnDorefreshdisparitymap()
{
	// TODO:  �ڴ���������������
	RefreshDisparityMap();
}

//Ribbon->ƥ��->����ؽ�(����)
void CMainFrame::OnBnCompdisp()
{
	CString FileTemp;
	FileTemp.Format(_T("%s\\%s"), WorkPath, _T("\\DATA\\pointcloud.xml"));
	const char* CloudsFile = FileTemp.GetBuffer(FileTemp.GetLength());
	// TODO:  �ڴ���������������
	m_stereoMatcher.getPointClouds(OriginalDisparity, pointCloud, CloudsFile);//������ά���Ʋ�����Y�ᷴת
	vector<PointCloudAnalyzer::ObjectInfo> objectInfos;
	PointCloudAnalyzer pointCloudAnalyzer;
	if (pointCloudAnalyzer.detectNearObject(DisparityMap, pointCloud, objectInfos)==0)
	{
		return;//��������ʧ��,�����׳��쳣��Ϣ,����ֱ���˳�
	}
	pointCloudAnalyzer.showObjectInfo(objectInfos, ProcessedImageL);//������ͼ�����������ʶ��Ŀ�
	m_ObjectDistance = objectInfos[0].distance; 
	m_ObjectDistance = (int)(m_ObjectDistance * 10000) / 10000.;
	m_ObjectDistance = -16 * m_ObjectDistance;//���16���Ǿ��ȵĺ�������
	//�������д�¾�����ֵ
	CString DIS;
	DIS.Format("%f", m_ObjectDistance);
	CPara3::getInstance()->GetDlgItem(IDC_e7ObjDist)->SetWindowText(DIS);
	F_ShowImage(ProcessedImageL, m_lfImage, IDC_PicLfCam);
	F_ShowImage(ProcessedImageR, m_riImage, IDC_PicRiCam);
	F_ShowImage(DisparityMap, m_disparity, IDC_PicSynImg);
	RangeEnable = true;      // ���ò����ع���
}

//Ribbon->���->�������(��ѡ��)
void CMainFrame::OnChkGetdepth()
{
	// TODO:  �ڴ���������������
	rangingModel = GetDepth;
}
void CMainFrame::OnUpdateChkGetdepth(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(rangingModel == GetDepth);
}

//Ribbon->���->�������(��ѡ��)
void CMainFrame::OnChkGetlength()
{
	rangingModel = GetLength;
}
void CMainFrame::OnUpdateChkGetlength(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(rangingModel == GetLength);
}



//Ribbon->����->����(����)
void CMainFrame::OnPhotograph()
{
	// TODO:  �ڴ���������������
	KillTimer(1);
	cv::Mat frame0, frame1, img0, img1;

	// ������ͷ����ͼ��
	lfCam >> frame0;
	riCam >> frame1;

	if (frame0.empty() && frame1.empty()){
		DoShowOrigFrame();//����Ϊ��,û�б�Ҫ����,ֱ�ӷ��ؼ���
		return;
	}
		
	//����ͼƬ			
	CString ImgName;
	CString TIME;
	CTime tm;

	tm = CTime::GetCurrentTime();//��ȡϵͳʱ�� ��
	TIME = tm.Format("%m%d%H%M%S");
	if (!frame0.empty()){
		ImgName.Format(_T("%s\\����\\%sL.jpg"), WorkPath, TIME);
		string imgnameL(ImgName.GetBuffer());
		imwrite(imgnameL, frame0);
	}
	
	if (!frame1.empty()){
		ImgName.Format(_T("%s\\����\\%sR.jpg"), WorkPath, TIME);
		string imgnameR(ImgName.GetBuffer());
		imwrite(imgnameR, frame1);
	}
	ImgName.ReleaseBuffer();
	TIME.ReleaseBuffer();
	//ʹͼ��ɫ
	if (!frame0.empty()){
		bitwise_not(frame0, frame0);
	}
	if (!frame1.empty()){
		bitwise_not(frame1, frame1);
	}
	
	//if (lfCam.isOpened() || riCam.isOpened())
	//{
		DoShowOrigFrame();
	//}
	return;
}



//Ribbon->���->��궨��(����)
void CMainFrame::OnBnMouseon()
{
	// ׼������
	int flag;                              
	
	moupoint.x = 5;
	moupoint.y = 5;

	vector<cv::Mat> xyzSet;
	split(pointCloud, xyzSet);
	xyzSet[2].copyTo(depth);

	switch (rangingModel)//���ֲ�෽���ֿ�
	{
	case GetDepth:
		cv::namedWindow("��������-��ESC�˳�", 1);
		flag = 1;
		while (flag)
		{
			imshow("��������-��ESC�˳�", DisparityMap);
			cv::setMouseCallback("��������-��ESC�˳�", On_Mouse, 0);
			if (waitKey(100) == 27){//27��ESC������ASCNII��
				break;//break-while
			}	
		}
		destroyWindow("��������-��ESC�˳�");
		break;//break-case
	case GetLength:
		DisparityMap2 = DisparityMap.clone();//�����Ӳ�ͼ����
		cv::namedWindow("��������-��ESC�˳�", 1);
		while (true)
		{
			imshow("��������-��ESC�˳�", DisparityMap2);
			cv::setMouseCallback("��������-��ESC�˳�", On_Mouse, 0);
			if (waitKey(100) == 27){
				break;//break-while
			}
		}
		destroyWindow("��������-��ESC�˳�");
		break;//break-case

		//��������ģʽ��Ҫ��һЩ���ƹ���Ҫ��,����Ϊ�����Ч��,����ʹ�������ѭ������
		//1 ��һ���Ӳ�ͼ�ĸ���,�������Ӧ����ȫ�ֱ���
		//2 ��ʾ�Ǹ�����
		//3 ����ֻ��Ҫѭ��������
		//4 ��Ӧ��������ĺ�����,Ҫ������:
			//4-1 ȡ��һ����,���Ӳ�ͼԭ�������Ѿ�������ĸ���,��ȫ�ָ������滮��,ÿ�ε��,������궼Ҫ���
			//4-2 ȥ�ڶ�����,��ȫ�ָ����ϻ���,����������ľ���,�����������������봰��
		break;
	default:
		break;
	}
	
	
}

// ��궨�㺯�� 
void CMainFrame::On_Mouse(int event, int x, int y, int flags, void *)
{
	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN:
	{
		moupoint.x = x;
		moupoint.y = y;
		AfxGetApp()->GetMainWnd()->SendMessage(WM_USER_XYZAnalyse, 0, 0);
	}
		break;
	case CV_EVENT_LBUTTONUP:
	{
							   
	}
		break;
	}
}

//���յ����������Ϣ,����Ϣ��On_Mouse��������,�����˺�����ʱ��,mousepoint�Ѿ���ȡ
afx_msg LRESULT CMainFrame::OnXYZAnalyse(WPARAM wParam, LPARAM lParam)
{
	//׼����ʱ����
	CString DIS;
	Point3f WorldPoint;
	Point3f WorldPoint2;
	float distance;//���ڴ洢����֮��ľ���
	
	if (moupoint.x > 20)//��ǰ��
	{
		m_ObjectDistance = depth.at<float>(moupoint);
		//	m_ObjectDistance=depth.ptr<float>(moupoint.x)[moupoint.y];
		m_ObjectDistance = -16 * m_ObjectDistance;
		if (m_ObjectDistance > 0)
		{
			//��������ģʽ,�����������궼Ҫ���
			DIS.Format("%d", moupoint.x);
			CPara3::getInstance()->GetDlgItem(IDC_EDIT_ImageX)->SetWindowText(DIS);//ͼƬ����X
			DIS.Format("%d", moupoint.y);
			CPara3::getInstance()->GetDlgItem(IDC_EDIT_ImageY)->SetWindowText(DIS);//ͼƬ����Y
			WorldPoint = (pointCloud.at<Vec3f>(moupoint));//���������������,�ӵ�����ȡ������Ӧ�ĵ����������
			DIS.Format("%.2f", 16 * WorldPoint.x);
			CPara3::getInstance()->GetDlgItem(IDC_EDIT_WorldX)->SetWindowText(DIS);//��������X
			DIS.Format("%.2f", 16 * WorldPoint.y);
			CPara3::getInstance()->GetDlgItem(IDC_EDIT_WorldY)->SetWindowText(DIS);//��������Y
			DIS.Format("%.2f", -16 * WorldPoint.z);
			CPara3::getInstance()->GetDlgItem(IDC_EDIT_WorldZ)->SetWindowText(DIS);//��������Z
			//���������ַ����ķֱ���
			switch (rangingModel)
			{
			case GetDepth:
				DIS.Format("%.3f", m_ObjectDistance);
				CPara3::getInstance()->GetDlgItem(IDC_e7ObjDist)->SetWindowText(DIS);//Ŀ�����(����ģʽ��,��ֵΪZ����)
				break;
			case GetLength:
				//������
				//�ǲ��ǵ�һ����-��ֵ��������Ϊtrue
				IsSecondPoint = !IsSecondPoint;

				if (IsSecondPoint == false){//����ǵ�һ����
					// ����Ӳ�ͼ����
					DisparityMap2 = DisparityMap.clone();//����Ӳ�ͼ�Ļ���
					// ��ս����ϵľ���ֵ
					CPara3::getInstance()->GetDlgItem(IDC_e7ObjDist)->SetWindowText(_T(""));//���Ŀ�����
					// ����
					line(DisparityMap2, cvPoint(moupoint.x, 0), cvPoint(moupoint.x, DisparityMap2.rows), CV_RGB(255, 255, 255));//����
					line(DisparityMap2, cvPoint(0, moupoint.y), cvPoint(DisparityMap2.cols, moupoint.y), CV_RGB(255, 255, 255));//����
					// ����������ͼ��ռ�����
					moupoint2.x = moupoint.x;
					moupoint2.y = moupoint.y;
				}
				else//����ǵڶ�����
				{
					//����
					line(DisparityMap2, cvPoint(moupoint.x, 0), cvPoint(moupoint.x, DisparityMap2.rows), CV_RGB(255, 255, 255));//����
					line(DisparityMap2, cvPoint(0, moupoint.y), cvPoint(DisparityMap2.cols, moupoint.y), CV_RGB(255, 255, 255));//����
					//��������
					line(DisparityMap2, cvPoint(moupoint2.x, moupoint2.y), cvPoint(moupoint.x, moupoint.y), CV_RGB(255, 255, 255));//��������
					//������������������
					WorldPoint = (pointCloud.at<Vec3f>(moupoint));
					WorldPoint2 = (pointCloud.at<Vec3f>(moupoint2));
					//�������
					distance = sqrt((256 * (WorldPoint.x - WorldPoint2.x)*(WorldPoint.x - WorldPoint2.x)) +
						(256 * (WorldPoint.y - WorldPoint2.y)*(WorldPoint.y - WorldPoint2.y)) +
						(256 * (WorldPoint.z - WorldPoint2.z)*(WorldPoint.z - WorldPoint2.z)));

					DIS.Format("%.3f", distance);
					CPara3::getInstance()->GetDlgItem(IDC_e7ObjDist)->SetWindowText(DIS);
					//end of if (IsSecondPoint == false)

					break;
			default:
				break;
				}//end of switch
			}//end of if (m_ObjectDistance>0)
		}//end of if (moupoint.x>20)//��ǰ��
	}
	return 0;
}









