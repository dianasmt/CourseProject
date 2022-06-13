// CExpDlg.cpp : implementation file
//

#include "pch.h"
#include "CourceWorkApp.h"
#include "ExpertMethod.h"
#include "afxdialogex.h"
#include "Formatter.h"


// CExpDlg dialog

IMPLEMENT_DYNAMIC(CExpDlg, CDialogEx)

CExpDlg::CExpDlg(std::vector<Food>& lst, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_EXPERT_METHOD, pParent),
	vect(lst)
{

}

CExpDlg::~CExpDlg()
{
}

BOOL CExpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	static1t.SetWindowText(AtoW(vect[0].GetName()));
	static2t.SetWindowText(AtoW(vect[1].GetName()));
	static3t.SetWindowText(AtoW(vect[2].GetName()));
	static4t.SetWindowText(AtoW(vect[3].GetName()));

	for(auto combo : {&combo11,&combo21,&combo31,&combo41, 
					  &combo12,&combo22,&combo32,&combo42, 
					  &combo13,&combo23,&combo33,&combo43, 
				      &combo14,&combo24,&combo34,&combo44})
	{
		combo->AddString(L"1");
		combo->AddString(L"2");
		combo->AddString(L"3");
		combo->AddString(L"4");
		combo->AddString(L"5");
		combo->AddString(L"6");
		combo->AddString(L"7");
		combo->AddString(L"8");
		combo->AddString(L"9");
		combo->AddString(L"10");
		combo->SetCurSel(0);
	}
	//PostMessage(MSG_UPDATE);
	return TRUE;
}

void CExpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_1T, static1t);
	DDX_Control(pDX, IDC_STATIC_2T, static2t);
	DDX_Control(pDX, IDC_STATIC_3T, static3t);
	DDX_Control(pDX, IDC_STATIC_4T, static4t);

	DDX_Control(pDX, IDC_COMBO_11, combo11);
	DDX_Control(pDX, IDC_COMBO_12, combo12);
	DDX_Control(pDX, IDC_COMBO_13, combo13);
	DDX_Control(pDX, IDC_COMBO_14, combo14);
	DDX_Control(pDX, IDC_COMBO_21, combo21);
	DDX_Control(pDX, IDC_COMBO_22, combo22);
	DDX_Control(pDX, IDC_COMBO_23, combo23);
	DDX_Control(pDX, IDC_COMBO_24, combo24);
	DDX_Control(pDX, IDC_COMBO_31, combo31);
	DDX_Control(pDX, IDC_COMBO_32, combo32);
	DDX_Control(pDX, IDC_COMBO_33, combo33);
	DDX_Control(pDX, IDC_COMBO_34, combo34);
	DDX_Control(pDX, IDC_COMBO_41, combo41);
	DDX_Control(pDX, IDC_COMBO_42, combo42);
	DDX_Control(pDX, IDC_COMBO_43, combo43);
	DDX_Control(pDX, IDC_COMBO_44, combo44);
}


BEGIN_MESSAGE_MAP(CExpDlg, CDialogEx)
	ON_MESSAGE_VOID(MSG_UPDATE, UpdatePage)
	ON_BN_CLICKED(IDOK, &CExpDlg::OnBnClickedOk)
END_MESSAGE_MAP()


void CExpDlg::UpdatePage()
{

}

BOOL CExpDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;                // Do not process further
		}
	}

	return CWnd::PreTranslateMessage(pMsg);
}

// CExpDlg message handlers

void CExpDlg::OnBnClickedOk()
{
	double k1 = 0;
	double k2 = 0;
	double k3 = 0;
	double k4 = 0;
	
	for (auto combo : { &combo11, &combo21, &combo31, &combo41 })
	{
		int index = combo->GetCurSel();
		CString str;
		combo->GetLBText(index, str);
		k1 += _wtof(str);
	}

	for (auto combo : { &combo12, &combo22, &combo32, &combo42 })
	{
		int index = combo->GetCurSel();
		CString str;
		combo->GetLBText(index, str);
		k2 += _wtof(str);
	}

	for (auto combo : { &combo13, &combo23, &combo33, &combo43 })
	{
		int index = combo->GetCurSel();
		CString str;
		combo->GetLBText(index, str);
		k3 += _wtof(str);
	}

	for (auto combo : { &combo14, &combo24, &combo34, &combo44 })
	{
		int index = combo->GetCurSel();
		CString str;
		combo->GetLBText(index, str);
		k4 += _wtof(str);
	}

	double sum = k1 + k2 + k3 + k4;
	k1 /= sum;
	k2 /= sum;
	k3 /= sum;
	k4 /= sum;

	vect[0].SetMark(k1);
	vect[1].SetMark(k2);
	vect[2].SetMark(k3);
	vect[3].SetMark(k4);

	CString winner = AtoW(vect[0].GetName());
	if (k2 >= k1 && k2 >= k3 && k2 >= k4)winner = AtoW(vect[1].GetName());
	if (k3 >= k1 && k3 >= k2 && k3 >= k4)winner = AtoW(vect[2].GetName());
	if (k4 >= k1 && k4 >= k2 && k4 >= k3)winner = AtoW(vect[3].GetName());

	CString strFormat;
	strFormat.Format(L"Результат:\n%s = %.2lf\n%s = %.2lf\n%s = %.2lf\n%s = %.2lf\n\nЛучший результат - %s\n"
		, AtoW(vect[0].GetName()), k1, AtoW(vect[1].GetName()), k2, AtoW(vect[2].GetName()), k3, AtoW(vect[3].GetName()), k4, winner);

	MessageBox(strFormat);

	CDialogEx::OnOK();
}
