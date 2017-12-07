// Para4.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SkyEyes.h"
#include "Para4.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// CPara4 �Ի��� �����ؼ����

IMPLEMENT_DYNAMIC(CPara4, CDialogEx)

CPara4* CPara4::getInstance(){//ȡ��ʵ��
	if (CP4_instance == 0)
	{
		CP4_instance = new CPara4();
	}
	return CP4_instance;
}

CPara4::CPara4(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPara4::IDD, pParent)
{

}

CPara4::~CPara4()
{
}

void CPara4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CP4CamList_L, m_CP4CamList_L);
	DDX_Control(pDX, IDC_CP4CamList_R, m_CP4CamList_R);
	DDX_Control(pDX, IDC_CP4MethodList, m_CP4MethodList);
	DDX_Control(pDX, IDC_CP4Resolution, m_CP4Resolution);
}


BEGIN_MESSAGE_MAP(CPara4, CDialogEx)
	ON_CBN_SELCHANGE(IDC_CP4Resolution, &CPara4::OnSelchangeCp4resolution)
	ON_CBN_SELCHANGE(IDC_CP4MethodList, &CPara4::OnCbnSelchangeCbn2methodlist)
	ON_CBN_SELCHANGE(IDC_CP4CamList_L, &CPara4::OnCbnSelchangeCp4camlistL)
	ON_CBN_SELCHANGE(IDC_CP4CamList_R, &CPara4::OnCbnSelchangeCp4camlistR)
END_MESSAGE_MAP()


// CPara4 ��Ϣ�������


void CPara4::OnSelchangeCp4resolution()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//�ֱ��ʱ�����,Ӧ�÷����Զ�����Ϣ,֪ͨ����������¼�
	//�ڴ���ĵ�ʱ��,Ӧ��ʹ�õ���ģʽ,ʹ��CPara1/4�ľ�ָ̬����������б��,�õ�������
	AfxGetMainWnd()->SendMessage(WM_USER_ChangeDPI, 4, 0);
}


void CPara4::OnCbnSelchangeCbn2methodlist()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//֡���������޸�,�����Զ�����Ϣ,֪ͨ�������ܴ�����¼�
	//���������յ������Ϣ��ʱ��,Ӧ��ʹ�õ���ģʽ,ʹ�ñ���ľ�ָ̬����������б��õ�������
	AfxGetMainWnd()->SendMessage(WM_USER_ChangeFrameProcMethod, 4, 0);
}


void CPara4::OnCbnSelchangeCp4camlistL()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//������ͷ���޸�,�����Զ�����Ϣ,֪ͨ�������ܴ�����¼�
	//���������յ������Ϣ��ʱ��,Ӧ��ʹ�õ���ģʽ,ʹ�ñ���ľ�ָ̬����������б��õ�������
	AfxGetMainWnd()->SendMessage(WM_USER_CPara4ChangeCameraL, 4, 0);
}


void CPara4::OnCbnSelchangeCp4camlistR()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//������ͷ���޸�,�����Զ�����Ϣ,֪ͨ�������ܴ�����¼�
	//���������յ������Ϣ��ʱ��,Ӧ��ʹ�õ���ģʽ,ʹ�ñ���ľ�ָ̬����������б��õ�������
	AfxGetMainWnd()->SendMessage(WM_USER_CPara4ChangeCameraR, 4, 0);
}
