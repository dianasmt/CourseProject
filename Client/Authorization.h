#pragma once
#include "ClientConnectionModule.h"

// CAuthorizationDlg dialog

class CAuthorizationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAuthorizationDlg)

public:
	CAuthorizationDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CAuthorizationDlg();

	BOOL OnInitDialog();

	TypeOfUser DoModal(ClientConnectionModule* pModule);

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_AUTHORIZATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnBnClickAuthorization();
	afx_msg void OnBnClickRegistration();

	DECLARE_MESSAGE_MAP()

	ClientConnectionModule* m_pModule;
	TypeOfUser m_TypeOfUser;

	CStatic m_wndIncorect;

	CEdit m_wndLogin;
	CEdit m_wndPassword;

	CButton m_wndBtnAuthorization;
	CButton m_wndLnkRegistration;
};
