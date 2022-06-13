#pragma once
#include "../SerializableEntities/Object.h"
#include "ClientConnectionModule.h"

// CProductCtrlDlg dialog

class CProductCtrlDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProductCtrlDlg)

public:
	CProductCtrlDlg(ClientConnectionModule* pModule, TypeOfUser type, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CProductCtrlDlg();
	virtual BOOL OnInitDialog();
	BOOL PreTranslateMessage(MSG* pMsg);
	void UpdatePage();
	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PRODUCT_CONTROL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	void AddToReport(Food& cloth);

	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedEdit();
	afx_msg void OnBnClickedDel();
	afx_msg void OnBnClickedFilter();
	afx_msg void OnBnClickedSearch();
	afx_msg void OnBnClickedReport();

	DECLARE_MESSAGE_MAP()

	ClientConnectionModule* m_pModule;
	TypeOfUser m_TypeOfUser;

	std::list<Food> m_Objects;

	CString strNameFilter;
	CString strTypeFilter;

	double nMinFirst;
	double nMaxFirst;
	double dMinMark;
	double dMaxMark;

	CListCtrl m_wndReportCtrl;

	CButton m_wndBtnApplyFilter;
	CButton m_wndBtnApplySearch;
	CButton m_wndBtnAdd;
	CButton m_wndBtnDel;
	CButton m_wndBtnEdit;
	CButton m_wndBtnReport;

	CEdit m_wndEdit1From;
	CEdit m_wndEdit1To;
	CEdit m_wndEditMarkFrom;
	CEdit m_wndEditMarkTo;
	CEdit m_wndEditFilterName;
	CEdit m_wndEditFilterType;

	CEdit m_wndEditNameA;
	CEdit m_wndEditTypeA;
	CEdit m_wndEditFirstA;
	CEdit m_wndEditDescriptionA;

	CEdit m_wndEditNameE;
	CEdit m_wndEditTypeE;
	CEdit m_wndEditFirstE;
	CEdit m_wndEditDescriptionE;

	bool bSortedName;
	bool bSortedNameUp;
	bool bSortedCost;
	bool bSortedCostUp;

	afx_msg void OnBnClickedButtonSortName();
	afx_msg void OnBnClickedButtonSortCost();
public:
	afx_msg void OnLvnItemchangedListProducts(NMHDR* pNMHDR, LRESULT* pResult);
};
