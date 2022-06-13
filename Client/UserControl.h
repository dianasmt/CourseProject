#pragma once
#include "ClientConnectionModule.h"

// CUserControlDlg dialog

class CUserControlDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUserControlDlg)

public:
	CUserControlDlg(ClientConnectionModule* pModule, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CUserControlDlg();
	virtual BOOL OnInitDialog();
	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_USER_CONTROL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL PreTranslateMessage(MSG* pMsg);
	void UpdatePage();

	void AddToReport(CString login, CString type);

	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedDel();

	DECLARE_MESSAGE_MAP()
public:
	ClientConnectionModule* m_pModule;

	std::list<Client> m_Clients;
	std::list<Admin> m_Admins;
	std::list<Expert> m_Experts;

	CListCtrl m_wndReport;
	CButton m_wndBtnAdd;
	CButton m_wndBtnDel;
};
