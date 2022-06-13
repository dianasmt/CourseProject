#pragma once
#include "ClientConnectionModule.h"

// CAddUserDlg dialog

class CAddUserDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddUserDlg)

public:
	CAddUserDlg(ClientConnectionModule* pModule, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CAddUserDlg();
	BOOL PreTranslateMessage(MSG* pMsg);
	BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD_USER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	ClientConnectionModule* m_pModule;

	CEdit m_wndEditLogin;
	CEdit m_wndEditPassword;
	CEdit m_wndEditRepeat;
	CComboBox m_wndComboType;
	CStatic m_wndPassIncorrect;
	CStatic m_wndAlreadyExist;
};
