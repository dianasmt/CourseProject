#pragma once
#include <vector>
#include "../SerializableEntities/Object.h"


// CExpDlg dialog

class CExpDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CExpDlg)

public:
	CExpDlg(std::vector<Food>& lst, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CExpDlg();

	virtual BOOL OnInitDialog();
	BOOL PreTranslateMessage(MSG* pMsg);
	void UpdatePage();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_EXPERT_METHOD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	std::vector<Food>& vect;

	CStatic static1t;
	CStatic static2t;
	CStatic static3t;
	CStatic static4t;

	CComboBox combo11;
	CComboBox combo12;
	CComboBox combo13;
	CComboBox combo14;
	CComboBox combo21;
	CComboBox combo22;
	CComboBox combo23;
	CComboBox combo24;
	CComboBox combo31;
	CComboBox combo32;
	CComboBox combo33;
	CComboBox combo34;
	CComboBox combo41;
	CComboBox combo42;
	CComboBox combo43;
	CComboBox combo44;

	afx_msg void OnBnClickedOk();
};