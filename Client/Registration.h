#pragma once
#include "ClientConnectionModule.h"

// CRegistrationDlg dialog

class CRegistrationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRegistrationDlg)

public:
	CRegistrationDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CRegistrationDlg();

	BOOL OnInitDialog();
	BOOL PreTranslateMessage(MSG* pMsg);

	TypeOfUser DoModal(ClientConnectionModule* pModule);
	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_REGISTRATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	afx_msg void OnBnClickRegistration();

	DECLARE_MESSAGE_MAP()

	ClientConnectionModule* m_pModule;
	TypeOfUser m_TypeOfUser;

	CEdit m_wndLogin;
	CEdit m_wndPassword;
	CEdit m_wndPassRepeat;

	CButton m_wndBtnRegistration;

	CStatic m_wndExistst;
};
