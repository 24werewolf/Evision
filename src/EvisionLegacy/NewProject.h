#pragma once


// CNewProject �Ի���

class CNewProject : public CDialogEx
{
	DECLARE_DYNAMIC(CNewProject)

public:
	CNewProject(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNewProject();

// �Ի�������
	enum { IDD = IDD_NewProject };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// �������湤����
	CString ProjectName;
};
