#pragma once
#include "ClientConnectionModule.h"

class CMenuDlg : public CDialogEx
{
public:
	CMenuDlg(CWnd* pParent = nullptr);
	~CMenuDlg();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PATTERN_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnBtnProductClck();
	afx_msg void OnBtnUserClck();
	afx_msg void OnBtnExpertClck();
	afx_msg void OnBtnExitClck();
	afx_msg void OnStart();

	DECLARE_MESSAGE_MAP()

	HICON m_hIcon;
	ClientConnectionModule* m_pConnectionModule;
	TypeOfUser m_nTypeOfUser;

	CButton m_wndBtnProduct;
	CButton m_wndBtnUser;
	CButton m_wndBtnExpert;
	CButton m_wndBtnExit;
};
