// Para1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EvisionLegacy.h"
#include "Para1.h"
#include "afxdialogex.h"


// CPara1 �Ի��� �궨�ؼ����

IMPLEMENT_DYNAMIC(CPara1, CDialog)
CPara1* CPara1::getInstance(){//ȡ��ʵ��
	if (CP1_instance==0)
	{
		CP1_instance = new CPara1();
	}
	return CP1_instance;
}
CPara1::CPara1(CWnd* pParent /*=NULL*/)
	: CDialog(CPara1::IDD, pParent)
{

}

CPara1::~CPara1()
{
}

void CPara1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CP1CamList_L, m_CP1CamList_L);
	DDX_Control(pDX, IDC_CP1CamList_R, m_CP1CamList_R);
	DDX_Control(pDX, IDC_CP1Resolution, m_CP1Resolution);
}


BEGIN_MESSAGE_MAP(CPara1, CDialog)
	ON_EN_CHANGE(IDC_BoardWidth, &CPara1::OnChangeBoardwidth)
	ON_EN_CHANGE(IDC_BoardHeight, &CPara1::OnChangeBoardheight)
	ON_EN_CHANGE(IDC_SquareSize, &CPara1::OnChangeSquaresize)
	ON_CBN_SELCHANGE(IDC_CP1CamList_L, &CPara1::OnCbnSelchangeCp1camlistL)
	ON_CBN_SELCHANGE(IDC_CP1CamList_R, &CPara1::OnCbnSelchangeCp1camlistR)
	ON_CBN_SELCHANGE(IDC_CP1Resolution, &CPara1::OnCbnSelchangeCp1resolution)
END_MESSAGE_MAP()


// CPara1 ��Ϣ�������


void CPara1::OnChangeBoardwidth()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//ԭ�����в�û�и���ʵ��.��ʹ΢����ע
}


void CPara1::OnChangeBoardheight()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//ԭ�����в�û�и���ʵ��.��ʹ΢����ע
}


void CPara1::OnChangeSquaresize()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//ԭ�����в�û�и���ʵ��.��ʹ΢����ע
}



//������ͷ�����б�
void CPara1::OnCbnSelchangeCp1camlistL()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//������ͷ���޸�,�����Զ�����Ϣ,֪ͨ�������ܴ�����¼�
	//���������յ������Ϣ��ʱ��,Ӧ��ʹ�õ���ģʽ,ʹ�ñ���ľ�ָ̬����������б��õ�������
	AfxGetMainWnd()->SendMessage(WM_USER_CPara4ChangeCameraL, 1, 0);
}

//������ͷ�����б�
void CPara1::OnCbnSelchangeCp1camlistR()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//������ͷ���޸�,�����Զ�����Ϣ,֪ͨ�������ܴ�����¼�
	//���������յ������Ϣ��ʱ��,Ӧ��ʹ�õ���ģʽ,ʹ�ñ���ľ�ָ̬����������б��õ�������
	AfxGetMainWnd()->SendMessage(WM_USER_CPara4ChangeCameraR, 1, 0);
}

//�ֱ��������б�
void CPara1::OnCbnSelchangeCp1resolution()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//�ֱ��ʱ�����,Ӧ�÷����Զ�����Ϣ,֪ͨ����������¼�
	//�ڴ���ĵ�ʱ��,Ӧ��ʹ�õ���ģʽ,ʹ��CPara1/4�ľ�ָ̬����������б��,�õ�������
	AfxGetMainWnd()->SendMessage(WM_USER_ChangeDPI, 1, 0);
}
