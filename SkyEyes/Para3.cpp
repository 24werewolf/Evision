// Para3.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SkyEyes.h"
#include "Para3.h"
#include "afxdialogex.h"


// CPara3 �Ի���

IMPLEMENT_DYNAMIC(CPara3, CDialog)
CPara3* CPara3::getInstance(){//ȡ��ʵ��
	if (CP3_instance == 0)
	{
		CP3_instance = new CPara3();
	}
	return CP3_instance;
}
CPara3::CPara3(CWnd* pParent /*=NULL*/)
	: CDialog(CPara3::IDD, pParent)
{

}

CPara3::~CPara3()
{
}

void CPara3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPara3, CDialog)
END_MESSAGE_MAP()


// CPara3 ��Ϣ�������
