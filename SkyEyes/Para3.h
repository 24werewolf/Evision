#pragma once



// CPara3 �Ի���

class CPara3 : public CDialog
{
	DECLARE_DYNAMIC(CPara3)

public:
	static CPara3* getInstance();//ȡ��ʵ��
	virtual ~CPara3();

// �Ի�������
	enum { IDD = IDD_PARA3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	CPara3(CWnd* pParent = NULL);   // ��׼���캯��
	DECLARE_MESSAGE_MAP()
};
static CPara3* CP3_instance;//����ģʽ