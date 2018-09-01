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

// EvisionLegacyView.cpp : CEvisionLegacyView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "EvisionLegacy.h"
#endif

#include "EvisionLegacyDoc.h"
#include "EvisionLegacyView.h"
#include "OutputWnd.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEvisionLegacyView

IMPLEMENT_DYNCREATE(CEvisionLegacyView, CFormView)

BEGIN_MESSAGE_MAP(CEvisionLegacyView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &CEvisionLegacyView::OnTcnSelchangeTab)
//	ON_WM_PAINT()
//	ON_WM_CREATE()
END_MESSAGE_MAP()

// CEvisionLegacyView ����/����

CEvisionLegacyView::CEvisionLegacyView()
	: CFormView(CEvisionLegacyView::IDD)
{
	// TODO:  �ڴ˴���ӹ������
	m_para1 = CPara1::getInstance();
	m_para2 = CPara2::getInstance();
	m_para3 = CPara3::getInstance();
	m_para4 = CPara4::getInstance();
}

CEvisionLegacyView::~CEvisionLegacyView()
{
}

void CEvisionLegacyView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB, m_tab);
}

BOOL CEvisionLegacyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CFormView::PreCreateWindow(cs);
}

void CEvisionLegacyView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	//����������������TabControl��������
	//1.������ǩҳ
	m_tab.InsertItem(0, _T("�궨"));      //���ѡ� 
	m_tab.InsertItem(1, _T("����ƥ��"));  
	m_tab.InsertItem(2, _T("���"));
	m_tab.InsertItem(3, _T("����"));
	//2.�Ӵ��ڰ�
	m_para1->Create(IDD_PARA1, GetDlgItem(IDC_TAB));
	m_para2->Create(IDD_PARA2, GetDlgItem(IDC_TAB));
	m_para3->Create(IDD_PARA3, GetDlgItem(IDC_TAB));
	m_para4->Create(IDD_PARA4, GetDlgItem(IDC_TAB));
	//3.������С
	CRect rs;                //���IDC_TABTEST�ͻ�����С
	m_tab.GetClientRect(&rs);//�����ӶԻ����ڸ������е�λ�� 
    rs.top += 22;
	rs.bottom -= 2;
	rs.left += 1;
	rs.right -= 3;           //�����ӶԻ���ߴ粢�ƶ���ָ��λ�� 
	m_para1->MoveWindow(&rs);
	m_para2->MoveWindow(&rs);
	m_para3->MoveWindow(&rs);
	m_para4->MoveWindow(&rs);
	//4.��ʾ
	m_para1->ShowWindow(true);
	m_para2->ShowWindow(false);
	m_para3->ShowWindow(false);
	m_para4->ShowWindow(false);
	//5.Ĭ��ѡ��
	m_tab.SetCurSel(0);
	//ע��,��ʱ,�������Ӵ�����ʵ�ǵ���һ���,������Ҫʹ�ü���������������ʾ������һ��,��ʵ���л�ҳ��Ч��
}

void CEvisionLegacyView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CEvisionLegacyView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CEvisionLegacyView ���

#ifdef _DEBUG
void CEvisionLegacyView::AssertValid() const
{
	CFormView::AssertValid();
}

void CEvisionLegacyView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CEvisionLegacyDoc* CEvisionLegacyView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEvisionLegacyDoc)));
	return (CEvisionLegacyDoc*)m_pDocument;
}
#endif //_DEBUG


// CEvisionLegacyView ��Ϣ�������


void CEvisionLegacyView::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int CurSel = m_tab.GetCurSel();
	CString str;
	switch (CurSel)
	{
		case 0:
		    m_para1->ShowWindow(true);
		    m_para2->ShowWindow(false);
		    m_para3->ShowWindow(false);
	    	m_para4->ShowWindow(false);
			break;
		case 1:
		         m_para1->ShowWindow(false);
		         m_para2->ShowWindow(true);
				 m_para3->ShowWindow(false);
				 m_para4->ShowWindow(false);
			break;
		case 2:
		         m_para1->ShowWindow(false);
		         m_para2->ShowWindow(false);
				 m_para3->ShowWindow(true);
				 m_para4->ShowWindow(false);
			 break;
		case 3:
			m_para1->ShowWindow(false);
			m_para2->ShowWindow(false);
			m_para3->ShowWindow(false);
			m_para4->ShowWindow(true);
			break;
		default:
				;
    }

	*pResult = 0;
}