#pragma once
#include <vector>
#include <list>
#include "../SerializableEntities/Object.h"
#include "ClientConnectionModule.h"
// CExpertMethodDlg dialog

class CExpertMethodDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CExpertMethodDlg)

public:
	CExpertMethodDlg(ClientConnectionModule* pModule, std::vector<Food>& lst, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CExpertMethodDlg();
	BOOL PreTranslateMessage(MSG* pMsg);

	virtual BOOL OnInitDialog();
	void UpdatePage();
	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_EXPERT_METHOD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedNext();
	afx_msg void OnBnClickedCancel();

	void AddToReport(Food& cloth);

	ClientConnectionModule* m_pModule;
	CListCtrl m_wndReportCtrl;
	CButton m_wndBtnCancel;
	CButton m_wndBtnNext;

	std::vector<Food>& m_Selected;
	std::list<Food> m_Objects;
	CComboBox combo11;
};
